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
#include "ui_gui.h"
#include "button.h"
#include "ui_button.h"
#include "editdialog.h"
#include <QDir>

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);

    filePath = new QString("~/.config/touchegg/touchegg.conf");
    linePath = findChild<QLineEdit*>(QString("filePath"));
    QScrollArea *sarea = findChild<QScrollArea*>("scrollArea");

    //scroll area for gesture list
    QWidget *wsa = new QWidget();
    wsa->setLayout(new QVBoxLayout(sarea));
    wsa->layout()->setSizeConstraint(QLayout::SetFixedSize);
    sarea->setWidget(wsa);

    //tree for applications
    QTreeView *tree = findChild<QTreeView*>("treeView");
    model = new QStandardItemModel(tree);
    adv = findChild<QFrame*>("advFrame");
    adv->hide();
    tree->setModel(new QStandardItemModel());
    tree->setModel(model);
    //connecting tree with data struct
    connect(model, SIGNAL(itemChanged(QStandardItem*)),this, SLOT(groupMoved(QStandardItem* )));

    //composed gesture slider
    slider = findChild<QSlider*>("cgt");
}

Gui::~Gui()
{
    delete ui;
}

QString Gui::getPath(){
    QString ret = *filePath;
    //parsing standard home notation
    if (ret.startsWith(QChar('~'))){
        ret.remove(0,1);
        ret.prepend(QDir::homePath());
    }
    //is the path is a directory, adding touchegg.conf as file by default
    if (QDir(ret).exists()){
        if (ret.endsWith(QChar('/')))
            ret.append(QString("touchegg.conf"));
        else
            ret.append(QString("/touchegg.conf"));
    }
    return ret;
}

void Gui::loadFile(QString path){
    parser = new Parser(path);
    if (!parser->init()) return;
    if (!parser->loadAll())return;

    //enable componentss requiring a memory loaded.
    findChild<QPushButton*>("pushButton")->setEnabled(true);
    findChild<QPushButton*>("pushButton_2")->setEnabled(true);
    QPushButton *saveButton = findChild<QPushButton*>("saveButton");
    saveButton->setEnabled(true);

    QScrollArea *sarea = findChild<QScrollArea*>("scrollArea");
    //clear gesture list
    cleanLayout(sarea->widget()->layout());
    //clear tree view and add application found in data struct memory
    refreshGroupTree();
    //setting props (only gesture time present atm)
    foreach(QString key, *Memory::getProps()){
        if (key == "composed_gestures_time"){
            slider->setEnabled(true);
            slider->setValue(Memory::getProp(key).toInt());
        }
    }
}



void Gui::on_filePath_textEdited(const QString &arg1)
{
    //update filePath on gui request
    filePath = new QString(arg1);
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
    findChild<QLabel*>("sliderValue")->setText(QString(tr("Value: ")).append(QString::number(value)).append("ms"));
    Memory::removeProp("composed_gestures_time");
    Memory::addProp("composed_gestures_time",QString::number(value));
}


void Gui::on_pushButton_6_clicked()
{
    //reset path button
    linePath->setText("~/.config/touchegg/");
    filePath = new QString("~/.config/touchegg/");
}

void Gui::on_pushButton_3_clicked()
{

    //Load button trigger
    qDebug(filePath->toLatin1());
    loadFile(getPath());
}

void Gui::on_treeView_clicked(const QModelIndex &index)
{

    //display gesture list on user tree interaction
    QModelIndex i;
    i = index.parent().isValid()?index.parent():index;
    QTreeView *tree = findChild<QTreeView*>("treeView");
    tree->collapseAll();
    tree->expand(i);
    QString name = (((QStandardItemModel*)i.model())->itemFromIndex(i))->text();
    currentGroup = Memory::getGroup(name);
    displayGroup();


}

void Gui::displayGroup(){
    QScrollArea *sarea = findChild<QScrollArea*>("scrollArea");
    cleanLayout(sarea->widget()->layout());
    //if no group is about to be displayed, only cleaning was required
    if (currentGroup == NULL)return;
    //sorted based on number of fingers
    foreach(Gesture *g,currentGroup->getSortedGestures()){
        //creating gestures frames inside the scroll area
        button *b = new button(this);
        b->setGesture(g);
        b->bLabel.gesture->setText(*Lists::toString(g->getType()));
        b->bLabel.fingers->setText(QString::number(g->getFingers()));
        b->bLabel.direction->setText(*Lists::toString(g->getDirection()));
        b->bLabel.layout->addWidget(new QLabel(tr("Action:")),0,0);
        b->bLabel.action = new QLabel(*Lists::toString(g->getAction()->getType()));
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
    QPushButton *addGesture = findChild<QPushButton*>("addGesture");
    addGesture->setEnabled(true);
}

void Gui::cleanLayout(QLayout* l){
    QLayoutItem *wItem;
    while ((wItem = l->takeAt(0)) != 0){
        wItem->widget()->deleteLater();
        delete wItem;
    }

    QPushButton *addGesture = findChild<QPushButton*>("addGesture");
    //no group selected, no new gests!
    addGesture->setEnabled(false);
}

void Gui::on_pushButton_5_clicked()
{
    //loading provided file
    loadFile("./default.conf");
}

void Gui::on_editDialog_done(Gesture *gesture){
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

    QTreeView *tree = findChild<QTreeView*>("treeView");
    if(tree->model()->hasChildren()){
        tree->model()->removeRows(0, tree->model()->rowCount());
    }
    foreach(QString key, *Memory::getGroupsNames()){
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

void Gui::on_pushButton_7_clicked()
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
    Scribe *scribe = new Scribe();
    if(scribe->open(getPath()))
        scribe->save();
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
    QTreeView *tree = findChild<QTreeView*>("treeView");
    if (!tree->currentIndex().isValid())return;
    QModelIndex i = tree->currentIndex();
    QString name = (((QStandardItemModel*)i.model())->itemFromIndex(i))->text();
    if (Memory::getAppsNames()->contains(name) && name != tr("All"))
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
void Gui::on_langCombo_textChanged(const QString &/*arg1*/)
{
}

void Gui::on_pushButton_4_clicked()
{
}

void Gui::on_langCombo_currentIndexChanged(const QString &/*arg1*/)
{
  //  dic->setLanguage(arg1);
}

void Gui::on_horizontalSlider_sliderMoved(int /*position*/)
{
}

void Gui::on_buttonBox_accepted()
{
}

void Gui::on_buttonBox_rejected()
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
