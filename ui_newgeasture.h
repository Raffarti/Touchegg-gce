/********************************************************************************
** Form generated from reading UI file 'newgeasture.ui'
**
** Created: Thu 4. Oct 10:21:47 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGEASTURE_H
#define UI_NEWGEASTURE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewGeasture
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QSpinBox *spinBox;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *actionList;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewGeasture)
    {
        if (NewGeasture->objectName().isEmpty())
            NewGeasture->setObjectName(QString::fromUtf8("NewGeasture"));
        NewGeasture->resize(400, 300);
        gridLayout = new QGridLayout(NewGeasture);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(NewGeasture);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(NewGeasture);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(NewGeasture);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        comboBox = new QComboBox(NewGeasture);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox);

        spinBox = new QSpinBox(NewGeasture);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBox);

        comboBox_2 = new QComboBox(NewGeasture);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBox_2);


        verticalLayout_2->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(NewGeasture);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_4);

        actionList = new QComboBox(NewGeasture);
        actionList->setObjectName(QString::fromUtf8("actionList"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(actionList->sizePolicy().hasHeightForWidth());
        actionList->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(actionList);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(NewGeasture);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 0, 2, 1, 1);


        retranslateUi(NewGeasture);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewGeasture, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewGeasture, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewGeasture);
    } // setupUi

    void retranslateUi(QDialog *NewGeasture)
    {
        NewGeasture->setWindowTitle(QApplication::translate("NewGeasture", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewGeasture", "Fingers:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewGeasture", "Gesture:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewGeasture", "Direction:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewGeasture", "Action:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewGeasture: public Ui_NewGeasture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGEASTURE_H
