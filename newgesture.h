#ifndef NEWGESTURE_H
#define NEWGESTURE_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class NewGesture;
}

class NewGesture : public QDialog
{
    Q_OBJECT
    
public:
    QComboBox *actionList;
    explicit NewGesture(QWidget *parent = 0);
    ~NewGesture();
    
private:
    Ui::NewGesture *ui;
};

#endif // NEWGEASTURE_H
