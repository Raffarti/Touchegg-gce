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

#ifndef SCRIBE_H
#define SCRIBE_H

#include "general.h"
#include <QMessageBox>
#include <QFile>
#include <QDialogButtonBox>
#include <QAbstractButton>

class Scribe : public QObject
{
    Q_OBJECT
public:
    explicit Scribe(QObject *parent = 0);
    bool open(const QString &path);
    void save();
private:
    QFile *file;
public slots:
    void restartTouchegg(QAbstractButton *button);
};

#endif // SCRIBE_H
