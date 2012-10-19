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
    bool open(QString name, int flag = 0);
    void save();
private:
    QFile *file;
public slots:
    void creationConfirmed(QAbstractButton *button);
    void folderCreationConfirmed(QAbstractButton *button);
    void restartTouchegg(QAbstractButton *button);
};

#endif // SCRIBE_H
