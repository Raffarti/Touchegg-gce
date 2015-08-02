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


void Parser::sStart(){
    if (m_reader.name() != QString::fromUtf8("touchégg"))
        throw(err(QString::fromUtf8("Found string: %1, touchégg expected.").arg(m_reader.name().toString())));
    state.append("TOUCHEGG");
}

void Parser::sTouchegg(){
    if (m_reader.isStartElement()){
        if (m_reader.name() == "settings"){
            state.append("SETTINGS");
        } else if (m_reader.name() == "application"){
            if (!m_reader.attributes().hasAttribute("name"))
                throw(err("Attribute 'name' expected."));

            appKey = m_reader.attributes().value("name").toString();
            appKey = Memory::addGroup(appKey);
            state.append("APPLICATION");
        }
        else
            throw(QString("Unrecognized string \"%1\" for token \"%2\".")
                       .arg(m_reader.name().toString())
                       .arg(m_reader.tokenString()));
    } else if (m_reader.isEndElement() && m_reader.name() == QString::fromUtf8("touchégg")){
        state.removeLast();
        return;
    } else
        throw(QString("Unrecognized string \"%1\" for token \"%2\".")
                   .arg(m_reader.name().toString())
                   .arg(m_reader.tokenString()));
}

void Parser::sSettings(){
    if (m_reader.isStartElement()){
        if (m_reader.name() == "property"){
            if (!m_reader.attributes().hasAttribute("name"))
                throw(err("Attribute 'name' expected."));

            state.append("PROPERTY");
            sProperty(m_reader.attributes().value("name").toString());
        }
        else
            throw(QString("Unrecognized string \"%1\" for token \"%2\".")
                       .arg(m_reader.name().toString())
                       .arg(m_reader.tokenString()));
    } else if (m_reader.isEndElement() && m_reader.name() == "settings"){
        state.removeLast();
        return;
    } else
        throw(QString("Unrecognized string \"%1\" for token \"%2\".")
                   .arg(m_reader.name().toString())
                   .arg(m_reader.tokenString()));
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
              attrs.hasAttribute("direction")))
            throw(err("Missing gesture attribute."));

        ges = new gesture;
        ges->type = attrs.value("type").toString();
        ges->num = attrs.value("fingers").toString().toInt();
        ges->direction = attrs.value("direction").toString();
        state.append("GESTURE");
    } else
        throw(QString("Unrecognized string \"%1\" for token \"%2\".")
                   .arg(m_reader.name().toString())
                   .arg(m_reader.tokenString()));
}

void Parser::sGesture(){
    if (m_reader.isEndElement() && m_reader.name() == "gesture"){
        state.removeLast();
        return;
    } else if (m_reader.isStartElement() && m_reader.name() == "action"){
        state.append("ACTION");
        auto attrs = m_reader.attributes();
        if (!attrs.hasAttribute("type"))
            throw(err("Attribute 'type' expected."));

        Group *g = Memory::getGroup(appKey);
        g->addGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction));
        Gesture *gest = g->getGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction));
        gest->setAction(Lists::aT(attrs.value("type").toString()));
        //sAction(g->getGest(ges->num, Lists::gT(ges->type), Lists::gD(ges->direction))->getAction());->setAction(Lists::aT(attrs.value("type").toString()))
        QStringList params = m_reader.readElementText().split(":");
        foreach(const QString &p, params)
            gest->getAction()->addParam(p.section("=",0,0),p.section("=",1));

        state.removeLast();
    } else
        throw(QString("Unrecognized string \"%1\" for token \"%2\".")
                   .arg(m_reader.name().toString())
                   .arg(m_reader.tokenString()));

}

Parser::error Parser::err(const QString &msg)
{
    return error(m_reader,msg);
}


bool Parser::loadAll(){
    state = QStringList();
    state.append("START");
    Memory();
    try{
        m_reader.readNextStartElement();
        sStart();
        while(state.last() != "START"){
            m_reader.readNextStartElement();
            if (state.last() == "TOUCHEGG") sTouchegg();
            else if (state.last() == "SETTINGS") sSettings();
            else if (state.last() == "APPLICATION") sApplication();
            else if (state.last() == "GESTURE") sGesture();
            else throw(err("Unhandled state."));
            if (m_reader.hasError())
                throw(err("Xml stream error."));
        }
        qDebug() << "Config file loaded.";
    } catch(const error & e){
        qWarning() << QString("Error while parsing at:%1:%2\nstate:\t"+state.last()).arg(e.line).arg(e.pos);
        if (m_reader.hasError()) qWarning() << m_reader.errorString();
        else qWarning() << e.msg;
        return false;
    }
    return true;
}
