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

#ifndef LISTS_H
#define LISTS_H

#include <QObject>
#include <QStringList>
class Lists :  public QObject
{
    Q_OBJECT
public:

    enum GestureDirection {
        NO_DIRECTION,
        ALL,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        IN,
        OUT
    };

    enum ActionType {
        NO_ACTION,
        MOUSE_CLICK,
        SCROLL,
        MINIMIZE_WINDOW,
        MAXIMIZE_RESTORE_WINDOW,
        CLOSE_WINDOW,
        RESIZE_WINDOW,
        SHOW_DESKTOP,
        CHANGE_DESKTOP,
        CHANGE_VIEWPORT,
        SEND_KEYS,
        MOVE_WINDOW,
        RUN_COMMAND,
        DRAG_AND_DROP
    };

    enum GestureType {
        TAP,
        DRAG,
        PINCH,
        ROTATE,
        TAP_AND_HOLD,
        DOUBLE_TAP
    };

    explicit Lists(QObject *parent = 0);

    static QStringList actionList();
    static QStringList gestureTypes();
    static QStringList gestureDirections(GestureType type);
    static QString toString(GestureType t);
    static QString toString(GestureDirection t);
    static QString toString(ActionType t);
    static QString printTag(GestureType t);
    static QString printTag(GestureDirection t);
    static QString printTag(ActionType t);
    static ActionType toAT(QString s);
    static GestureType toGT(QString s);
    static GestureDirection toGD(QString s);
    static ActionType aT(QString s);
    static GestureType gT(QString s);
    static GestureDirection gD(QString s);
    static bool got(GestureType type, GestureDirection dir);
    static QString trnAT(QString s);
    static QString trnGT(QString s);
    static QString trnGD(QString s);
signals:

};

#endif // LISTS_H
