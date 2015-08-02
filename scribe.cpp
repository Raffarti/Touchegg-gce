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

#include "scribe.h"
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>

Scribe::Scribe(QObject *parent) :
    QObject(parent)
{
}

bool Scribe::open(const QString &path){
    QFileInfo info(path);
    if (!info.exists()){
        if (!info.dir().exists()){
            auto result = QMessageBox::question(0,tr("File error"),
                                                tr("File path does not exists, create it?"),QMessageBox::Ok|QMessageBox::Cancel);
            if (result != QMessageBox::Ok)
                return false;
            if (!info.dir().mkpath(info.path())){
                QMessageBox::critical(0,tr("File error"),
                                      tr("Cannot create file path."));
                return false;
            }
        } else {
            auto result = QMessageBox::question(0,tr("File does not exists"),
                                                tr("File does not exists, create a new one?"),
                                                QMessageBox::Ok|QMessageBox::Cancel);
            if (result != QMessageBox::Ok)
                return false;
        }
    }
    file = new QFile(path);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(0,tr("File error"),
                              tr("Cannote write configuration file, check permissions."));
        return false;
    }
    return true;
}

void Scribe::restartTouchegg(QAbstractButton *button){
    if (button->text() == "&Yes"){
        system("killall touchegg");
        system("touchegg &");
    }
}

void Scribe::save(){
    QTextStream output(file);
    output.setCodec(QTextCodec::codecForName("UTF8"));
    output << QString::fromUtf8("<touchégg>") << endl;
    output << "\t<settings>"<< endl;
    foreach(QString prop, Memory::getProps()){
        output << "\t\t<property name=\"" << prop << "\">";
        output << Memory::getProp(prop);
        output << "</property>" << endl;
    }
    output << "\t</settings>" << endl;
    foreach(QString group, Memory::getGroupsNames()){
        QString apps = QString("");
        foreach(QString n, Memory::getGroup(group)->getAppsNames()){
            if (!apps.isEmpty()) apps.append(", ");
            apps.append(n);
        }
        output << "\t<application name=\"" << apps << "\">" << endl;
        foreach(Gesture *ges, Memory::getGroup(group)->getGests()){
            output << "\t\t<gesture type=\"" << Lists::printTag(ges->getType()) << "\" ";
            output << "fingers=\"" << ges->getFingers() << "\" ";
            output << "direction=\"" << Lists::printTag(ges->getDirection()) << "\">" << endl;
            Action *act = ges->getAction();
            output << "\t\t\t<action type=\"" << Lists::printTag(act->getType()) << "\">";
            bool first = true;
            foreach(QString par, act->getParamKeys()){
                if (!first) output << ":";
                output << par;
                if (!act->getParamValue(par).isNull()){
                    output << "=" << act->getParamValue(par);
                }
                first = false;
            }
            output << "</action>" << endl;
            output << "\t\t</gesture>" << endl;
        }

        output << "\t</application>" << endl;
    }
    output << QString::fromUtf8("</touchégg>");

    file->close();

    QMessageBox *conf = new QMessageBox(QMessageBox::Question,
                                   QString(tr("Saving complite")),
                                   QString(tr("Confiuration file generated.\nRestart touchegg?")),
                                   QMessageBox::Yes|QMessageBox::No);
    QObject::connect(conf,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(restartTouchegg(QAbstractButton*)));
    conf->show();

}
