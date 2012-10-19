#ifndef LANGSELECTOR_H
#define LANGSELECTOR_H

#include <QDir>

class LangSelector : public QObject
{
    Q_OBJECT
public:
    explicit LangSelector(QObject *parent = 0);
    int value;
signals:
    
public slots:
    void set(int val);
};

#endif // LANGSELECTOR_H
