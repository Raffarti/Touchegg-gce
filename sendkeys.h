#ifndef SENDKEYS_H
#define SENDKEYS_H

#include <QFrame>
#include "ui_sendkeys.h"

namespace Ui {
class SendKeys;
}

class SendKeys : public QFrame
{
    Q_OBJECT
    
public:
    explicit SendKeys(QWidget *parent = 0);
    ~SendKeys();

    void setKeys(QString keys);

    QString getKeys();
    
private slots:
    void on_keyBox_textChanged(const QString &arg1);

    void on_keyBox_textEdited(const QString &arg1);

    void on_keyBox_keyCatched(const QString &text);

    void on_pushButton_clicked();

private:
    Ui::SendKeys *ui;

    QCheckBox *superBox;
    QCheckBox *ctrlBox;
    QCheckBox *altBox;
    QCheckBox *altGrBox;
    QCheckBox *shiftBox;
    QLineEdit *keyBox;
};

#endif // SENDKEYS_H
