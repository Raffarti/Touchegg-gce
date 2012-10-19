#ifndef BUTTON_H
#define BUTTON_H

#include "gui.h"
#include "general.h"

namespace Ui {
class button;
}

class button : public QWidget
{
    Q_OBJECT
    
public:
    /**
     *Stuct used by some classes to quickly access some
     *fields in the gesture list without a findchild.
     * @brief The bLabel struct
     */
    struct bLabel{
        QLabel *gesture;
        QLabel *fingers;
        QLabel *direction;
        QLabel *action;
        QGridLayout *layout;
    }bLabel;

    explicit button(QWidget *parent = 0);
    ~button();

    /**
     *
     * @brief setGesture Needed to keep a link between
     *          data struct and interface.
     * @param gesture set the gesture related to this bottom.
     */
    void setGesture(Gesture *gesture);

    /**
     * @brief getGesture get the referece to the gesture
     *          related to this interface.
     * @return the referece to the gesture
     *          related to this interface.
     */
    Gesture* getGesture();
    
private slots:

    /**
     * @brief on_pushButton_2_clicked
     *Create the edit dialog of a gesture
     */
    void on_pushButton_2_clicked();
    /**
     * @brief on_pushButton_clicked
     *Remove the gesture
     */
    void on_pushButton_clicked();

private:

    Gesture *gesture;
    Ui::button *ui;
};

#endif // BUTTON_H
