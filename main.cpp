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

#include "gui.h"
#include <QApplication>
#include <QTranslator>
#include <QDir>
#include "translatorhandler.h"
#include <QtDebug>
#include <QLibraryInfo>
#include "settings.h"

#if QT_VERSION < 0x50000
bool qEnvironmentVariableIsSet(const char *var){
    return !qgetenv(var).isNull();
}

#endif

void initializeSearchPaths(){

    qDebug() << "Initializating search paths...";

    auto addVar = [](QStringList & paths,const char* var){
        if (qEnvironmentVariableIsSet(var))
            paths.prepend(qgetenv(var));
    };

    QStringList ressPaths = {
        ":",
        ".",
        QDir::homePath().append("/.local/share/touchegg-gce"),
        "/usr/share/touchegg-gce",
        "/usr/local/share/touchegg-gce",
        "/opt/touchegg-gce/lib"
    };

    QStringList dictsPaths = {"ress:Dictionaries"};

    QStringList userConfPaths = {
        ".",
        QDir::homePath().append("/.config"),
    };
    QStringList sysConfPaths = {
        QDir::homePath().append("/.local/etc"),
        "/etc",
        "/usr/etc",
        "/usr/local/etc",
        "/etc/opt"
    };

    addVar(ressPaths,"TOUCHEGG_GCE_RESOURCES_PATH");
    addVar(dictsPaths,"TOUCHEGG_GCE_DICTS_PATH");
    addVar(userConfPaths,"TOUCHEGG_GCE_CONFIG_PATH");


    foreach(QString path, userConfPaths){
        QFileInfo confFile(path.append("/touchegg-gce.conf"));
        if(confFile.exists()){
            QSettings::setPath(QSettings::NativeFormat,
                               QSettings::UserScope,
                               confFile.canonicalPath());
            qDebug() << "User configuration file path:\n\t" << confFile.canonicalPath();
            break;
        }
    }
    foreach(QString path, sysConfPaths){
        QFileInfo confFile(path.append("/touchegg-gce.conf"));
        if(confFile.exists()){
            QSettings::setPath(QSettings::NativeFormat,
                               QSettings::SystemScope,
                               confFile.canonicalPath());
            qDebug() << "System configuration file path:\n\t" << confFile.canonicalPath();
            break;
        }
    }

    Settings *conf = Settings::instance();

    auto addConf = [conf](QStringList & paths,const char* var){
        if (conf->contains(var))
            paths.prepend(conf->value(var).toString());
    };

    addConf(dictsPaths, Settings::str_Locale_dictsPath);

    addConf(ressPaths, Settings::str_resourcesPath);

    QDir::setSearchPaths("dicts",dictsPaths);
    QDir::setSearchPaths("ress",ressPaths);

    qDebug() << "Resources search path:\n\t" << QDir::searchPaths("ress");
    qDebug() << "Translations search path:\n\t" << QDir::searchPaths("dicts");

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (QFileInfo(":/touchegg-gce.svg").exists())
        a.setWindowIcon(QIcon(":/touchegg-gce.svg"));
    else
        a.setWindowIcon(QIcon::fromTheme("touchegg-gce"));
#if QT_VERSION >= 0x50000
    a.setApplicationDisplayName("Touchégg GCE");
#endif
    a.setApplicationName("touchegg-gce");

    initializeSearchPaths();

    qDebug() << "Initializating translations...";
    QString lang = Settings::instance()->Locale_language();

    TranslatorHandler *th = TranslatorHandler::instance("dicts:", lang);

    QDebug(QtDebugMsg) << "Loading GUI...";
    Gui w;

    w.setLanguageList(th->dicts());
    w.setLanguage(th->current());
    a.connect(&w,SIGNAL(languageChanged(QString)),th,SLOT(load(QString)));

    w.show();

    return a.exec();
}
