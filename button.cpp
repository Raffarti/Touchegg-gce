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

#include "button.h"
#include "ui_button.h"
#include "editdialog.h"

Button::Button(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::button)
{
    ui->setupUi(this);
    bLabel.gesture = findChild<QLabel*>("lg");
    bLabel.fingers = findChild<QLabel*>("lf");
    bLabel.direction = findChild<QLabel*>("ld");
    bLabel.layout = findChild<QGridLayout*>("optionLayout");
}

Button::~Button()
{
    delete ui;
}

/**
 * @brief on_pushButton_2_clicked
 *Create the edit dialog of a gesture
 */
void Button::on_pushButton_2_clicked()
{
    EditDialog *a = new EditDialog(getGesture(), this);
    a->open();
    a->b = this;
    a->setUp(false);
}

/**
 *
 * @brief setGesture Needed to keep a link between
 *          data struct and interface.
 * @param gesture set the gesture related to this bottom.
 */
void Button::setGesture(Gesture *gesture){
    this->gesture = gesture;
}

/**
 * @brief getGesture get the referece to the gesture
 *          related to this interface.
 * @return the referece to the gesture
 *          related to this interface.
 */
Gesture* Button::getGesture(){
    return gesture;
}

/**
 * @brief on_pushButton_clicked
 *Remove the gesture
 */
void Button::on_pushButton_clicked()
{
    gesture->destroy();
    delete this;
}

void Button::on_pushButton_3_clicked()
{
    EditDialog *a = new EditDialog(getGesture(), this);
    a->open();
    a->b = this;
    a->setUp(true);
}
