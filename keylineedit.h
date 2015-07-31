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

#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QLineEdit>

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
