#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QChar>
#include <QHash>
#include <QStringList>
#include "general.h"
#include <QTextCodec>
#include <QTextStream>

class Parser{

public:

    struct error{
        QString msg;
        QChar ch;
        int line;
        int pos;
    } error;

    typedef struct{
        int num;
        QString type;
        QString direction;
    }gesture;



    Parser(QString file);

    ~Parser();

    int init();

    void close();

    bool loadAll();

private:
    QString appKey;

    gesture *ges;

    QChar peeked;

    QStringList state;

    QTextStream *in;

    QFile *input;

    QChar peek();

    QChar poll();

    void eat(QString s);

    QString getVarName();
    QString getParam();
    int getInt();
    QString getString();

    void throwError();

    void sStart();

    void sTouchegg();

    void sSettings();

    void sProperty(QString key);

    void sApplication();

    void sGesture();

    void sAction(Action *act);
};

#endif // PARSER_H
