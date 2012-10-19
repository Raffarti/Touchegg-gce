#ifndef NEWGROUPDIALOG_H
#define NEWGROUPDIALOG_H

#include <QDialog>
#include "general.h"

namespace Ui {
class NewGroupDialog;
}

class NewGroupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewGroupDialog(QWidget *parent = 0);
    ~NewGroupDialog();
    
private slots:
    void on_NewGroupDialog_accepted();

    void on_buttonBox_accepted();

    void on_targetCombo_currentIndexChanged(int index);

signals:
    void done();
private:
    Ui::NewGroupDialog *ui;
};

#endif // NEWGROUPDIALOG_H
