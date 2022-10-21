#include "errorform.h"
#include "ui_errorform.h"
#include <QDebug>

extern QString AllError; //声明外部变量，与主界面全局变量转参
extern QString SNo; //声明外部变量，与主界面全局变量转参
//TODO 024、显示错误码的窗口errorForm
errorForm::errorForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::errorForm)
{
    ui->setupUi(this);
    setMinimumSize(297, 617);
    setMaximumSize(297, 617);

    //tableWidget列表自适应内容宽度，i代表第几列
    for (int i = 0; i < 3; i++) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    //tableWidget列表不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setError();
}

errorForm::~errorForm()
{
    delete ui;
}

void errorForm::setError()
{
    qDebug() << "setError启动成功,ErrorInfo = " << AllError;
    ui->label_error_version->setText(AllError.mid(47, 1));
    ui->label_SNo->setText(SNo);
    ui->label_SNo->setStyleSheet("color:red;");
    QFont font("Microsoft YaHei", 12, 100); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    ui->label_SNo->setFont(font);
    QStringList errorInfo;
    errorInfo << "纸币外形尺寸（长、宽）"
              << "可见光反射图文"
              << "可见光透视图文"
              << "红外反射图文"
              << "红外透视图文"
              << "荧光图文"
              << "磁性图文"
              << "安全线磁性特征"
              << "印刷光变图文"
              << "安全线（贴膜）光学特征"
              << "精细镂空图文"
              << "电学特征"
              << "光谱吸收特征"
              << "透明视窗特征"
              << "水印特征"
              << "冠字号码"
              << "厚度特征"
              << "其他防伪特征";
    for (int i = 0; i < 18; i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(errorInfo[i]));
        //        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(AllError.mid(i * 2, 1)));
        //        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(AllError.mid((i * 2) + 1, 1)));

        QTableWidgetItem* item1 = new QTableWidgetItem(AllError.mid(i * 2, 1));

        if (item1->text().toInt() == 0) {
            item1->setTextColor(QColor(Qt::red));
            QFont nullFont;
            nullFont.setBold(true);
            item1->setFont(nullFont);
            ui->tableWidget->setItem(i, 1, item1);
        } else {
            ui->tableWidget->setItem(i, 1, item1);
        }

        QTableWidgetItem* item2 = new QTableWidgetItem(AllError.mid((i * 2) + 1, 1));

        if (item2->text().toInt() == 1) {
            item2->setTextColor(QColor(Qt::red));
            QFont nullFont;
            nullFont.setBold(true);
            item2->setFont(nullFont);
            ui->tableWidget->setItem(i, 2, item2);
        } else {
            ui->tableWidget->setItem(i, 2, item2);
        }
    }
}
