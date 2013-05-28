#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include "button.h"
#include "general.h"
#include <QCheckBox>
#include "sendkeys.h"


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
    button *b;
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
     * @brief on_buttonBox_rejected
     *Simply exit without any change to memory.
     */
    void on_buttonBox_rejected();

    /**
     * @brief on_buttonBox_accepted
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
