#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include "parser.h"
#include <QStandardItemModel>
#include <QGridLayout>
#include <QSlider>
#include <QObjectList>
#include <QBoxLayout>
#include "general.h"
#include "scribe.h"
#include "newgroupdialog.h"

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit Gui(QWidget *parent = 0);
    ~Gui();

public slots:

    /**
     * @brief groupMoved
     *Used to keep synchronized memory and group tree
     * @param item
     *the group moved.
     */
    void groupMoved(QStandardItem *item);

    /**
     * @brief on_editDialog_done
     *totally override (if exists) the old gesture with the newly created
     * @param gesture
     */
    void on_editDialog_done(Gesture *gesture);

    /**
     * @brief inheritGestures
     *clone gestures from the native group if &yes is pressed
     * @param button
     */
    void inheritGestures(QAbstractButton *button);

    void newGroupAccepted();
private slots:

    void on_buttonBox_accepted();

    void on_filePath_textEdited(const QString &arg1);

    void on_buttonBox_rejected();

    void on_scrollArea_destroyed();

    void on_checkBox_toggled(bool checked);

    void on_horizontalSlider_sliderMoved(int position);

    void on_cgt_sliderMoved(int position);

    void on_cgt_valueChanged(int value);

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_saveButton_clicked();

    void on_addGesture_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_langCombo_textChanged(const QString &arg1);

    void on_langCombo_currentIndexChanged(const QString &arg1);

private:


   // Dictionary *dic;
    Ui::Gui *ui;
    Parser *parser;
    QString *filePath;
    QLineEdit *linePath;
    QStandardItemModel *model;
    QFrame *adv;
    QSlider *slider;
    void cleanLayout(QLayout *l);
    void loadFile(QString path);
    Group *currentGroup;
    Group *inheritGroup;
    Group *newGroup;

    QString getPath();

    void displayGroup();
    void refreshGroupTree();
};

#endif // GUI_H
