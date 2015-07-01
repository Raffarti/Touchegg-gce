/**
 *This work is licensed under the
 *Creative Commons Attribuzione 3.0
 *Unported License. To view a copy
 *of this license, visit
 *http://creativecommons.org/licenses/by/3.0/
 *
 *Please note that this is not Touchégg nor Touchégg-gui,
 *which author is José Expósito <jose.exposito89@gmail.com>.
 *This is a gui interface to edit
 *Touchégg configuration file alternative to Touchégg-gui.
 *
 *@author Raffaele Pertile <raffarti@yahoo.it>
 */
#include "scribe.h"
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>
#include <QTextStream>
#include <QIODevice>

Scribe::Scribe(QObject *parent) :
    QObject(parent)
{
}

bool Scribe::open(QString name, int flag){
    file = new QFile(name);
    if (!file->exists() && flag < 1){
        QMessageBox *conf = new QMessageBox(QMessageBox::Warning,
                                       QString(tr("File not found")),
                                       QString(tr("Target file doesn't exists,\nmake a new one?")),
                                       QMessageBox::Yes|QMessageBox::Cancel);

        QObject::connect(conf,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(creationConfirmed(QAbstractButton*)));
        conf->show();
        return false;
    }
    else if (!file->exists()){
        if (!QFileInfo(*file).absoluteDir().exists() && flag < 2){
            QMessageBox *conf = new QMessageBox(QMessageBox::Warning,
                                           QString(tr("File path doesn't exists")),
                                                QString(tr("The folder of the file doesn't exists,\nmake a new one?")),
                                           QMessageBox::Yes|QMessageBox::Cancel);

            QObject::connect(conf,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(folderCreationConfirmed(QAbstractButton*)));
            conf->show();
            return false;
        }
        QDir("/").mkpath(QFileInfo(*file).absolutePath());
        if (!QFileInfo(*file).absoluteDir().exists()){
            QMessageBox *conf = new QMessageBox(QMessageBox::Critical,
                                           QString(tr("Cannot create folder")),
                                           QString(tr("Cannot create parent folder.")),
                                           QMessageBox::Ok);

            conf->show();
            return false;
        }
        if(!file->open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox *conf = new QMessageBox(QMessageBox::Critical,
                                           QString(tr("Cannot open file")),
                                           QString(file->exists()?
                                                       tr("Cannot write file.")
                                                       :tr("Cannot create the configuration file.")),
                                           QMessageBox::Ok);
            conf->show();
            return false;
        }
    }
    return true;
}


void Scribe::creationConfirmed(QAbstractButton *button){
    if (button->text() == "&Yes"){
        open(file->fileName(), 1);
    }
}


void Scribe::folderCreationConfirmed(QAbstractButton *button){
    if (button->text() == "&Yes"){
        open(file->fileName(), 2);
    }
}

void Scribe::restartTouchegg(QAbstractButton *button){
    if (button->text() == "&Yes"){
        system("killall touchegg");
        system("touchegg &");
    }
}

void Scribe::save(){
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream output(file);
    output.setCodec(QTextCodec::codecForName("UTF8"));
    output << QString::fromUtf8("<touchégg>") << endl;
    output << "\t<settings>"<< endl;
    foreach(QString prop, *Memory::getProps()){
        output << "\t\t<property name=\"" << prop << "\">";
        output << Memory::getProp(prop);
        output << "</property>" << endl;
    }
    output << "\t</settings>" << endl;
    foreach(QString group, *Memory::getGroupsNames()){
        QString apps = QString("");
        foreach(QString n, Memory::getGroup(group)->getAppsNames()){
            if (!apps.isEmpty()) apps.append(", ");
            apps.append(n);
        }
        output << "\t<application name=\"" << apps << "\">" << endl;
        foreach(Gesture *ges, Memory::getGroup(group)->getGests()){
            output << "\t\t<gesture type=\"" << *Lists::printTag(ges->getType()) << "\" ";
            output << "fingers=\"" << ges->getFingers() << "\" ";
            output << "direction=\"" << *Lists::printTag(ges->getDirection()) << "\">" << endl;
            Action *act = ges->getAction();
            output << "\t\t\t<action type=\"" << *Lists::printTag(act->getType()) << "\">";
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
