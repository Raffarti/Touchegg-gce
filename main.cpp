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
#include "gui.h"
#include <QApplication>
#include <QTranslator>
#include <QComboBox>
#include <QPushButton>
#include <QDir>
#include <QDebug>


int main(int argc, char *argv[])
{
    //Asking user for language and starting application
    QApplication a(argc, argv);
    QTranslator *t = new QTranslator();
    QDialog *diag = new QDialog();
    diag->setLayout(new QHBoxLayout());
    QComboBox *chooser = new QComboBox(diag);

    QStringList dirs;
    dirs << "" << DICTS_PREFIX;
    qDebug() << dirs;
    QFileInfoList langs;

    QStringList visited_dirs;
    foreach(QString dirName, dirs){
        QDir dir(dirName);
        if (!dir.exists() || visited_dirs.contains(dir.canonicalPath()))
            continue;

        visited_dirs << dir.canonicalPath();
        dir.cd("Dictionaries");
        langs += dir.entryInfoList(QStringList("[A-Z][A-Z]*.qm"), QDir::Files);
    }

    QStringList chopped = QStringList();
    foreach(QFileInfo s, langs){
        chopped.append(s.completeBaseName());
    }

    if (!chopped.isEmpty()){
        chooser->addItems(chopped);
        QPushButton *button = new QPushButton("Ok",diag);
        diag->connect(button,SIGNAL(clicked()),diag,SLOT(close()));
        diag->layout()->addWidget(chooser);
        diag->layout()->addWidget(button);
        diag->exec();
        QFileInfo langFile = langs.at(chooser->currentIndex());//langs.at(sel->value);
        t->load(langFile.completeBaseName(),langFile.canonicalPath());
        a.installTranslator(t);

    }
    delete diag;
    Gui w;
    w.show();

    return a.exec();
}
