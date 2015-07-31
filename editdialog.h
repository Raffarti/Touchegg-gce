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

#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

class Gesture;
class QComboBox;
class QSpinBox;
class QCheckBox;
class Button;


namespace Ui {
class EditDialog;
}
/**
 * @brief The EditDialog class
 *This class is an interface to edit
 *existing gestures or create new ones.
 */
class EditDialog : public QDialog
{
    Q_OBJECT
    
signals:
    /**
     * @brief done
     *send a signal with the reference of the new gesture.
     *If an existing gesture was edited instead, gesture will be NULL.
     * @param gesture
     */
    void done(Gesture *gesture = 0);
    /**
     * @brief done
     *send a signal with the reference of the new gesture.
     *If an existing gesture was edited instead, gesture will be NULL.
     * @param gesture
     */
    void deleteGesture(Gesture *gesture);

public:
    /**
     * @brief b
     *reference to the calling button interface to
     *load the values of an existing gesture.
     *This is NULL if is a new gesture instead.
     */
    Button *b;
    /**
     * @brief actionList
     *Allow the user to select the action for the gesture.
     */
    QComboBox *actionList;
    /**
     * @brief EditDialog
     *costructors for edit a gesture or edit an existing one.
     * @param gesture if existing.
     * @param parent
     */
    explicit EditDialog(Gesture *gesture, QWidget *parent = 0);
    explicit EditDialog(QWidget *parent = 0);

    Gesture* getGesture();
    void setGesture(Gesture * gesture);

    ~EditDialog();

    /**
     * @brief setUp
     *initialize the starting values of the dialog components,
     *it loads the old ones for existing gestures.
     * @param fullEditable true is the gesture is a new one, to allow
     *the editing of gestures specific values (fingers, type and direction)
     *Action values are allways editable.
     */
    void setUp(bool fullEditable);
    
private slots:
    /**
     * @brief on_actionList_currentIndexChanged
     *Allow the selection of the gest action type.
     * @param arg1 the action type name.
     */
    void on_actionList_currentIndexChanged(const QString &arg1);

    /**
     * @brief buttonBoxRejected
     *Simply exit without any change to memory.
     */
    void on_buttonBox_rejected();

    /**
     * @brief buttonBoxAccepted
     *Apply the changes to memory.
     */
    void on_buttonBox_accepted();

    /**
     * @brief on_gesture_currentIndexChanged
     *When gesture type is changed, directions have to be refreshed.
     * @param arg1 the name of the new gesture type.
     */
    void on_gesture_currentIndexChanged(const QString &arg1);

private:
    /**
     * @brief gesture
     *reference in memory.
     */
    Gesture *gesture;
    /**
     * @brief cleanLayout
     *Used to clean action layout
     * @param l
     */
    void cleanLayout(QLayout* l);
    /**
     * @brief fingSpin ref to the spinner used to select the number of finges of the gesture.
     */
    QSpinBox *fingSpin;
    /**
     * @brief gesType ref to the combo box used to select the type of the gesture.
     */
    QComboBox *gesType;
    /**
     * @brief gesDirection ref to the combo box used to select the direction of the gesture.
     */
    QComboBox *gesDirection;
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
