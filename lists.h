#ifndef LISTS_H
#define LISTS_H

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

    static QStringList* actionList();
    static QStringList* gestureTypes();
    static QStringList* gestureDirections(GestureType type);
    static QString* toString(GestureType t);
    static QString* toString(GestureDirection t);
    static QString* toString(ActionType t);
    static QString* printTag(GestureType t);
    static QString* printTag(GestureDirection t);
    static QString* printTag(ActionType t);
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
