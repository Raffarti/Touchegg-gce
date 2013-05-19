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
#include "langselector.h"
#include <QComboBox>
#include <QPushButton>


int main(int argc, char *argv[])
{
    QDir::setCurrent(QFileInfo(QString(argv[0])).absoluteDir().absolutePath());
    qDebug(QFileInfo(QString(argv[0])).absoluteDir().absolutePath().prepend("cd ").toLatin1());

    //Asking user for language and starting application
    QApplication a(argc, argv);
    QTranslator *t = new QTranslator();
    QDialog *diag = new QDialog();
    diag->setLayout(new QHBoxLayout());
    QComboBox *chooser = new QComboBox(diag);
    QDir *dir = new QDir("Dictionaries");
    QStringList langs = dir->entryList(QStringList("[A-Z][A-Z]*.qm"), QDir::Files);
    QStringList chopped = QStringList();
    foreach(QString s, langs){
        s.chop(3);
        chopped.append(s);
    }

    chooser->addItems(chopped);
    LangSelector *sel = new LangSelector();
    diag->connect(chooser,SIGNAL(currentIndexChanged(int)),sel,SLOT(set(int)));
    QPushButton *button = new QPushButton("Ok",diag);
    diag->connect(button,SIGNAL(clicked()),diag,SLOT(close()));
    diag->layout()->addWidget(chooser);
    diag->layout()->addWidget(button);
    diag->exec();
    t->load(QString("Dictionaries/").append(chopped.at(sel->value)));
    qDebug("%d",sel->value);
    a.installTranslator(t);

    Gui w;
    w.show();

    return a.exec();
}
