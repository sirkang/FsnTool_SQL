/********************************************************************************
** Form generated from reading UI file 'fsntool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FSNTOOL_H
#define UI_FSNTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FsnTool
{
public:
    QWidget *GUI;
    QGridLayout *gridLayout_2;
    QGridLayout *up;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_fsn_num;
    QLabel *label_3;
    QLabel *label_logo;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_fsnName;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QGridLayout *down;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_7;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLabel *label_fsnFileNumber;
    QVBoxLayout *verticalLayout_5;
    QListWidget *listWidget_fsn;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLineEdit *lineEdit_SNo;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QLineEdit *lineEdit_Valuta;
    QPushButton *pushButton_5;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QDateTimeEdit *dateTimeEdit_2;
    QDateTimeEdit *dateTimeEdit;
    QGridLayout *gridLayout_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QPushButton *pushButton_7;
    QCheckBox *checkBox_image;
    QPushButton *pushButton_11;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *FsnTool)
    {
        if (FsnTool->objectName().isEmpty())
            FsnTool->setObjectName(QStringLiteral("FsnTool"));
        FsnTool->resize(1000, 600);
        GUI = new QWidget(FsnTool);
        GUI->setObjectName(QStringLiteral("GUI"));
        gridLayout_2 = new QGridLayout(GUI);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        up = new QGridLayout();
        up->setObjectName(QStringLiteral("up"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        up->addLayout(verticalLayout_2, 0, 2, 1, 1);

        label_fsn_num = new QLabel(GUI);
        label_fsn_num->setObjectName(QStringLiteral("label_fsn_num"));

        up->addWidget(label_fsn_num, 0, 4, 1, 1);

        label_3 = new QLabel(GUI);
        label_3->setObjectName(QStringLiteral("label_3"));

        up->addWidget(label_3, 0, 3, 1, 1);

        label_logo = new QLabel(GUI);
        label_logo->setObjectName(QStringLiteral("label_logo"));

        up->addWidget(label_logo, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_fsnName = new QLineEdit(GUI);
        lineEdit_fsnName->setObjectName(QStringLiteral("lineEdit_fsnName"));

        gridLayout->addWidget(lineEdit_fsnName, 1, 2, 1, 1);

        pushButton_2 = new QPushButton(GUI);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 3, 1, 1);

        label_2 = new QLabel(GUI);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        label = new QLabel(GUI);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lineEdit = new QLineEdit(GUI);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 2);


        up->addLayout(gridLayout, 0, 1, 1, 1);


        gridLayout_2->addLayout(up, 0, 0, 1, 1);

        down = new QGridLayout();
        down->setSpacing(0);
        down->setObjectName(QStringLiteral("down"));
        down->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(GUI);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(6);
        gridLayout_7->setVerticalSpacing(0);
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setAutoFillBackground(false);

        gridLayout_7->addWidget(pushButton, 0, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_7);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        label_fsnFileNumber = new QLabel(groupBox);
        label_fsnFileNumber->setObjectName(QStringLiteral("label_fsnFileNumber"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label_fsnFileNumber);


        verticalLayout_7->addLayout(formLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        listWidget_fsn = new QListWidget(groupBox);
        listWidget_fsn->setObjectName(QStringLiteral("listWidget_fsn"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget_fsn->sizePolicy().hasHeightForWidth());
        listWidget_fsn->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(listWidget_fsn);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_9 = new QVBoxLayout(groupBox_2);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setEnabled(true);

        horizontalLayout_4->addWidget(label_7);

        lineEdit_SNo = new QLineEdit(groupBox_2);
        lineEdit_SNo->setObjectName(QStringLiteral("lineEdit_SNo"));

        horizontalLayout_4->addWidget(lineEdit_SNo);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);


        verticalLayout_9->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_5->addWidget(label_8);

        lineEdit_Valuta = new QLineEdit(groupBox_2);
        lineEdit_Valuta->setObjectName(QStringLiteral("lineEdit_Valuta"));

        horizontalLayout_5->addWidget(lineEdit_Valuta);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_5->addWidget(pushButton_5);


        verticalLayout_9->addLayout(horizontalLayout_5);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_6->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox_2);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_6->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(groupBox_2);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        horizontalLayout_6->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(groupBox_2);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        horizontalLayout_6->addWidget(checkBox_4);


        gridLayout_3->addLayout(horizontalLayout_6, 3, 0, 1, 3);

        dateTimeEdit_2 = new QDateTimeEdit(groupBox_2);
        dateTimeEdit_2->setObjectName(QStringLiteral("dateTimeEdit_2"));

        gridLayout_3->addWidget(dateTimeEdit_2, 5, 1, 1, 2);

        dateTimeEdit = new QDateTimeEdit(groupBox_2);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));

        gridLayout_3->addWidget(dateTimeEdit, 5, 0, 1, 1);


        verticalLayout_9->addLayout(gridLayout_3);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_6->addWidget(pushButton_4, 0, 0, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_6->addWidget(pushButton_6, 0, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout_6);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout_5->addWidget(pushButton_8, 0, 0, 1, 1);

        pushButton_10 = new QPushButton(groupBox_2);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout_5->addWidget(pushButton_10, 0, 1, 1, 1);

        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 1, 0, 1, 1);

        checkBox_image = new QCheckBox(groupBox_2);
        checkBox_image->setObjectName(QStringLiteral("checkBox_image"));
        checkBox_image->setLayoutDirection(Qt::LeftToRight);

        gridLayout_5->addWidget(checkBox_image, 1, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout_5);

        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 0, 0);"));

        verticalLayout_9->addWidget(pushButton_11);


        verticalLayout_5->addWidget(groupBox_2);


        verticalLayout_7->addLayout(verticalLayout_5);


        verticalLayout_4->addLayout(verticalLayout_7);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));

        verticalLayout_4->addLayout(gridLayout_4);


        verticalLayout_3->addLayout(verticalLayout_4);


        down->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(GUI);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(groupBox_3);
        if (tableWidget->columnCount() < 11)
            tableWidget->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        down->addWidget(groupBox_3, 0, 1, 1, 1);

        down->setColumnStretch(0, 2);
        down->setColumnStretch(1, 8);

        gridLayout_2->addLayout(down, 1, 0, 1, 1);

        FsnTool->setCentralWidget(GUI);
        QWidget::setTabOrder(pushButton_3, pushButton_2);
        QWidget::setTabOrder(pushButton_2, listWidget_fsn);
        QWidget::setTabOrder(listWidget_fsn, lineEdit_SNo);
        QWidget::setTabOrder(lineEdit_SNo, lineEdit_Valuta);
        QWidget::setTabOrder(lineEdit_Valuta, pushButton_5);
        QWidget::setTabOrder(pushButton_5, lineEdit);
        QWidget::setTabOrder(lineEdit, checkBox);
        QWidget::setTabOrder(checkBox, checkBox_2);
        QWidget::setTabOrder(checkBox_2, checkBox_3);
        QWidget::setTabOrder(checkBox_3, lineEdit_fsnName);
        QWidget::setTabOrder(lineEdit_fsnName, checkBox_4);
        QWidget::setTabOrder(checkBox_4, dateTimeEdit_2);
        QWidget::setTabOrder(dateTimeEdit_2, dateTimeEdit);
        QWidget::setTabOrder(dateTimeEdit, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_6);
        QWidget::setTabOrder(pushButton_6, pushButton_8);

        retranslateUi(FsnTool);

        QMetaObject::connectSlotsByName(FsnTool);
    } // setupUi

    void retranslateUi(QMainWindow *FsnTool)
    {
        FsnTool->setWindowTitle(QApplication::translate("FsnTool", "FsnTool", Q_NULLPTR));
        label_fsn_num->setText(QApplication::translate("FsnTool", "0", Q_NULLPTR));
        label_3->setText(QApplication::translate("FsnTool", "Num\357\274\232", Q_NULLPTR));
        label_logo->setText(QApplication::translate("FsnTool", "Logo", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("FsnTool", "Choose File", Q_NULLPTR));
        label_2->setText(QApplication::translate("FsnTool", "FsnFile\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("FsnTool", "FsnFilePath\357\274\232", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("FsnTool", "Operation", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FsnTool", "Choose Path", Q_NULLPTR));
        label_5->setText(QApplication::translate("FsnTool", "File Num\357\274\232", Q_NULLPTR));
        label_fsnFileNumber->setText(QApplication::translate("FsnTool", "0", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("FsnTool", "File Search", Q_NULLPTR));
        label_7->setText(QApplication::translate("FsnTool", "SNo\357\274\232", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("FsnTool", "Search", Q_NULLPTR));
        label_8->setText(QApplication::translate("FsnTool", "MoneyFlag\357\274\232", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("FsnTool", "Search", Q_NULLPTR));
        checkBox->setText(QApplication::translate("FsnTool", "Real", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("FsnTool", "Fake", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("FsnTool", "Damaged", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("FsnTool", "Old", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("FsnTool", "Datetime Search", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("FsnTool", "Back", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("FsnTool", "Show All FSN", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("FsnTool", "Amalgamate All FSN", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("FsnTool", "Save Excel", Q_NULLPTR));
        checkBox_image->setText(QApplication::translate("FsnTool", "Contains Pictures", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("FsnTool", "Save Sql Data", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("FsnTool", "Show", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FsnTool", "DateTime", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FsnTool", "TfFlag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FsnTool", "Error", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FsnTool", "MoneyFlag", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("FsnTool", "Ver", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("FsnTool", "Valuta", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("FsnTool", "CharNUM", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("FsnTool", "SNo", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("FsnTool", "Image", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("FsnTool", "MachineSNo", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("FsnTool", "Operateor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FsnTool: public Ui_FsnTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FSNTOOL_H
