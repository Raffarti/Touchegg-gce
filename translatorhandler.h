/**************************************************************************
 * Copyright (c) 2015 Raffaele Pertile <raffarti@zoho.com>
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

#ifndef TRANSLATORHANDLER_H
#define TRANSLATORHANDLER_H

#include <QObject>
#include <QStringList>

class QTranslator;

class TranslatorHandler : public QObject
{
    Q_OBJECT
public:
    static TranslatorHandler *instance(QString path = QString(), QString name = QString(), QObject *parent = 0);

    int current();
    QStringList dicts();

private:
    explicit TranslatorHandler(QString path = QString(), QString name = QString(), QObject *parent = 0);

    static TranslatorHandler *m_instance;
    QString m_path;
    QTranslator *m_current = nullptr;
    QString m_lang;
    QStringList m_dicts;

signals:
public slots:
    void load(QString name);
};

#endif // TRANSLATORHANDLER_H
