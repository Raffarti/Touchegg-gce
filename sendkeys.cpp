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
#include "sendkeys.h"
#include "ui_sendkeys.h"
//#include <QDebug>

SendKeys::SendKeys(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SendKeys)
{
    ui->setupUi(this);
    superBox = findChild<QCheckBox *>("superBox");
    ctrlBox = findChild<QCheckBox *>("ctrlBox");
    altBox = findChild<QCheckBox *>("altBox");
    altGrBox = findChild<QCheckBox *>("altGrBox");
    shiftBox = findChild<QCheckBox *>("shiftBox");
    keyBox = findChild<QLineEdit *>("keyBox");
}

SendKeys::~SendKeys()
{
    delete ui;
}

void SendKeys::setKeys(QString keys){
    int k = 0;
    while (true){
        QString part = keys.section('+',k,k,QString::SectionSkipEmpty);
        if (part.isEmpty()) break;
        while (part.startsWith(" ")) part.remove(0,1);
        while (part.endsWith(" ")) part.chop(1);
        if (!part.isEmpty()){
            if (part == "Super")  superBox->setChecked(true);
            else if (part == "Shift")  shiftBox->setChecked(true);
            else if (part == "Control")  ctrlBox->setChecked(true);
            else if (part == "Alt")  altBox->setChecked(true);
            else if (part == "AltGr")  altGrBox->setChecked(true);
            else keyBox->setText(keyBox->text().append(keyBox->text().isEmpty()?"":"+").append(part));
        }
        k++;
    }
}

QString SendKeys::getKeys(){

    QString ret = QString("");
    if (superBox->isChecked()) ret.append("Super");
    if (ctrlBox->isChecked()){
        if (!ret.isEmpty()) ret.append("+");
        ret.append("Control");
    }
    if (altBox->isChecked()){
            if (!ret.isEmpty()) ret.append("+");
            ret.append("Alt");
    }
    if (altGrBox->isChecked()){
            if (!ret.isEmpty()) ret.append("+");
            ret.append("AltGr");
    }
    if (shiftBox->isChecked()){
            if (!ret.isEmpty()) ret.append("+");
            ret.append("Shift");
    }
    if (!keyBox->text().isEmpty()){
            if (!ret.isEmpty()) ret.append("+");
            ret.append(keyBox->text());
    }
    return ret;
}

void SendKeys::on_keyBox_textChanged(const QString &/*arg1*/)
{

}

void SendKeys::on_keyBox_textEdited(const QString &/*arg1*/)
{
 //   QLineEdit *keyBox = findChild<QLineEdit *>("keyBox");

}


void SendKeys::on_keyBox_keyCatched(const QString & /*text*/)
{
    //qDebug() << text;
}

void SendKeys::on_pushButton_clicked()
{
 //   QLineEdit *keyBox = findChild<QLineEdit *>("keyBox");
    keyBox->clear();
}
