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
