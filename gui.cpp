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
#include <QLineEdit>
#include <QLabel>
#include <QSettings>
#include "parser.h"
#include <QStandardItemModel>
#include <QGridLayout>
#include <QSlider>
#include <QObjectList>
#include <QBoxLayout>
#include "general.h"
#include "scribe.h"
#include "newgroupdialog.h"
#include "ui_gui.h"
#include "button.h"
#include "ui_button.h"
#include "editdialog.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui),
    parser(nullptr)
{
    ui->setupUi(this);

    QSettings settings("touchegg-gce");
    if (settings.contains("filePath"))
        filePath = settings.value("filePath").toString();
    else
        filePath = "~/.config/touchegg/";

    ui->filePath->setText(filePath);

    linePath = ui->filePath;
    QScrollArea *sarea = ui->scrollArea;

    //scroll area for gesture list
    QWidget *wsa = new QWidget();
    wsa->setLayout(new QVBoxLayout(sarea));
    wsa->layout()->setSizeConstraint(QLayout::SetFixedSize);
    sarea->setWidget(wsa);

    //tree for applications
    QTreeView *tree = ui->treeView;
    model = new QStandardItemModel(tree);
    adv = ui->advFrame;
    adv->hide();
    tree->setModel(new QStandardItemModel());
    tree->setModel(model);
    //connecting tree with data struct
    connect(model, SIGNAL(itemChanged(QStandardItem*)),this, SLOT(groupMoved(QStandardItem* )));

    //composed gesture slider
    slider = ui->cgt;
}

Gui::~Gui()
{
    delete ui;
}

QString Gui::getPath(){
    QString ret = filePath;
    //parsing standard home notation
    ret.replace(QRegExp("^~"),QDir::homePath());
    //is the path is a directory, adding touchegg.conf as file by default
    if (QFileInfo(ret).isDir()){
        ret = QFileInfo(ret).canonicalPath().append(QString("/touchegg.conf"));
    }
    if (ret.endsWith("/"))
        ret.append(QString("/touchegg.conf"));
    return ret;
}

void Gui::loadFile(QString path){
    QFile *file = new QFile(path);
    if (!file->exists()){
        QMessageBox::warning(this, tr("File Error"), tr("Target file does not exists."));
        return;
    }
    if (!file->open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, tr("File Error"), tr("Target file cannot be opened."));
        return;
    }
    if (parser) delete parser;
    parser = new Parser(file);
    if (!parser->loadAll())return;

    //enable componentss requiring a memory loaded.
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->saveChooser->setEnabled(true);

    QScrollArea *sarea = ui->scrollArea;
    //clear gesture list
    cleanLayout(sarea->widget()->layout());
    //clear tree view and add application found in data struct memory
    refreshGroupTree();
    //setting props (only gesture time present atm)
    foreach(QString key, Memory::getProps()){
        if (key == "composed_gestures_time"){
            slider->setEnabled(true);
            slider->setValue(Memory::getProp(key).toInt());
        }
    }
}



void Gui::on_filePath_textEdited(const QString &arg1)
{
    //update filePath on gui request
    filePath = arg1;
}

void Gui::on_checkBox_toggled(bool checked)
{
    //shows advanced inteface
    if (checked) adv->show();
    else adv->hide();
}

void Gui::on_cgt_valueChanged(int value)
{
    //sync memory with gesture timer slider
    ui->sliderValue->setText(QString(tr("Value: ")).append(QString::number(value)).append("ms"));
    Memory::removeProp("composed_gestures_time");
    Memory::addProp("composed_gestures_time",QString::number(value));
}


void Gui::on_pushButton_6_clicked()
{
    //reset path button
    QSettings settings("touchegg-gce");
    if (settings.contains("filePath") && settings.value("filePath") != filePath)
        filePath = settings.value("filePath").toString();
    else
        filePath = "~/.config/touchegg/";
    linePath->setText(filePath);
}

void Gui::on_pushButton_3_clicked()
{

    //Load button trigger
    qDebug() << filePath;
    loadFile(getPath());
}

void Gui::on_treeView_clicked(const QModelIndex &index)
{

    //display gesture list on user tree interaction
    QModelIndex i;
    i = index.parent().isValid()?index.parent():index;
    QTreeView *tree = ui->treeView;
    tree->collapseAll();
    tree->expand(i);
    QString name = (((QStandardItemModel*)i.model())->itemFromIndex(i))->text();
    currentGroup = Memory::getGroup(name);
    displayGroup();


}

void Gui::displayGroup(){
    QScrollArea *sarea = ui->scrollArea;
    cleanLayout(sarea->widget()->layout());
    //if no group is about to be displayed, only cleaning was required
    if (currentGroup == NULL)return;
    //sorted based on number of fingers
    foreach(Gesture *g,currentGroup->getSortedGestures()){
        //creating gestures frames inside the scroll area
        Button *b = new Button(this);
        b->setGesture(g);
        b->bLabel.gesture->setText(Lists::toString(g->getType()));
        b->bLabel.fingers->setText(QString::number(g->getFingers()));
        b->bLabel.direction->setText(Lists::toString(g->getDirection()));
        b->bLabel.layout->addWidget(new QLabel(tr("Action:")),0,0);
        b->bLabel.action = new QLabel(Lists::toString(g->getAction()->getType()));
        b->bLabel.layout->addWidget(b->bLabel.action,0,1);
        int count = 1;
        foreach(QString s, g->getAction()->getParamKeys()){
            b->bLabel.layout->addWidget(new QLabel(s),count,0);
            QString tmp = g->getAction()->getParamValue(s);
            if (!tmp.isEmpty())b->bLabel.layout->addWidget(new QLabel(tmp),count,1);
            else b->bLabel.layout->addItem(new QSpacerItem(10, 10, QSizePolicy::Ignored, QSizePolicy::Expanding),count,1);
            count++;
        }
        //just for a better view, adding spaces inside empty cells
        for (;count < 4;count++){
            b->bLabel.layout->addItem(new QSpacerItem(10, 10, QSizePolicy::Ignored, QSizePolicy::Expanding),count,0);
            b->bLabel.layout->addItem(new QSpacerItem(10, 10, QSizePolicy::Ignored, QSizePolicy::Expanding),count,1);
        }
        sarea->widget()->layout()->addWidget(b);
    }

    //once a group is selected, you can add gests
    QPushButton *addGesture = ui->addGesture;
    addGesture->setEnabled(true);
}

void Gui::cleanLayout(QLayout* l){
    QLayoutItem *wItem;
    while ((wItem = l->takeAt(0)) != 0){
        wItem->widget()->deleteLater();
        delete wItem;
    }

    QPushButton *addGesture = ui->addGesture;
    //no group selected, no new gests!
    addGesture->setEnabled(false);
}

void Gui::on_pushButton_5_clicked()
{
    //loading provided file
    loadFile("ress:default.conf");
}

void Gui::editDialogFinished(Gesture *gesture){
    //called on edit or new gesture complete
    if (gesture){
        currentGroup->removeGesture(gesture->getFingers(),
                                             gesture->getType(),
                                             gesture->getDirection());
        currentGroup->addGest(gesture);
    }
    //to make changes appears, it will reset scroll bar position, though
    //maybe I'll add a backup for it
    displayGroup();
}

void Gui::gestureDeleted(Gesture *gesture){
    //called on edit or new gesture complete
    if (gesture){
        currentGroup->removeGesture(gesture->getFingers(),
                                             gesture->getType(),
                                             gesture->getDirection());
    }
    //to make changes appears, it will reset scroll bar position, though
    //maybe I'll add a backup for it
    displayGroup();
}

void Gui::groupMoved(QStandardItem *item){
    if (item->parent() == NULL){
        //if parent is null, an application is to be moved to a new group
        inheritGroup = Memory::getApp(item->text())->getGroup();
        QString group = Memory::addGroup(item->text());
        newGroup = Memory::getGroup(group);
        Memory::getApp(item->text())->changeGroup(group);
        //you sould want to keep old settings, though
        QMessageBox *conf = new QMessageBox(QMessageBox::Question,
                                            QString(tr("New group")),
                                            QString(tr("Moving an application to a new group,\ninherit old group gestures?")),
                                            QMessageBox::Yes|QMessageBox::Cancel);
        QObject::connect(conf,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(inheritGestures(QAbstractButton*)));
        conf->show();
        refreshGroupTree();
    }//if is moved to an existing group, nothing is really needed but changing the application pointer to the group
    else Memory::getApp(item->text())->changeGroup(item->parent()->text());
}

void Gui::refreshGroupTree(){

    QTreeView *tree = ui->treeView;
    if(tree->model()->hasChildren()){
        tree->model()->removeRows(0, tree->model()->rowCount());
    }
    if (!Memory::getGroupsNames().isEmpty())
        foreach(QString key, Memory::getGroupsNames()){
            QStandardItem *group = new QStandardItem(key);
            group->setEditable(false); //no renaming! group names can't be saved, so no reason for that.
            group->setDragEnabled(false);//groups have no reason to be moved, just expose to buggs.
            foreach(QString part, Memory::getGroup(key)->getAppsNames()){
                if(key != tr("All")){ //All group have no reason to own specific applications
                    QStandardItem *item = new QStandardItem(part);
                    item->setEditable(false); //well maybe someone could find it convenient to rename apps, I'll think about that another time
                    item->setDragEnabled(true); //apps can be moved
                    item->setDropEnabled(false); //apps can't own anything
                    group->appendRow(item);
                }
                else group->setDropEnabled(false); //no purpose on moving apps to All, just delete them
            }
            model->appendRow(group);
        }
}

void Gui::pushButton7Clicked()
{
    //Add gesture button trigger
    EditDialog *a = new EditDialog(this);
    a->open();
    a->b = NULL;
    a->setUp(true);
}

    //Save button trigger
void Gui::on_saveButton_clicked()
{
    Scribe scribe;
    if(scribe.open(getPath()))
        scribe.save();
}

    //Add gesture button trigger (Hell, one of those two should be in 'trash [see below]' checking it later)
void Gui::on_addGesture_clicked()
{
    EditDialog *a = new EditDialog(this);
    a->open();
    a->b = NULL;
    a->setUp(true);
}

    //inherit dialog confirmation handler
void Gui::inheritGestures(QAbstractButton *button){
    if (button->text() != "&Yes")return;
    foreach(Gesture *ges, inheritGroup->getGests())
        newGroup->addGest(new Gesture(ges));
}

void Gui::setLanguage(int indx)
{
    ui->langBox->setCurrentIndex(indx);
}

void Gui::setLanguageList(QStringList langs)
{
    ui->langBox->clear();
    ui->langBox->addItems(langs);
}

    //Add group button trigger
void Gui::on_pushButton_2_clicked()
{
    NewGroupDialog *ngDialog = new NewGroupDialog(this);
    ngDialog->open();
    connect(ngDialog, SIGNAL(done()), this, SLOT(newGroupAccepted()));
}

//add group dialog terminated (the dialog will handle the memory changes)
void Gui::newGroupAccepted(){
    refreshGroupTree();
}

//remove button trigger
void Gui::on_pushButton_clicked()
{
    QTreeView *tree = ui->treeView;
    if (!tree->currentIndex().isValid())return;
    QModelIndex i = tree->currentIndex();
    QString name = (((QStandardItemModel*)i.model())->itemFromIndex(i))->text();
    if (Memory::getAppsNames().contains(name) && name != tr("All"))
        //that's for app remove
        Memory::removeApp(name);
    else{
        //that's for group remove
        Memory::removeGroup(name);
        //this could be unnecessary in rare cases (selecting the group with keyboard)
        //but, honestly, who is going to do that? (well well well... nice things you find commenting... I'll fix it later)
        currentGroup = NULL;
        displayGroup();
    }
    refreshGroupTree();
}




//   ***TRASH*** can't figure out how to remove them without causing Qt going mad
void Gui::langCombo_textChanged(const QString &/*arg1*/)
{
}

void Gui::pushButton4Clicked()
{
}

void Gui::langCombo_currentIndexChanged(const QString &/*arg1*/)
{
  //  dic->setLanguage(arg1);
}

void Gui::horizontalSlider_sliderMoved(int /*position*/)
{
}

void Gui::buttonBoxAccepted()
{
}

void Gui::buttonBoxRejected()
{
}

void Gui::on_scrollArea_destroyed()
{

}

void Gui::on_cgt_sliderMoved(int /*position*/)
{}


void Gui::on_treeView_doubleClicked(const QModelIndex &/*index*/)
{
}


void Gui::on_langBox_currentIndexChanged(const QString &arg1)
{
    if (isHidden())return;
    //TODO
    //emit languageChanged(arg1);

    //WORKARROUND
    QSettings conf("touchegg-gce");
    conf.setValue("Locale/Language",arg1);
    conf.sync();
    if (conf.status() == QSettings::NoError)
        QMessageBox::information(this,"Restart Required","Please restart the application to apply language selection.\nThis will be hopefuly fixed in  future releases.");
    else
        QMessageBox::warning(this,"Config Error",QString("Cannot write into the configuration file.\n%1").arg(conf.fileName()));
}

void Gui::on_openChooser_clicked()
{
    filePath = QFileDialog::getOpenFileName(this,tr("Select Configuration File"),ui->filePath->text(),tr("Configuration Files (*.conf);;All Files (*.*)"));
    ui->filePath->setText(filePath);
}

void Gui::on_saveChooser_clicked()
{
    QString ret = QFileDialog::getSaveFileName(this,tr("Select Configuration File"),filePath,tr("Configuration Files (*.conf);;All Files (*.*)"));
    if (ret.isNull()) return;
    filePath = ret;
    ui->filePath->setText(filePath);
    Scribe scribe;
    if(scribe.open(getPath()))
        scribe.save();
}

void Gui::on_savePath_toggled(bool checked)
{
    QSettings settings("touchegg-gce");
    if (checked)
        settings.setValue("filePath",filePath);
    else if (settings.value("filePath") == filePath)
        settings.remove("filePath");
}

void Gui::on_filePath_textChanged(const QString &arg1)
{
    QSettings settings("touchegg-gce");
    if (settings.value("filePath").toString() == arg1)
        ui->savePath->setChecked(true);
    else ui->savePath->setChecked(false);
}
