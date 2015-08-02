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

#include <QHash>
#include <QStringList>
#include "general.h"
#include <QXmlStreamReader>

class Parser{

public:


    typedef struct{
        int num;
        QString type;
        QString direction;
    }gesture;



    Parser(QIODevice *dev);

    ~Parser();

    bool loadAll();

private:
    typedef struct error{
        error(const QXmlStreamReader &reader, const QString & emsg){
            pos = reader.columnNumber();
            line = reader.lineNumber();
            msg = emsg;
        }

        QString msg;
        int line;
        int pos;
    } error;

    QXmlStreamReader m_reader;

    QString appKey;

    gesture *ges;

    QStringList state;

    void sStart();

    void sTouchegg();

    void sSettings();

    void sProperty(QString key);

    void sApplication();

    void sGesture();

    error err(const QString &msg);

};

#endif // PARSER_H
