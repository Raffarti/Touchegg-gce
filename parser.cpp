/**************************************************************************
 * Copyright (c) 2012-2015 Raffaele Pertile <raffarti@zoho.com>
 * This file is part of touchegg-gce.
 *
 * touchegg-gce is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * touchegg-gce is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with touchegg-gce.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include "parser.h"
#include "general.h"

#include <QDebug>

Parser::Parser(QIODevice *dev):
    m_reader(dev)
{
}

Parser::~Parser(){
    QIODevice *input = m_reader.device();
    input->close();
    delete input;
}

void Parser::throwError(){
    state.append("ERROR");
}

void Parser::sStart(){
    if (m_reader.name() != QString::fromUtf8("touchégg")){
        throwError();
        return;
    }
    state.append("TOUCHEGG");
}

void Parser::sTouchegg(){
    if (m_reader.isStartElement()){
        if (m_reader.name() == "settings"){
            state.append("SETTINGS");
        } else if (m_reader.name() == "application"){
            if (!m_reader.attributes().hasAttribute("name")){
                throwError();
                return;
            }
            appKey = m_reader.attributes().value("name").toString();
            appKey = Memory::addGroup(appKey);
            state.append("APPLICATION");
        }
        else {
            throwError();
            return;
        }
    } else if (m_reader.isEndElement() && m_reader.name() == QString::fromUtf8("touchégg")){
        state.removeLast();
        return;
    } else {
        throwError();
        return;
    }
}

void Parser::sSettings(){
    if (m_reader.isStartElement()){
        if (m_reader.name() == "property"){
            if (!m_reader.attributes().hasAttribute("name")){
                throwError();
                return;
            }
            state.append("PROPERTY");
            sProperty(m_reader.attributes().value("name").toString());
        }
        else {
            throwError();
            return;
        }
    } else if (m_reader.isEndElement() && m_reader.name() == "settings"){
        state.removeLast();
        return;
    } else {
        throwError();
        return;
    }
}

void Parser::sProperty(QString key){
    Memory::addProp(key,m_reader.readElementText());
    state.removeLast();
}

void Parser::sApplication(){
    if (m_reader.isEndElement() && m_reader.name() == "application"){
        state.removeLast();
        return;
    } else if (m_reader.isStartElement() && m_reader.name() == "gesture"){
        auto attrs = m_reader.attributes();
        if (!(attrs.hasAttribute("type") ||
              attrs.hasAttribute("fingers") ||
              attrs.hasAttribute("direction"))){
            throwError();
            return;
        }

        ges = new gesture;
        ges->type = attrs.value("type").toString();
        ges->num = attrs.value("fingers").toString().toInt();
        ges->direction = attrs.value("direction").toString();
        state.append("GESTURE");
    } else {
        throwError();
        return;
    }
}

void Parser::sGesture(){
    if (m_reader.isEndElement() && m_reader.name() == "gesture"){
        state.removeLast();
        return;
    } else if (m_reader.isStartElement() && m_reader.name() == "action"){
        state.append("ACTION");
        auto attrs = m_reader.attributes();
        if (!attrs.hasAttribute("type")){
            throwError();
            return;
        }
        Group *g = Memory::getGroup(appKey);
        g->addGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction));
        Gesture *gest = g->getGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction));
        gest->setAction(Lists::aT(attrs.value("type").toString()));
        //sAction(g->getGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction))->getAction());->setAction(Lists::aT(attrs.value("type").toString()))
        QStringList params = m_reader.readElementText().split(":");
        foreach(const QString &p, params)
            gest->getAction()->addParam(p.section("=",0,0),p.section("=",1));

        state.removeLast();
    } else {
        throwError();
        return;
    }

}


bool Parser::loadAll(){
    state = QStringList();
    state.append("START");
    error.ch = 0;
    error.line = 1;
    error.pos = 0;
    error.msg = QString::null;
    Memory();
    while(!m_reader.atEnd()){
        m_reader.readNext();
        if (!m_reader.isStartElement() && !m_reader.isEndElement()) continue;
        if (!state.last().compare("START")) sStart();
        else if (!state.last().compare("TOUCHEGG")) sTouchegg();
        else if (!state.last().compare("SETTINGS")) sSettings();
        else if (!state.last().compare("APPLICATION")) sApplication();
        else if (!state.last().compare("GESTURE")) sGesture();
        else throwError();
        if (m_reader.error() != QXmlStreamReader::NoError)
            throwError();
        if (!state.last().compare("ERROR")){
            qWarning() << QString("Error while parsing:%1:%2\nstate:\t"+state.at(state.length()-2)).arg(error.line).arg(error.pos);
            if (m_reader.error() != QXmlStreamReader::NoError) qWarning() << m_reader.errorString();
            return false;
        }
    }
    qDebug() << "Config file loaded.";
    return true;
}
