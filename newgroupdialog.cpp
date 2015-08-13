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

#include "newgroupdialog.h"
#include "ui_newgroupdialog.h"

NewGroupDialog::NewGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGroupDialog)
{
    ui->setupUi(this);
    QComboBox *groups = findChild<QComboBox*>("groupCombo");
    groups->addItem("<No imports>");
    groups->addItems(Memory::getGroupsNames());
    QComboBox *targets = findChild<QComboBox*>("targetCombo");
    targets->addItem("<New group>");
    targets->addItems(Memory::getGroupsNames());
    targets->removeItem(targets->findText("All"));
}

NewGroupDialog::~NewGroupDialog()
{
    delete ui;
}

void NewGroupDialog::accept()
{
    QDialog::accept();
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
