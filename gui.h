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

#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

class Parser;
class QStandardItem;
class Gesture;
class QAbstractButton;
class QLineEdit;
class QStandardItemModel;
class QFrame;
class QSlider;
class Group;
class QModelIndex;

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit Gui(QWidget *parent = 0);
    ~Gui();

public slots:

    /**
     * @brief groupMoved
     *Used to keep synchronized memory and group tree
     * @param item
     *the group moved.
     */
    void groupMoved(QStandardItem *item);

    /**
     * @brief editDialogFinished
     *totally override (if exists) the old gesture with the newly created
     * @param gesture
     */
    void editDialogFinished(Gesture *gesture);
    /**
     * @brief gestureDeleted
     *delete a gesture
     * @param gesture
     */
    void gestureDeleted(Gesture *gesture);

    /**
     * @brief inheritGestures
     *clone gestures from the native group if &yes is pressed
     * @param button
     */
    void inheritGestures(QAbstractButton *button);

    /**
     * @brief setLanguage
     * change the language displayed by langBox
     * @param indx language index
     */
    void setLanguage(int indx);

    /**
     * @brief setLanguageList
     * set the language lst displayed by langBox
     * @param langs language list to be displayed
     */
    void setLanguageList(QStringList langs);

    void newGroupAccepted();
private slots:

    void buttonBoxAccepted();

    void on_filePath_textEdited(const QString &arg1);

    void buttonBoxRejected();

    void on_scrollArea_destroyed();

    void on_checkBox_toggled(bool checked);

    void horizontalSlider_sliderMoved(int position);

    void on_cgt_sliderMoved(int position);

    void on_cgt_valueChanged(int value);

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void pushButton7Clicked();

    void pushButton4Clicked();

    void on_saveButton_clicked();

    void on_addGesture_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void langCombo_textChanged(const QString &arg1);

    void langCombo_currentIndexChanged(const QString &arg1);

    void on_langBox_currentIndexChanged(const QString &arg1);

    void on_openChooser_clicked();
    
    void on_saveChooser_clicked();

    void on_savePath_toggled(bool checked);

    void on_filePath_textChanged(const QString &arg1);

signals:

    /**
     * @brief languageChanged
     * emitted by langBox changes
     * @param lang
     */
    void languageChanged(QString lang);

private:


   // Dictionary *dic;
    Ui::Gui *ui;
    Parser *parser;
    QString filePath;
    QLineEdit *linePath;
    QStandardItemModel *model;
    QFrame *adv;
    QSlider *slider;
    void cleanLayout(QLayout *l);
    void loadFile(QString path);
    Group *currentGroup;
    Group *inheritGroup;
    Group *newGroup;

    QString getPath();

    void displayGroup();
    void refreshGroupTree();
};

#endif // GUI_H
