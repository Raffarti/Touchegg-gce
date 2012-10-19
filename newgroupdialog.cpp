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
#include "newgroupdialog.h"
#include "ui_newgroupdialog.h"

NewGroupDialog::NewGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGroupDialog)
{
    ui->setupUi(this);
    QComboBox *groups = findChild<QComboBox*>("groupCombo");
    groups->addItem("<No imports>");
    groups->addItems(*Memory::getGroupsNames());
    QComboBox *targets = findChild<QComboBox*>("targetCombo");
    targets->addItem("<New group>");
    targets->addItems(*Memory::getGroupsNames());
    targets->removeItem(targets->findText("All"));
}

NewGroupDialog::~NewGroupDialog()
{
    delete ui;
}

void NewGroupDialog::on_NewGroupDialog_accepted()
{
}

void NewGroupDialog::on_buttonBox_accepted()
{
    QLineEdit *apps = findChild<QLineEdit*>();
    QComboBox *group = findChild<QComboBox*>("groupCombo");
    QComboBox *target = findChild<QComboBox*>("targetCombo");
    if (!target->currentIndex()){
        QString newGroup = Memory::addGroup(apps->text());
        if (group->currentIndex() != 0)
            foreach(Gesture *ges, Memory::getGroup(group->currentText())->getGests())
                Memory::getGroup(newGroup)->addGest(new Gesture(ges));
    }
    else Memory::getGroup(target->currentText())->addApps(apps->text());
    emit done();
}

void NewGroupDialog::on_targetCombo_currentIndexChanged(int index)
{
    QComboBox *group = findChild<QComboBox*>("groupCombo");
    group->setEnabled(index == 0);
}
