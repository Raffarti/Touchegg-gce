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

#ifndef BUTTON_H
#define BUTTON_H

#include "gui.h"
#include "general.h"

class QLabel;
class QGridLayout;

namespace Ui {
class button;
}

class Button : public QWidget
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

    explicit Button(QWidget *parent = 0);
    ~Button();

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

    void on_pushButton_3_clicked();

private:

    Gesture *gesture;
    Ui::button *ui;
};

#endif // BUTTON_H
