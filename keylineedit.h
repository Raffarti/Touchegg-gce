#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class KeyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit KeyLineEdit(QWidget *parent = 0);
    
signals:
    void keyCatched(QString key);
public slots:

private:
    bool event(QEvent *event);
};

#endif // KEYLINEEDIT_H
