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
