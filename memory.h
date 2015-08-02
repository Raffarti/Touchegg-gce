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

#ifndef MEMORY_H
#define MEMORY_H
#include <QStringList>
#include <QHash>
#include "general.h"

class Action;
class Gesture;
class Group;
class App;

typedef QHash<QString,QString> type_paramsHash;
typedef QHash<QString,QString> type_propsHash;

class Memory:  public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = 0);

    static QString addGroup(QString apps);
    static Group* getGroup(QString name);
    static QStringList getGroupsNames();
    static QList<Group*> getGroups();
    static void removeGroup(QString name);

    static void addProp(QString name, QString value);
    static QString getProp(QString name);
    static QStringList getProps();
    static void removeProp(QString name);

    static void addApp(QString name, QString group);
    static void addApp(QString name);
    static App* getApp(QString name);
    static QStringList getAppsNames();
    static QList<App*> getApps();
    static void removeApp(QString name);
private:
    static QStringList groupsList;
    static QStringList propsList;
    static QStringList appsList;
    static QHash<QString, App*> *appsHash;
    static QHash<QString, Group*> *groupsHash;
    static type_propsHash *propsHash;
    static int groupCounter;

};

class Group{
public:
    Group(QString name);
    QString getName();

    void addApp(QString name);
    void addApps(QString names);
    App *getApp(QString name);
    QStringList getAppsNames();
    QList<App*> getApps();
  //void removeApp(QString name);

    void addGest(int fingers, Lists::GestureType type, Lists::GestureDirection direction);
    void addGest(Gesture *gesture);
    Gesture *getGest(int fingers, Lists::GestureType type, Lists::GestureDirection direction);
    QList<Gesture*> getGests();
    QList<Gesture*> getSortedGestures();
    void removeGesture(int fingers, Lists::GestureType type, Lists::GestureDirection direction);
    void removeGesture(Gesture gest);

private:
    QString name;
    QStringList gestsList;
    QHash<QString, Gesture*> *gestsHash;
};

class App{
public:
    App(QString name);
    App(QString name, Group *group);
    App(QString name, QString group);
    QString getName();
    Group* getGroup();
    void changeGroup(QString name);
    void changeGroup(Group *group);

private:
    Group *group;
    QString name;
};

class Gesture{
public:

    operator QString (){
        return toString();
    }

    Gesture(int fingers, Lists::GestureType type, Lists::GestureDirection direction, Group *parent);
    Gesture(Gesture *ges);
    void destroy();
    int getFingers();
    Lists::GestureType getType();
    Lists::GestureDirection getDirection();
    void setGroup(Group *group);

    void setAction(Lists::ActionType type);
    void setAction(Action *act);
    Action* getAction();
    void removeAction();
    QString toString();

private:
    Group *parent;
    int fingers;
    Lists::GestureType type;
    Lists::GestureDirection direction;
    Action *act;
};

class Action{
public:
    Action(Lists::ActionType type);
    Action(Action *act);
    void addParam(QString name, QString value);
    void addParam(QString name);
    Lists::ActionType getType();
    QStringList getParamKeys();
    QString getParamValue(QString key);
    void removeParam(QString name);
    void changeParamValue(QString name, QString value);

private:
    Lists::ActionType type;
    QStringList paramsList;
    type_paramsHash *parHash;
};

#endif // MEMORY_H
