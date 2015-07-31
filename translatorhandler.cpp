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

#include "translatorhandler.h"
#include <QLocale>
#include <QTranslator>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include "settings.h"

TranslatorHandler * TranslatorHandler::m_instance = nullptr;

TranslatorHandler::TranslatorHandler(QString path, QString name, QObject *parent) :
    QObject(parent), m_path(path)
{
    if (!name.isEmpty()) load(name);
    else load("Default");
    m_dicts = QDir(path).entryList(QStringList("[A-Z][A-Z]*.qm"), QDir::Files).replaceInStrings(".qm","");
}

TranslatorHandler *TranslatorHandler::instance(QString path, QString name, QObject *parent)
{
    if (!m_instance)
        m_instance = new TranslatorHandler(path, name, parent);

    return m_instance;
}

void TranslatorHandler::load(QString name)
{
    qDebug() << "Changing language to" << name;
    QTranslator *t = new QTranslator();
    if (name == "Default") t->load(QLocale::system(),"","",m_path);
    else t->load(name,m_path);
    if (t->isEmpty()){
        qWarning() << QString("Failed to load \"%1\" translation.").arg(name);
        return;
    }
    if (m_current){
        QApplication::instance()->removeTranslator(m_current);
        delete m_current;
    }
    m_current = t;
    QApplication::instance()->installTranslator(m_current);
    m_lang = name;
    Settings::instance()->set_Locale_language(m_lang);
    qDebug() << QString("\"%1\" translation loaded.").arg(m_lang);
}

int TranslatorHandler::current()
{
    return m_dicts.indexOf(m_lang);
}

QStringList TranslatorHandler::dicts()
{
    return m_dicts << "Default";
}

