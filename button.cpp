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
#include "button.h"
#include "ui_button.h"
#include "editdialog.h"

button::button(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::button)
{
    ui->setupUi(this);
    bLabel.gesture = findChild<QLabel*>("lg");
    bLabel.fingers = findChild<QLabel*>("lf");
    bLabel.direction = findChild<QLabel*>("ld");
    bLabel.layout = findChild<QGridLayout*>("optionLayout");
}

button::~button()
{
    delete ui;
}

/**
 * @brief on_pushButton_2_clicked
 *Create the edit dialog of a gesture
 */
void button::on_pushButton_2_clicked()
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
void button::setGesture(Gesture *gesture){
    this->gesture = gesture;
}

/**
 * @brief getGesture get the referece to the gesture
 *          related to this interface.
 * @return the referece to the gesture
 *          related to this interface.
 */
Gesture* button::getGesture(){
    return gesture;
}

/**
 * @brief on_pushButton_clicked
 *Remove the gesture
 */
void button::on_pushButton_clicked()
{
    gesture->destroy();
    delete this;
}
