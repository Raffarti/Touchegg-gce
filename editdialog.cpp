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
#include "editdialog.h"
#include "ui_editdialog.h"
#include "gui.h"


EditDialog::EditDialog(Gesture *gesture, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    this->gesture = gesture;

    QObject *gui = parent;
    while(gui->objectName() != "Gui") gui = gui->parent();
    connect(this, SIGNAL(done(Gesture*)), gui, SLOT(on_editDialog_done(Gesture*)));
}
EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    this->gesture = NULL;

    QObject *gui = parent;
    while(gui->objectName() != "Gui") gui = gui->parent();
    connect(this, SIGNAL(done(Gesture*)), gui, SLOT(on_editDialog_done(Gesture*)));
}

EditDialog::~EditDialog()
{
    delete ui;
}

Gesture* EditDialog::getGesture(){
    return gesture;
}

void EditDialog::setUp(bool fullEditable){
    fingSpin = findChild<QSpinBox *>("fingers");
    gesType = findChild<QComboBox *>("gesture");
    gesDirection = findChild<QComboBox *>("direction");
    actionList = findChild<QComboBox*>("actionList");
    actionList->addItems(*Lists::actionList());
    gesType->addItems(*Lists::gestureTypes());
    fingSpin->setMaximum(5);
    fingSpin->setMinimum(1);
    if (!fullEditable){
        fingSpin->setValue(b->bLabel.fingers->text().toInt());
        gesType->setCurrentIndex(gesType->findText(b->bLabel.gesture->text()));
        gesDirection->addItems(*Lists::gestureDirections(Lists::toGT(b->bLabel.gesture->text())));
        gesDirection->setCurrentIndex(gesDirection->findText(b->bLabel.direction->text()));
        actionList->setCurrentIndex(actionList->findText(b->bLabel.action->text()));
        gesDirection->setEnabled(false);
        gesType->setEnabled(false);
        fingSpin->setEnabled(false);
    }
    else{
        gesDirection->addItems(*Lists::gestureDirections(Lists::toGT(gesType->currentText())));
    }
}




void EditDialog::cleanLayout(QLayout* l){
    QLayoutItem *wItem;
    while ((wItem = l->takeAt(0)) != 0){
        delete wItem->widget();
        delete wItem;
    }
}

void EditDialog::on_actionList_currentIndexChanged(const QString &arg1)
{
    QGridLayout *actionArea = findChild<QGridLayout *>("actionArea");
    cleanLayout(actionArea);
    int lines = 0;
    switch(Lists::toAT(arg1)){
    case Lists::CLOSE_WINDOW:
    case Lists::MOVE_WINDOW:
    case Lists::RESIZE_WINDOW:
    case Lists::CHANGE_DESKTOP:
    case Lists::CHANGE_VIEWPORT:
    case Lists::MINIMIZE_WINDOW:
    case Lists::MAXIMIZE_RESTORE_WINDOW:
    case Lists::SHOW_DESKTOP:
    case Lists::NO_ACTION: break;
    case Lists::DRAG_AND_DROP:
    case Lists::MOUSE_CLICK:{
        actionArea->addWidget(new QLabel(tr("Button:"),this),0,0);
        QSpinBox *box = new QSpinBox(this);
        box->setObjectName("buttonSpin");
        box->setMinimum(1);
        box->setMaximum(7);
        if(b != NULL && (b->bLabel.action->text() == Lists::toString(Lists::MOUSE_CLICK) || b->bLabel.action->text() == Lists::toString(Lists::DRAG_AND_DROP)))
            box->setValue(getGesture()->getAction()->getParamValue("BUTTON").toInt());
        actionArea->addWidget(box,0,1);
        lines = 1;
        break;}
    case Lists::SCROLL:{
        actionArea->addWidget(new QLabel(tr("Speed:"),this),0,0);
        QSpinBox *box = new QSpinBox(this);
        box->setObjectName("speedSpin");
        box->setMinimum(1);
        if(b != NULL && b->bLabel.action->text() == Lists::toString(Lists::SCROLL))
            box->setValue(getGesture()->getAction()->getParamValue("SPEED").toInt());
        actionArea->addWidget(box,0,1);
        actionArea->addWidget(new QLabel(tr("Inverted:"),this),1,0);
        QCheckBox *box2 = new QCheckBox(this);
        box2->setObjectName("invertedCombo");
        if(b != NULL && b->bLabel.action->text() == Lists::toString(Lists::SCROLL))
            box2->setChecked(getGesture()->getAction()->getParamValue("INVERTED").toLower() == "true");
        actionArea->addWidget(box2,1,1);
        lines = 2;
        break;}
    case Lists::SEND_KEYS:{
        SendKeys *box = new SendKeys();
        box->setObjectName("keysEditor");
        if(b != NULL && b->bLabel.action->text() == Lists::toString(Lists::SEND_KEYS))
            box->setKeys(gesture->getAction()->getParamKeys().first());
        actionArea->addWidget(box,0,0);
        lines = 1;
        break;}
    case Lists::RUN_COMMAND:{
        actionArea->addWidget(new QLabel(tr("Command:"),this),0,0);
        QLineEdit *box = new QLineEdit();
        box->setObjectName("commandLine");
        if(b != NULL && b->bLabel.action->text() == Lists::toString(Lists::RUN_COMMAND))
            box->setText(gesture->getAction()->getParamKeys().first());
        actionArea->addWidget(box,0,1);
        lines = 1;
        break;}
    }
    actionArea->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),lines,0);
}

void EditDialog::on_buttonBox_rejected()
{
    delete this;
}

void EditDialog::on_buttonBox_accepted()
{
    if (fingSpin->isEnabled()){
        gesture = new Gesture(fingSpin->value(), Lists::toGT(gesType->currentText()), Lists::toGD(gesDirection->currentText()), NULL);
    }
    QComboBox *actionCombo = findChild<QComboBox *>("actionList");
    Lists::ActionType act = Lists::toAT(actionCombo->currentText());
    switch(act){
    case Lists::CLOSE_WINDOW:
    case Lists::MOVE_WINDOW:
    case Lists::RESIZE_WINDOW:
    case Lists::CHANGE_DESKTOP:
    case Lists::CHANGE_VIEWPORT:
    case Lists::MINIMIZE_WINDOW:
    case Lists::MAXIMIZE_RESTORE_WINDOW:
    case Lists::SHOW_DESKTOP:
    case Lists::NO_ACTION:
        gesture->setAction(new Action(act));
        break;
    case Lists::DRAG_AND_DROP:
    case Lists::MOUSE_CLICK:{
        QSpinBox *box = findChild<QSpinBox*>("buttonSpin");
        Action *newAct = new Action(act);
        newAct->addParam("BUTTON",QString::number(box->value()));
        gesture->setAction(newAct);
        break;}
    case Lists::SCROLL:{
        QSpinBox *box = findChild<QSpinBox*>("speedSpin");
        QCheckBox *box2 = findChild<QCheckBox*>("invertedCombo");
        Action *newAct = new Action(act);
        newAct->addParam("SPEED",QString::number(box->value()));
        newAct->addParam("INVERTED",box2->isChecked()?"true":"false");
        gesture->setAction(newAct);
        break;}
    case Lists::SEND_KEYS:{
        SendKeys *box = findChild<SendKeys *>("keysEditor");
        Action *newAct = new Action(act);
        newAct->addParam(box->getKeys());
        gesture->setAction(newAct);
        break;}
    case Lists::RUN_COMMAND:{
        QLineEdit *box = findChild<QLineEdit*>("commandLine");
        Action *newAct = new Action(act);
        newAct->addParam(box->text());
        gesture->setAction(newAct);
        break;}
    }
    if(fingSpin->isEnabled())emit done(gesture);
    else emit done(NULL);
    deleteLater();

}

void EditDialog::on_gesture_currentIndexChanged(const QString &arg1)
{
    gesDirection->clear();
    gesDirection->addItems(*Lists::gestureDirections(Lists::toGT(arg1)));
}
