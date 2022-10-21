#include "fsntool.h"
#include "errorform.h"
#include "ui_fsntool.h"
#include <QAxObject>
#include <QDebug>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDirIterator>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMimeData>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPainter>
#include <QSettings>
#include <shlobj.h>
#include <windows.h>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QString AllError; //声明一个全局变量用于窗体间传值
QString SNo; //声明一个全局变量用于窗体间传值
//double version = 2.3;  //软件本地版本
bool showAll = true;
bool showFile = true;
bool bFlag = true;
bool haveImage = false;

int allFsnVersion = 0;

FsnTool::FsnTool(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::FsnTool)
{
    ui->setupUi(this);

    //设置软件界面logo

    QPixmap icon(":/logo.png");
    ui->label_logo->setPixmap(icon);
    ui->label_logo->installEventFilter(this);

    //    setWindowState(Qt::WindowMaximized);
    //启动全屏显示

    //无边框
    //    setWindowFlags(Qt::FramelessWindowHint);

    //冠字号码张数修改字体样式和大小
    ui->label_fsn_num->setStyleSheet("color:red;");
    QFont font("Microsoft YaHei", 16, 100); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    ui->label_fsn_num->setFont(font);

    //启动fsn文件拖放功能
    setAcceptDrops(true);

    // TODO 001、安装消息处理函数（是否启动本地日志）
    //    Singleton<kcLog>::getInstance().installMessageHandler();
    //    qDebug() << "安装消息处理函数,并启动软件！";

    // tableWidget列表自适应内容宽度，i代表第几列
    for (int i = 0; i < 12; i++) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    // tableWidget列表不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // tableWidget列表被双击
    //    connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this,
    //    SLOT(slot_doubleClicked(int, int)));
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_doubleClicked(int, int)));

    // 复选框连接信号槽 QCheckBox 在状态改变时会发送一个 stateChanged
    // 信号，该信号有一个参数 state；
    connect(ui->checkBox, &QCheckBox::stateChanged, [=](int state) { checkBox_OnClick(state); });
    connect(ui->checkBox_2, &QCheckBox::stateChanged, [=](int state) { checkBox_2_OnClick(state); });
    connect(ui->checkBox_3, &QCheckBox::stateChanged, [=](int state) { checkBox_3_OnClick(state); });
    connect(ui->checkBox_4, &QCheckBox::stateChanged, [=](int state) { checkBox_4_OnClick(state); });
    connect(ui->checkBox_image, &QCheckBox::stateChanged, [=](int state) { checkBox_image_OnClick(state); });

    //时间控件
    ui->dateTimeEdit->setCalendarPopup(true);
    ui->dateTimeEdit_2->setCalendarPopup(true);
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    //主动检测更新
    //    kcUpdateThread *upt = new kcUpdateThread();
    //    connect(upt, SIGNAL(info(QString)), this, SLOT(upLoad(QString)));
    //    upt->test();
}
FsnTool::~FsnTool() { delete ui; }

// TODO 002、启动软件后点击按钮选择文件目录。
void FsnTool::on_pushButton_clicked()
{
    qDebug() << "选择文件目录按钮被单击";
    ui->listWidget_fsn->clear();
    QString fileDir = QFileDialog::getExistingDirectory(this);
    if (fileDir.isEmpty()) {
        return;
    } else {
        // TODO 003、写出文件目录到lineEdit。
        qDebug() << "文件目录:" << fileDir;
        ui->lineEdit->setText(fileDir);

        // TODO 004、遍历目录中的文件，找到*.fsn文件。
        FsnTool::findFile(fileDir);

        // TODO 007、*.fsn文件遍历和添加结束！。
        qDebug() << "*.fsn文件遍历和添加结束！";
    }
}

// 遍历指定目录下所有子目录，查找*.fsn文件
void FsnTool::findFile(QString path)
{
    //判断路径是否存在
    QDir dir(path);
    if (!dir.exists()) {
        return;
    }
    //获取所选文件类型过滤器
    QStringList filters;
    filters << QString("*.fsn") << QString("*.efsn");
    // filters << QString("*.jpeg") << QString("*.jpg") << QString("*.png") <<
    // QString("*.tiff") << QString("*.gif") << QString("*.bmp");
    //定义迭代器并设置过滤器
    QDirIterator dir_iterator(path, filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    int fsnFileNumber = 0;
    while (dir_iterator.hasNext()) {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString fsn_file_path = file_info.absoluteFilePath();
        qDebug() << "遍历到的FSN文件 : " << fsn_file_path;
        // TODO 005、将*.fsn文件添加到listView中。
        ui->listWidget_fsn->addItem(fsn_file_path);
        fsnFileNumber++;
    }
    // TODO 006、将指定文件夹中的fsn文件数量添加到label_fsnFileNumber。
    ui->label_fsnFileNumber->setText(QString::number(fsnFileNumber));
}

// TODO 008、对选中的FSN文件单击，将FSN文件名添加到lineEdit_fsnName中,同时对fsn文件进行解析。
void FsnTool::on_listWidget_fsn_currentTextChanged(const QString& fsnFile)
{
    ui->lineEdit_fsnName->setText(fsnFile);
    qDebug() << "被选中的FSN文件：" << fsnFile;
    qDebug() << "该FSN文件被单击，添加到lineEdit_fsnName中,同时对fsn文件进行解析";
    FsnTool::readyGo(fsnFile);
}

// TODO 009、点击选择文件按钮，将FSN文件名添加到lineEdit_fsnName中,同时对fsn文件进行解析。
void FsnTool::on_pushButton_2_clicked()
{
    QString fsnFile = QFileDialog::getOpenFileName(this, tr("文件"), "", tr("text(*.fsn *.efsn)"));
    ui->lineEdit_fsnName->setText(fsnFile);
    qDebug() << "被选中的FSN文件：" << fsnFile;
    qDebug() << "该FSN文件被单击，添加到lineEdit_fsnName中,同时对fsn文件进行解析";
    FsnTool::readyGo(fsnFile);
}

// TODO 010、解析文件钱准备工作。
void FsnTool::readyGo(QString fsnFile)
{
    //确定解析文件
    ui->lineEdit_fsnName->setText(fsnFile);
    //解析前，清空列表
    if (showAll) {
        int row = ui->tableWidget->rowCount();
        for (int i = row; i > 0; i--) {
            ui->tableWidget->removeRow(0);
        }
    }

    //开始解析
    FsnTool::fsnRead(fsnFile);

    //解决解析fsn文件条数
    int list = ui->tableWidget->rowCount();
    QString num = QString::number(list);
    ui->label_fsn_num->setText(num);

    qDebug() << "FSN解析完成--------------------------------------------------------";
}

// TODO 011-01、解析2014版FSN文件函数。
void FsnTool::fsnRead(QString fsnPath)
{
    qDebug() << "开始解析FSN文件:" << fsnPath;
    //    ui->textEdit->clear();

    if (haveImage) {
        QDir* folder = new QDir;
        bool exist = folder->exists(QApplication::applicationDirPath() + "/imageTemp/");
        if (exist) {
            qDebug() << "文件夹存在";
        } else {
            //创建文件夹
            bool ok = folder->mkdir(QApplication::applicationDirPath() + "/imageTemp/");
            if (ok)
                qDebug() << "文件夹不存在，创建成功";
            else
                qDebug() << "文件夹不存在，创建失败";
        }
    }

    //读取文件
    QFile file(fsnPath);
    QByteArray Data;
    file.open(QIODevice::ReadOnly);
    Data = file.readAll();
    file.close();
    //    qDebug() << "文件总长度 = " << num;

    //数据取前32个字节
    int fsnHeadLength = sizeof(FSN_Header_Fromat);
    QByteArray Data_fsnHead;
    Data_fsnHead = Data.mid(0, fsnHeadLength);
    QString info_fsnHead = ByteArrayToHexString(Data_fsnHead);
    //    ui->textEdit->append("----解析文件头----");
    //    qDebug() << "----解析文件头-------------------------------------";
    //========================================================================
    QString HeadStart = info_fsnHead.mid(0, 16);
    //    qDebug() << "HeadStart=" << HeadStart;
    //    ui->textEdit->append("HeadStart=" + HeadStart);

    QString HeadStart_1 = HeadStart.mid(0, 2);
    QString HeadStart_2 = HeadStart.mid(4, 2);
    QString HeadStart_3 = HeadStart.mid(8, 2);
    QString HeadStart_4 = HeadStart.mid(12, 2);
    QString HeadStartALL = QString::number(HexStringToInt(HeadStart_1)) + "," + QString::number(HexStringToInt(HeadStart_2)) + "," + QString::number(HexStringToInt(HeadStart_3)) + "," + QString::number(HexStringToInt(HeadStart_4));
    //    qDebug() << "开始标识 =" << HeadStartALL;
    //    ui->textEdit->append("开始标识 = " + HeadStartALL);
    //=============================================================================================
    QString HeadString = info_fsnHead.mid(16, 24);

    //判断fsn文件版本
    int fsnVer = HeadString.mid(4, 2).toInt();
    if (fsnVer == 1) {
        //        ui->textEdit->append("文件版本 = 2014版FSN");
        //        qDebug() << "文件版本 = 2014版FSN";
    } else if (fsnVer == 2) {
        //        ui->textEdit->append("文件版本 = 2018版FSN");
        //        qDebug() << "文件版本 = 2018版FSN";
        file.close();
        fsnReadFor2018(fsnPath);
        return;
    } else {
        //        ui->textEdit->append("文件版本 = 无此版本");
        //        qDebug() << "文件版本 = 无此版本";
        file.close();
        return;
    }

    //判断fsn文件是否包含图片
    QString fsnImage = HeadString.mid(8, 2);
    bFlag = fsnImage.contains(QRegExp("2E"));
    if (bFlag) {
        //        ui->textEdit->append("图像包含 = 包含图像");
        //        qDebug() << "图像包含 = 包含图像";
    } else {
        //        ui->textEdit->append("图像包含 = 不包含图像");
        //        qDebug() << "图像包含 = 不包含图";
    }

    //=============================================================================================
    QString Counter = info_fsnHead.mid(40, 8);
    // Counter= "64000000"//进行倒序
    QString fsnConter_1 = Counter.mid(6, 2);
    QString fsnConter_2 = Counter.mid(4, 2);
    QString fsnConter_3 = Counter.mid(2, 2);
    QString fsnConter_4 = Counter.mid(0, 2);
    QString CounterALL = fsnConter_1 + fsnConter_2 + fsnConter_3 + fsnConter_4;
    int Counter_all = HexStringToInt(CounterALL);
    //    qDebug() << "QStringCounter=" << fsnConter_1 + fsnConter_2 + fsnConter_3
    //    + fsnConter_4; qDebug() << "文件张数 =" << QString::number(Counter_all);
    //    ui->textEdit->append("记录张数 = " + QString::number(Counter_all) + "张");

    //=============================================================================================
    QString HeadEnd = info_fsnHead.mid(48, 16);
    QString HeadEnd_1 = HeadEnd.mid(0, 2);
    QString HeadEnd_2 = HeadEnd.mid(4, 2);
    QString HeadEnd_3 = HeadEnd.mid(8, 2);
    QString HeadEnd_4 = HeadEnd.mid(12, 2);
    QString HeadEndALL = QString::number(HexStringToInt(HeadEnd_1)) + "," + QString::number(HexStringToInt(HeadEnd_2)) + "," + QString::number(HexStringToInt(HeadEnd_3)) + "," + QString::number(HexStringToInt(HeadEnd_4));
    //    qDebug() << "结束标识 =" << HeadEndALL;
    //    ui->textEdit->append("结束标识 = " + HeadEndALL);

    //数据文件体字节长度==============================================================================
    int fsnBodyLength = sizeof(FSN_BodyData_Fromat);
    //    qDebug() << "文件体长度 = " << sizeof(FSN_BodyData_Fromat);
    int start = 0;

    for (int i = 0; i < Counter_all; i++) {
        QByteArray Data_fsnBody;
        Data_fsnBody = Data.mid(fsnHeadLength + start, fsnBodyLength);
        QString info_fsnBody = ByteArrayToHexString(Data_fsnBody);
        //    qDebug() << "文件体内容 = " << info_fsnBody;
        //    qDebug() << "第（" << i << "）张数据"
        //    qDebug() <<
        //    "----解析文件体--------------------------------------------------------";
        //    int fsnImageLength = sizeof(TImageSNo);
        //    qDebug() << "FSN图像长度 = " << fsnImageLength;

        QString dateInfo = info_fsnBody.mid(2, 2) + info_fsnBody.mid(0, 2);
        QString timeInfo = info_fsnBody.mid(6, 2) + info_fsnBody.mid(4, 2);
        //    qDebug() << "dateInfo = " << dateInfo;
        //    qDebug() << "timeInfo = " << timeInfo;

        //获取fsn走钞日期和时间
        unsigned short date;
        unsigned short time;
        bool ok;
        date = dateInfo.toUShort(&ok, 16);
        time = timeInfo.toUShort(&ok, 16);
        //    qDebug() << "date =" << date;
        //    qDebug() << "time =" << time;
        int Y = (date >> 9) + 1980;
        int M = (date >> 5) & 0x0F;
        int D = date & 0x1F;
        int H = time >> 11;
        int m = (time >> 5) & 0x3F;
        int s = (time << 1) & 0x3F;
        //王征写法
        //    int H = (time & 0xF800) >> 11;
        //    int m = (time & 0x07E0) >> 5;
        //    int s = (time & 0x001F) << 1;

        QString DateTime = QString::number(Y) + "-" + QString::number(M) + "-" + QString::number(D) + " " + QString::number(H) + ":" + QString::number(m) + ":" + QString::number(s);
        int RowCont = ui->tableWidget->rowCount(); //获取当前行
        ui->tableWidget->insertRow(RowCont); //增加一行
        ui->tableWidget->setItem(RowCont, 0, new QTableWidgetItem(DateTime)); //插入元素
        //    qDebug() << "时  间 = " << DateTime;

        QDateTime current_time = QDateTime::fromString(DateTime, "yyyy-MM-dd hh:mm:ss"); //显示时间，格式为：年-月-日 时：分：秒 周几
        if (i == 0) {
            ui->dateTimeEdit->setDateTime(current_time);
        }
        if (i == Counter_all - 1) {
            ui->dateTimeEdit_2->setDateTime(current_time);
        }

        //获取纸币真假状态
        QString tfFlag;
        tfFlag = info_fsnBody.mid(8, 2);
        QStringList tfFlag_info;
        tfFlag_info << "Fake"
                    << "Real"
                    << "Damaged"
                    << "Old";
        if (HexStringToInt(tfFlag) == 0) {
            QTableWidgetItem* item = new QTableWidgetItem(tfFlag_info[HexStringToInt(tfFlag)]);
            item->setTextColor(QColor(Qt::red));
            QFont nullFont;
            nullFont.setBold(true);
            item->setFont(nullFont);
            ui->tableWidget->setItem(RowCont, 1, item);
        } else {
            ui->tableWidget->setItem(RowCont, 1, new QTableWidgetItem(tfFlag_info[HexStringToInt(tfFlag)]));
        }

        //        qDebug() << "真  假 = " << tfFlag_info[HexStringToInt(tfFlag)];

        //获取纸币错误码ErrorCode[3]
        QStringList ErrorCode;
        ErrorCode << info_fsnBody.mid(12, 2) << info_fsnBody.mid(14, 2) << info_fsnBody.mid(16, 2) << info_fsnBody.mid(18, 2) << info_fsnBody.mid(20, 2) << info_fsnBody.mid(22, 2);
        QString ErrorCode_info = ErrorCode[1] + ErrorCode[0] + ":" + ErrorCode[3] + ErrorCode[2] + ":" + ErrorCode[5] + ErrorCode[4];
        ui->tableWidget->setItem(RowCont, 2, new QTableWidgetItem(ErrorCode_info));
        //        qDebug() << "错误码 = " << ErrorCode_info;

        //获取纸币币种MoneyFlag[4]
        QStringList MoneyFlag;
        MoneyFlag << info_fsnBody.mid(24, 2) << info_fsnBody.mid(28, 2) << info_fsnBody.mid(32, 2) << info_fsnBody.mid(36, 2);
        QString MoneyFlagInfo = changefromHex_to_ascii(MoneyFlag[0]) + changefromHex_to_ascii(MoneyFlag[1]) + changefromHex_to_ascii(MoneyFlag[2]) + changefromHex_to_ascii(MoneyFlag[3]);

        ui->tableWidget->setItem(RowCont, 3, new QTableWidgetItem(MoneyFlagInfo));
        //        qDebug() << "币  种 = " << MoneyFlagInfo;

        //获取纸币版本Ver
        QString Ver;
        Ver = info_fsnBody.mid(40, 2);
        QStringList Ver_info;
        Ver_info << "1990"
                 << "1999"
                 << "2005"
                 << "2015"
                 << "2019"
                 << "2020";
        if (HexStringToInt(Ver) > 5) {
            ui->tableWidget->setItem(RowCont, 4, new QTableWidgetItem("9999"));
            //            qDebug() << "版  本 =  9999";
        } else {
            ui->tableWidget->setItem(
                RowCont, 4, new QTableWidgetItem(Ver_info[HexStringToInt(Ver)]));
            //            qDebug() << "版  本 = " << Ver_info[HexStringToInt(Ver)];
        }

        //获取纸币币值Valuta
        QStringList Valuta;
        Valuta << info_fsnBody.mid(46, 2) << info_fsnBody.mid(44, 2);
        //        qDebug() << "Valuta[0] = " << Valuta[0];
        //        qDebug() << "Valuta[1] = " << Valuta[1];
        QString ValutaInfo = removeFirst0(Valuta[0] + Valuta[1]);
        //        qDebug() << "QStringList Valuta = " << ValutaInfo;
        //        qDebug() << "HexStringToInt(ValutaInfo) = " <<
        //        HexStringToInt(ValutaInfo);
        ui->tableWidget->setItem(
            RowCont, 5,
            new QTableWidgetItem(QString::number(HexStringToInt(ValutaInfo))));
        //        qDebug() << "面  值 = " <<
        //        QString::number(HexStringToInt(ValutaInfo));

        //获取纸币冠字号字符数CharNUM
        QStringList CharNUM;
        CharNUM << info_fsnBody.mid(50, 2) << info_fsnBody.mid(48, 2);
        QString CharNUMInfo = removeFirst0(CharNUM[0] + CharNUM[1]);
        //    qDebug() << "QStringList CharNUM = " << CharNUMInfo;
        //    qDebug() << "HexStringToInt(ValutaInfo) = " <<
        //    HexStringToInt(CharNUMInfo);
        ui->tableWidget->setItem(
            RowCont, 6,
            new QTableWidgetItem(QString::number(HexStringToInt(CharNUMInfo))));
        //        qDebug() << "字符数 = " <<QString::number(HexStringToInt(CharNUMInfo));

        //获取纸冠字号SNo[12];
        QStringList SNo;
        SNo << info_fsnBody.mid(52, 2) << info_fsnBody.mid(56, 2)
            << info_fsnBody.mid(60, 2) << info_fsnBody.mid(64, 2)
            << info_fsnBody.mid(68, 2) << info_fsnBody.mid(72, 2)
            << info_fsnBody.mid(76, 2) << info_fsnBody.mid(80, 2)
            << info_fsnBody.mid(84, 2) << info_fsnBody.mid(88, 2)
            << info_fsnBody.mid(92, 2) << info_fsnBody.mid(96, 2);
        QString SNoInfo;
        for (int i = 0; i < HexStringToInt(CharNUMInfo); i++) {
            SNoInfo = SNoInfo.append(changefromHex_to_ascii(SNo[i]));
        }
        ui->tableWidget->setItem(RowCont, 7, new QTableWidgetItem(SNoInfo));
        //        qDebug() << "冠字号 = " << SNoInfo;

        //获取机具编号MachineSNo[24]
        QStringList MachineSNo;
        MachineSNo << info_fsnBody.mid(100, 2) << info_fsnBody.mid(104, 2)
                   << info_fsnBody.mid(108, 2) << info_fsnBody.mid(112, 2)
                   << info_fsnBody.mid(116, 2) << info_fsnBody.mid(120, 2)
                   << info_fsnBody.mid(124, 2) << info_fsnBody.mid(128, 2)
                   << info_fsnBody.mid(132, 2) << info_fsnBody.mid(136, 2)
                   << info_fsnBody.mid(140, 2) << info_fsnBody.mid(144, 2)
                   << info_fsnBody.mid(148, 2) << info_fsnBody.mid(152, 2)
                   << info_fsnBody.mid(156, 2) << info_fsnBody.mid(160, 2)
                   << info_fsnBody.mid(164, 2) << info_fsnBody.mid(168, 2)
                   << info_fsnBody.mid(172, 2) << info_fsnBody.mid(176, 2)
                   << info_fsnBody.mid(180, 2) << info_fsnBody.mid(184, 2)
                   << info_fsnBody.mid(188, 2) << info_fsnBody.mid(192, 2);
        QString MachineSNoInfo;
        int MachineSNoNum = MachineSNo.count();
        for (int i = 0; i < MachineSNoNum; i++) {
            MachineSNoInfo = MachineSNoInfo.append(changefromHex_to_ascii(MachineSNo[i]));
        }
        ui->tableWidget->setItem(RowCont, 9, new QTableWidgetItem(MachineSNoInfo));
        //        qDebug() << "机具号 = " << MachineSNoInfo;

        //获取保留字1 Operateor_No
        QStringList Operateor_No;
        Operateor_No << info_fsnBody.mid(196, 2) << info_fsnBody.mid(198, 2);
        //    qDebug() << "Operateor_No[0] = " << Operateor_No[0];
        //    qDebug() << "Operateor_No[1] = " << Operateor_No[1];
        ui->tableWidget->setItem(
            RowCont, 10, new QTableWidgetItem(Operateor_No[0] + Operateor_No[1]));
        //        qDebug() << "预留字 = " << Operateor_No[0] + Operateor_No[1];

        //冠字号图像处理
        if (bFlag) {
            QByteArray image_Data_fsnBody;
            int fsnImageLength = sizeof(TImageSNo); //长度为1544
            image_Data_fsnBody = Data_fsnBody.mid(fsnBodyLength - fsnImageLength + 8, fsnImageLength - 8);
            //        QString image_info_fsnBody =
            //        ByteArrayToHexString(image_Data_fsnBody); qDebug() <<"----解析文件图像--------------------------------------------------------";

            //获取图像冠字号码结构中的字符数  short Num 8个在上面处理
            //        QString fsnImageNum      = image_info_fsnBody.mid(0, 2);
            //        QString fsnImageHeight   = image_info_fsnBody.mid(4, 2);
            //        QString fsnImageWidth    = image_info_fsnBody.mid(8, 2);
            //        QString fsnImageReserve2 = image_info_fsnBody.mid(12, 4);
            //        qDebug() << "图像个数 = " << HexStringToInt(fsnImageNum);
            //        qDebug() << "图像高度 = " << HexStringToInt(fsnImageHeight);
            //        qDebug() << "图像宽度 = " << HexStringToInt(fsnImageWidth);
            //        qDebug() << "图像预留字段 = " << fsnImageReserve2;
            //        QByteArray image_Data_fsnBody_info;
            //        image_Data_fsnBody_info = image_Data_fsnBody.mid(8,fsnImageLength - 8);

            TImageSNoData sn[12];
            memcpy(&sn[0].Data[0], image_Data_fsnBody.data(), sizeof(TImageSNoData) * 12);
            QImage image;
            if (HexStringToInt(CharNUMInfo) == 10) {
                image = QImage(320, 32, QImage::Format_Mono);
            } else if (HexStringToInt(CharNUMInfo) == 11) {
                image = QImage(352, 32, QImage::Format_Mono);
            } else {
                image = QImage(384, 32, QImage::Format_Mono);
            }

            //qDebug() << "冠字号字符数：HexStringToInt(CharNUMInfo) = " << HexStringToInt(CharNUMInfo);

            for (int count = 0; count < HexStringToInt(CharNUMInfo); count++) {
                for (int i = 0; i < 32; i++) {
                    for (int j = 0; j < 32; j++) {
                        if (((sn[count].Data[i] >> j) & 0x01) == 0x01) {
                            image.setPixel(i + count * 32, (31 - j), 1);
                        } else {
                            image.setPixel(i + count * 32, (31 - j), 0);
                        }
                    }
                }
            }

            //添加图片的第一种方法（耗时严重，不采用）
            //            QLabel *label1 = new QLabel();
            //            label1->setScaledContents(true);  //设置图片适应label
            //            label1->setPixmap(QPixmap::fromImage(image));
            //            ui->tableWidget->setCellWidget(RowCont, 8, label1);  //显示label

            //添加图片的第二种方法（以图标方式显示冠字号图片，在图标后面显示冠字号码
            //            -- QIcon(QPixmap::fromImage(image)), SNoInfo)）
            if (HexStringToInt(CharNUMInfo) == 10) {
                ui->tableWidget->setIconSize(QSize(320, 32));
            } else if (HexStringToInt(CharNUMInfo) == 11) {
                ui->tableWidget->setIconSize(QSize(352, 32));
            } else {
                ui->tableWidget->setIconSize(QSize(384, 32));
            }
            ui->tableWidget->setItem(RowCont, 8, new QTableWidgetItem(QIcon(QPixmap::fromImage(image)), ""));
            //        图片后面加冠字号
            //        ui->tableWidget->setItem(RowCont, 8, newQTableWidgetItem(QIcon(QPixmap::fromImage(image)), SNoInfo));

            if (haveImage) {
                //            保存图片
                //            当m_image(一个QImage变量)中已经载入图片数据后，可调用save()进行保存，如：m_image.save(pictrureName, “JPG”, 100);对于这三个参数，解释如下：
                //            1.pictrureName为图片文件的路径，比如："/home/feng/IMG_0.jpg"，需要注意的是路径必须要有权限读写；
                //            2."JPG"为图片的格式，注意不需要带"."；
                //            3.100指的是图片的质量因数，范围必须在0到100之内或-1，指定0以获取小型压缩文件，指定100表示大型未压缩文件，使用-1（默认值）使用默认设置。

                QString pictrureName = QApplication::applicationDirPath() + "/imageTemp/" + QString::number(i) + ".jpg";
                //                qDebug() << i << ":测试图片保存速度->" << pictrureName;
                image.save(pictrureName, "jpg", 100);
            }
            //关闭fsn文件
            file.close();
            if (bFlag) {
                start = start + fsnBodyLength; //加一个1644
            } else {
                start = start + fsnBodyLength - 1544; //加一个1644
            }
        }
    }
}

// TODO 011-02、解析2018版FSN文件函数。
void FsnTool::fsnReadFor2018(QString fsnPath)
{
    //  qDebug() << "开始解析FSN文件函数";
    //    ui->textEdit->clear();

    if (haveImage) {
        QDir* folder = new QDir;
        bool exist = folder->exists(QApplication::applicationDirPath() + "/imageTemp/");
        if (exist) {
            qDebug() << "文件夹存在";
        } else {
            //创建文件夹
            bool ok = folder->mkdir(QApplication::applicationDirPath() + "/imageTemp/");
            if (ok)
                qDebug() << "文件夹不存在，创建成功";
            else
                qDebug() << "文件夹不存在，创建失败";
        }
    }

    //读取文件
    QFile file(fsnPath);
    QByteArray Data;
    file.open(QIODevice::ReadOnly);
    Data = file.readAll();
    file.close();

    //数据取前350个字节(文件头)
    QByteArray Data_fsnHead;
    Data_fsnHead = Data.mid(0, 350);
    QString info_fsnHead = ByteArrayToHexString(Data_fsnHead);
    //    ui->textEdit->append("------解析文件头开始------");
    //  qDebug() << "----解析文件头-------------------------------------";
    //    qDebug() << "解析文件头内容 = " << info_fsnHead;
    //========================================================================
    QString HeadStart = info_fsnHead.mid(0, 16);
    QString HeadStart_1 = HeadStart.mid(0, 2);
    QString HeadStart_2 = HeadStart.mid(4, 2);
    QString HeadStart_3 = HeadStart.mid(8, 2);
    QString HeadStart_4 = HeadStart.mid(12, 2);
    QString HeadStartALL = QString::number(HexStringToInt(HeadStart_1)) + "," + QString::number(HexStringToInt(HeadStart_2)) + "," + QString::number(HexStringToInt(HeadStart_3)) + "," + QString::number(HexStringToInt(HeadStart_4));
    //  qDebug() << "开始标识 =" << HeadStartALL;
    //    ui->textEdit->append("开始标识 = " + HeadStartALL);
    //=============================================================================================
    QString HeadString = info_fsnHead.mid(16, 24);
    //    qDebug() << "HeadString=" << HeadString;
    //    ui->textEdit->append("HeadString=" + HeadString);

    //判断fsn文件版本
    int fsnVer = HeadString.mid(4, 2).toInt();
    if (fsnVer == 1) {
        //        ui->textEdit->append("文件版本 = 2014版FSN");
        //    qDebug() << "文件版本 = 2014版FSN";
    } else if (fsnVer == 2) {
        //        ui->textEdit->append("文件版本 = 2018版FSN");
        //    qDebug() << "文件版本 = 2018版FSN";
    } else {
        //        ui->textEdit->append("文件版本 = 无此版本");
        //    qDebug() << "文件版本 = 无此版本";
        file.close();
        return;
    }

    //判断fsn文件是否包含图片
    QString fsnImage = HeadString.mid(8, 2);
    bool bFlag = fsnImage.contains(QRegExp("2E"));
    if (bFlag) {
        //        ui->textEdit->append("图像包含 = 包含图像");
        //    qDebug() << "图像包含 = 包含图像";
    } else {
        //        ui->textEdit->append("图像包含 = 不包含图像");
        //    qDebug() << "图像包含 = 不包含图";
    }

    //=============================================================================================
    // HeadDatatypeFlag
    // 机具信息记录格式标识，分为标识机具型号、硬件版本号和软件版本号的存储格式，1为Uint16格式，2为Unit8格式；
    QString HeadDatatypeFlag = info_fsnHead.mid(40, 4);
    int HeadDatatypeFlagNum = HeadDatatypeFlag.mid(0, 2).toInt();
    //================================================================================

    QString Counter = info_fsnHead.mid(44, 8);
    // Counter= "64000000"//进行倒序
    QString fsnConter_1 = Counter.mid(6, 2);
    QString fsnConter_2 = Counter.mid(4, 2);
    QString fsnConter_3 = Counter.mid(2, 2);
    QString fsnConter_4 = Counter.mid(0, 2);
    QString CounterALL = fsnConter_1 + fsnConter_2 + fsnConter_3 + fsnConter_4;
    int Counter_all = HexStringToInt(CounterALL);
    //    qDebug() << "QStringCounter=" << fsnConter_1 + fsnConter_2 + fsnConter_3
    //    + fsnConter_4;
    //  qDebug() << "文件张数 =" << QString::number(Counter_all);
    //    ui->textEdit->append("记录张数 = " + QString::number(Counter_all) + "张");

    //================================================================================
    //    USHORT FinanIns[6];         /*金融机构缩写*/
    QStringList FinanIns;
    FinanIns << info_fsnHead.mid(52, 2) << info_fsnHead.mid(56, 2) << info_fsnHead.mid(60, 2) << info_fsnHead.mid(64, 2) << info_fsnHead.mid(68, 2) << info_fsnHead.mid(72, 2);
    QString FinanInsInfo;
    int FinanInsNum = FinanIns.count();
    for (int i = 0; i < FinanInsNum; i++) {
        if (FinanIns[i] != "00") {
            FinanInsInfo = FinanInsInfo.append(changefromHex_to_ascii(FinanIns[i]));
        }
    }
    //    ui->textEdit->append("金融机构 = " + FinanInsInfo);
    //  qDebug() << "金融机构缩写 = " << FinanInsInfo;

    //    UINT Enabletime; /*设备启用时间*/
    QString Enabletime = info_fsnHead.mid(76, 8);
    QString Enabletime_1 = Enabletime.mid(0, 2);
    QString Enabletime_2 = Enabletime.mid(2, 2);
    QString Enabletime_3 = Enabletime.mid(4, 2);
    QString Enabletime_4 = Enabletime.mid(6, 2);
    //    ui->textEdit->append("启用时间 = " + changefromHex_to_ascii(Enabletime_1) + changefromHex_to_ascii(Enabletime_2) + changefromHex_to_ascii(Enabletime_3) + changefromHex_to_ascii(Enabletime_4));
    //  qDebug() << "启用时间 = " << changefromHex_to_ascii(Enabletime_1)
    //           << changefromHex_to_ascii(Enabletime_2)
    //           << changefromHex_to_ascii(Enabletime_3)
    //           << changefromHex_to_ascii(Enabletime_4);

    //    USHORT MachineSNo[24];      /*机具编号*/
    QStringList MachineSNo;
    MachineSNo << info_fsnHead.mid(84, 2) << info_fsnHead.mid(88, 2)
               << info_fsnHead.mid(92, 2) << info_fsnHead.mid(96, 2)
               << info_fsnHead.mid(100, 2) << info_fsnHead.mid(104, 2)
               << info_fsnHead.mid(108, 2) << info_fsnHead.mid(112, 2)
               << info_fsnHead.mid(116, 2) << info_fsnHead.mid(120, 2)
               << info_fsnHead.mid(124, 2) << info_fsnHead.mid(128, 2)
               << info_fsnHead.mid(132, 2) << info_fsnHead.mid(136, 2)
               << info_fsnHead.mid(140, 2) << info_fsnHead.mid(144, 2)
               << info_fsnHead.mid(148, 2) << info_fsnHead.mid(152, 2)
               << info_fsnHead.mid(156, 2) << info_fsnHead.mid(160, 2)
               << info_fsnHead.mid(164, 2) << info_fsnHead.mid(168, 2)
               << info_fsnHead.mid(172, 2) << info_fsnHead.mid(176, 2);
    QString MachineSNoInfo;
    int MachineSNoNum = MachineSNo.count();
    for (int i = 0; i < MachineSNoNum; i++) {
        if (MachineSNo[i] != "00") {
            MachineSNoInfo = MachineSNoInfo.append(changefromHex_to_ascii(MachineSNo[i]));
        }
    }
    //    ui->textEdit->append("机具编号 = " + MachineSNoInfo);
    //  qDebug() << "机具编号 = " << MachineSNoInfo;

    //    USHORT MachineType[15];     /*机具类型*/
    QStringList MachineType;
    MachineType << info_fsnHead.mid(180, 2) << info_fsnHead.mid(184, 2)
                << info_fsnHead.mid(188, 2) << info_fsnHead.mid(192, 2)
                << info_fsnHead.mid(196, 2) << info_fsnHead.mid(200, 2)
                << info_fsnHead.mid(204, 2) << info_fsnHead.mid(208, 2)
                << info_fsnHead.mid(212, 2) << info_fsnHead.mid(216, 2)
                << info_fsnHead.mid(220, 2) << info_fsnHead.mid(224, 2)
                << info_fsnHead.mid(228, 2) << info_fsnHead.mid(232, 2)
                << info_fsnHead.mid(236, 2);
    QString MachineTypeInfo;
    int MachineTypeNum = MachineType.count();
    for (int i = 0; i < MachineTypeNum; i++) {
        if (MachineType[i] != "00") {
            MachineTypeInfo = MachineTypeInfo.append(changefromHex_to_ascii(MachineType[i]));
        }
    }
    //    ui->textEdit->append("机具类型 = " + MachineTypeInfo);
    //  qDebug() << "机具类型 = " << MachineTypeInfo;

    //    USHORT MachineModel[24];
    //    /*机具型号*/=======================================================
    QStringList MachineModel;
    if (HeadDatatypeFlagNum == 1) {
        for (int i = 0; i < 24; i++) {
            MachineModel.append(info_fsnHead.mid(240 + (i * 4), 2)); //循环添加数据
        }
    } else {
        for (int i = 0; i < 48; i++) {
            MachineModel.append(info_fsnHead.mid(240 + (i * 2), 2)); //循环添加数据
        }
    }
    QString MachineModelInfo;
    int MachineModelNum = MachineModel.count();
    for (int i = 0; i < MachineModelNum; i++) {
        if (MachineModel[i] != "00") {
            MachineModelInfo = MachineModelInfo.append(changefromHex_to_ascii(MachineModel[i]));
        }
    }
    //    ui->textEdit->append("机具型号 = " + MachineModelInfo);
    //  qDebug() << "机具型号 = " << MachineModelInfo;

    //    USHORT HardVerNo[24];
    //    /*硬件版本号*/=====================================================
    QStringList HardVerNo;
    if (HeadDatatypeFlagNum == 1) {
        for (int i = 0; i < 24; i++) {
            HardVerNo.append(info_fsnHead.mid(336 + (i * 4), 2)); //循环添加数据
        }
    } else {
        for (int i = 0; i < 48; i++) {
            HardVerNo.append(info_fsnHead.mid(336 + (i * 2), 2)); //循环添加数据
        }
    }
    QString HardVerNoInfo;
    int HardVerNoNum = HardVerNo.count();
    for (int i = 0; i < HardVerNoNum; i++) {
        if (HardVerNo[i] != "00") {
            HardVerNoInfo = HardVerNoInfo.append(changefromHex_to_ascii(HardVerNo[i]));
        }
    }
    //    ui->textEdit->append("硬件版本 = " + HardVerNoInfo);
    //  qDebug() << "硬件版本号 = " << HardVerNoInfo;

    //    USHORT AuthSoftVerNo[24];
    //    /*软件版本号*/===================================================
    QStringList AuthSoftVerNo;
    if (HeadDatatypeFlagNum == 1) {
        for (int i = 0; i < 24; i++) {
            AuthSoftVerNo.append(info_fsnHead.mid(432 + (i * 4), 2)); //循环添加数据
        }
    } else {
        for (int i = 0; i < 48; i++) {
            AuthSoftVerNo.append(info_fsnHead.mid(432 + (i * 2), 2)); //循环添加数据
        }
    }
    QString AuthSoftVerNoInfo;
    int AuthSoftVerNoNum = AuthSoftVerNo.count();
    for (int i = 0; i < AuthSoftVerNoNum; i++) {
        if (AuthSoftVerNo[i] != "00") {
            AuthSoftVerNoInfo = AuthSoftVerNoInfo.append(changefromHex_to_ascii(AuthSoftVerNo[i]));
        }
    }
    //    ui->textEdit->append("软件版本 = " + AuthSoftVerNoInfo);
    //  qDebug() << "软件版本号 = " << AuthSoftVerNoInfo;

    //    USHORT Appli_denom[6];
    //    /*适用券别*/============================================================
    QStringList Appli_denom;
    for (int i = 0; i < 6; i++) {
        Appli_denom.append(info_fsnHead.mid(528 + (i * 4), 2)); //循环添加数据
    }
    QString Appli_denomInfo;
    Appli_denomInfo = "100:" + QString::number(HexStringToInt(Appli_denom[0])) + "," + "50:" + QString::number(HexStringToInt(Appli_denom[1])) + "," + "20:" + QString::number(HexStringToInt(Appli_denom[2])) + "," + "10:" + QString::number(HexStringToInt(Appli_denom[3])) + "," + "5:" + QString::number(HexStringToInt(Appli_denom[4])) + "," + "1:" + QString::number(HexStringToInt(Appli_denom[5]));
    //    ui->textEdit->append("适用券别 = " + Appli_denomInfo);
    //  qDebug() << "适用券别 = " << Appli_denomInfo;

    //    USHORT FinanInst[14];
    //    /*报送银行*/=====================================================================
    QStringList FinanInst;
    for (int i = 0; i < 14; i++) {
        FinanInst.append(info_fsnHead.mid(552 + (i * 4), 2)); //循环添加数据
    }
    QString FinanInstInfo;
    int FinanInstNum = FinanInst.count();
    for (int i = 0; i < FinanInstNum; i++) {
        if (FinanInst[i] != "00") {
            FinanInstInfo = FinanInstInfo.append(changefromHex_to_ascii(FinanInst[i]));
        }
    }
    //    ui->textEdit->append("报送银行 = " + FinanInstInfo);
    //  qDebug() << "报送银行 = " << FinanInstInfo;
    //    USHORT FinanInstOutlet[14];
    //    /*报送网点*/===========================================================================
    QStringList FinanInstOutlet;
    for (int i = 0; i < 14; i++) {
        FinanInstOutlet.append(info_fsnHead.mid(608 + (i * 4), 2)); //循环添加数据
    }
    QString FinanInstOutletInfo;
    int FinanInstOutletNum = FinanInstOutlet.count();
    for (int i = 0; i < FinanInstOutletNum; i++) {
        if (FinanInstOutlet[i] != "00") {
            FinanInstOutletInfo = FinanInstOutletInfo.append(
                changefromHex_to_ascii(FinanInstOutlet[i]));
        }
    }
    //    ui->textEdit->append("报送网点 = " + FinanInstOutletInfo);
    //  qDebug() << "报送网点 = " << FinanInstOutletInfo;

    //    USHORT Operator[4];
    //    /*操作人员*/========================================================================================
    QStringList Operator;
    for (int i = 0; i < 4; i++) {
        Operator.append(info_fsnHead.mid(664 + (i * 4), 2)); //循环添加数据
    }
    QString OperatorInfo;
    int OperatorNum = Operator.count();
    for (int i = 0; i < OperatorNum; i++) {
        if (Operator[i] != "00") {
            OperatorInfo = OperatorInfo.append(changefromHex_to_ascii(Operator[i]));
        }
    }
    //    ui->textEdit->append("操作人员 = " + OperatorInfo);
    //  qDebug() << "操作人员 = " << OperatorInfo;

    //    USHORT Reserve1;
    //    /*保留字1*/========================================================================================
    QString Reserve1 = info_fsnHead.mid(680, 4);
    //    ui->textEdit->append("保留字1  = " + Reserve1);
    //  qDebug() << "保留字1 = " << Reserve1;

    //    USHORT HeadEnd[4];
    //    /*文件头结束标识*/==================================================================================
    QStringList HeadEnd;
    for (int i = 0; i < 4; i++) {
        HeadEnd.append(info_fsnHead.mid(684 + (i * 4), 2)); //循环添加数据
    }
    //    qDebug() << HeadEnd[0] << "," << HeadEnd[1] << "," << HeadEnd[2] << ","
    //    << HeadEnd[3];
    QString HeadEndInfo;
    HeadEndInfo = QString::number(HexStringToInt(HeadEnd[0])) + "," + QString::number(HexStringToInt(HeadEnd[1])) + "," + QString::number(HexStringToInt(HeadEnd[2])) + "," + QString::number(HexStringToInt(HeadEnd[3]));
    //    ui->textEdit->append("结束标识 = " + HeadEndInfo);
    //  qDebug() << "文件头结束标识 = " << HeadEndInfo;

    //数据文件体字节长度================================================================================================================
    //数据文件体字节长度================================================================================================================
    int fsnBodyLength = sizeof(FSN_2108BodyData_Fromat);
    int fsnHeadLength_2018 = 350;
    int start = 0;

    for (int i = 0; i < Counter_all; i++) {
        QByteArray Data_fsnBody;
        Data_fsnBody = Data.mid(fsnHeadLength_2018 + start, fsnBodyLength);
        QString info_fsnBody = ByteArrayToHexString(Data_fsnBody);
        //    qDebug() << "文件体内容 = " << info_fsnBody;
        //    qDebug() << "第（" << i << "）张数据";
        //    qDebug() <<
        //    "----解析文件体--------------------------------------------------------";
        //    int fsnImageLength = sizeof(TImageSNo);
        //    qDebug() << "FSN图像长度 = " << fsnImageLength;

        //  QString timeInfo = "7352A984"; // 时  间 = 2021-03-19 16:37:18
        //    QString dateInfo = "5273"; // 时  间 = 2021-03-19 16:37:18
        //    QString timeInfo = "84A9"; // 时  间 = 2021-03-19 16:37:18

        QString dateInfo = info_fsnBody.mid(2, 2) + info_fsnBody.mid(0, 2);
        QString timeInfo = info_fsnBody.mid(6, 2) + info_fsnBody.mid(4, 2);
        //    qDebug() << "dateInfo = " << dateInfo;
        //    qDebug() << "timeInfo = " << timeInfo;

        //获取fsn走钞日期和时间
        unsigned short date;
        unsigned short time;
        bool ok;
        date = dateInfo.toUShort(&ok, 16);
        time = timeInfo.toUShort(&ok, 16);

        //    date = (Data_fsnBody.at(1) << 8) + Data_fsnBody.at(0);
        //    time = (Data_fsnBody.at(3) << 8) + Data_fsnBody.at(2);
        //    qDebug() << "(Data_fsnBody.at(1) =" << (Data_fsnBody.at(1));
        //    qDebug() << "(Data_fsnBody.at(1) << 8) =" << (Data_fsnBody.at(1) <<
        //    8); qDebug() << "Data_fsnBody.at(0) << 8) =" << Data_fsnBody.at(0);
        //    qDebug() << "Data_fsnBody.at(3) << 8) =" << (Data_fsnBody.at(3) << 8);
        //    qDebug() << "Data_fsnBody.at(0) << 2) =" << Data_fsnBody.at(2);

        //    qDebug() << "date =" << date;
        //    qDebug() << "time =" << time;
        int Y = (date >> 9) + 1980;
        int M = (date >> 5) & 0x0F;
        int D = date & 0x1F;
        int H = time >> 11;
        int m = (time >> 5) & 0x3F;
        int s = (time << 1) & 0x3F;
        //王征写法
        //    int H = (time & 0xF800) >> 11;
        //    int m = (time & 0x07E0) >> 5;
        //    int s = (time & 0x001F) << 1;

        QString DateTime = QString::number(Y) + "-" + QString::number(M) + "-" + QString::number(D) + " " + QString::number(H) + ":" + QString::number(m) + ":" + QString::number(s);
        int RowCont = ui->tableWidget->rowCount(); //获取当前行
        ui->tableWidget->insertRow(RowCont); //增加一行
        ui->tableWidget->setItem(RowCont, 0,
            new QTableWidgetItem(DateTime)); //插入元素
        //    qDebug() << "时  间 = " << DateTime;

        QDateTime current_time = QDateTime::fromString(DateTime, "yyyy-MM-dd hh:mm:ss"); //显示时间，格式为：年-月-日 时：分：秒 周几
        if (i == 0) {
            ui->dateTimeEdit->setDateTime(current_time);
        }
        if (i == Counter_all - 1) {
            ui->dateTimeEdit_2->setDateTime(current_time);
        }

        //获取纸币真假状态
        QString tfFlag;
        tfFlag = info_fsnBody.mid(8, 2);
        QStringList tfFlag_info;
        tfFlag_info << "Fake"
                    << "Real"
                    << "Damaged"
                    << "Old";
        if (HexStringToInt(tfFlag) == 0) {
            QTableWidgetItem* item = new QTableWidgetItem(tfFlag_info[HexStringToInt(tfFlag)]);
            item->setTextColor(QColor(Qt::red));
            QFont nullFont;
            nullFont.setBold(true);
            item->setFont(nullFont);
            ui->tableWidget->setItem(RowCont, 1, item);
        } else {
            ui->tableWidget->setItem(
                RowCont, 1,
                new QTableWidgetItem(tfFlag_info[HexStringToInt(tfFlag)]));
        }

        //    qDebug() << "真  假 = " << tfFlag_info[HexStringToInt(tfFlag)];

        //获取纸币错误码ErrorCode[3]
        QStringList ErrorCode;
        ErrorCode << info_fsnBody.mid(12, 2) << info_fsnBody.mid(14, 2) << info_fsnBody.mid(16, 2) << info_fsnBody.mid(18, 2) << info_fsnBody.mid(20, 2) << info_fsnBody.mid(22, 2);
        QString ErrorCode_info = ErrorCode[1] + ErrorCode[0] + ":" + ErrorCode[3] + ErrorCode[2] + ":" + ErrorCode[5] + ErrorCode[4];
        ui->tableWidget->setItem(RowCont, 2, new QTableWidgetItem(ErrorCode_info));
        //    qDebug() << "错误码 = " << ErrorCode_info;

        //获取纸币币种MoneyFlag[4]
        QStringList MoneyFlag;
        MoneyFlag << info_fsnBody.mid(24, 2) << info_fsnBody.mid(28, 2) << info_fsnBody.mid(32, 2) << info_fsnBody.mid(36, 2);
        QString MoneyFlagInfo = changefromHex_to_ascii(MoneyFlag[0]) + changefromHex_to_ascii(MoneyFlag[1]) + changefromHex_to_ascii(MoneyFlag[2]) + changefromHex_to_ascii(MoneyFlag[3]);
        ui->tableWidget->setItem(RowCont, 3, new QTableWidgetItem(MoneyFlagInfo));
        //    qDebug() << "币  种 = " << MoneyFlagInfo;

        //获取纸币版本Ver
        QString Ver;
        Ver = info_fsnBody.mid(40, 2);
        QStringList Ver_info;
        Ver_info << "1990"
                 << "1999"
                 << "2005"
                 << "2015"
                 << "2019"
                 << "2020";
        if (HexStringToInt(Ver) > 5) {
            ui->tableWidget->setItem(RowCont, 4, new QTableWidgetItem("9999"));
            //      qDebug() << "版  本 =  9999";
        } else {
            ui->tableWidget->setItem(
                RowCont, 4, new QTableWidgetItem(Ver_info[HexStringToInt(Ver)]));
            //      qDebug() << "版  本 = " << Ver_info[HexStringToInt(Ver)];
        }

        //获取纸币币值Valuta
        QStringList Valuta;
        Valuta << info_fsnBody.mid(44, 2) << info_fsnBody.mid(46, 2)
               << info_fsnBody.mid(48, 2) << info_fsnBody.mid(50, 2)
               << info_fsnBody.mid(52, 2) << info_fsnBody.mid(54, 2)
               << info_fsnBody.mid(56, 2) << info_fsnBody.mid(58, 2);
        //        for (int i = 0; i < 8; i++) {
        //            qDebug() << "Valuta["
        //                     << "i"
        //                     << "] = " << Valuta[i];
        //        }
        //        QString ValutaInfo  = removeFirst0(Valuta[0] + Valuta[1] +
        //        Valuta[2] + Valuta[3] + Valuta[4] + Valuta[5] + Valuta[6] +
        //        Valuta[7]);
        QString ValutaInfo = removeFirst0(Valuta[7] + Valuta[6] + Valuta[5] + Valuta[4] + Valuta[3] + Valuta[2] + Valuta[1] + Valuta[0]);
        //    qDebug() << "QStringList Valuta = " << ValutaInfo;

        //    qDebug() << "HexStringToInt(ValutaInfo) = " <<
        //    HexStringToInt(ValutaInfo);
        ui->tableWidget->setItem(
            RowCont, 5,
            new QTableWidgetItem(QString::number(HexStringToInt(ValutaInfo))));
        //    qDebug() << "面  值 = " <<
        //    QString::number(HexStringToInt(ValutaInfo));

        //获取纸币冠字号字符数CharNUM
        QStringList CharNUM;
        CharNUM << info_fsnBody.mid(62, 2) << info_fsnBody.mid(60, 2);
        QString CharNUMInfo = removeFirst0(CharNUM[0] + CharNUM[1]);
        //    qDebug() << "QStringList CharNUM = " << CharNUMInfo;
        //    qDebug() << "HexStringToInt(ValutaInfo) = " <<
        //    HexStringToInt(CharNUMInfo);
        ui->tableWidget->setItem(
            RowCont, 6,
            new QTableWidgetItem(QString::number(HexStringToInt(CharNUMInfo))));
        //    qDebug() << "字符数 = " <<
        //    QString::number(HexStringToInt(CharNUMInfo));

        //获取纸冠字号SNo[12];
        QStringList SNo;
        SNo << info_fsnBody.mid(64, 2) << info_fsnBody.mid(68, 2)
            << info_fsnBody.mid(72, 2) << info_fsnBody.mid(76, 2)
            << info_fsnBody.mid(80, 2) << info_fsnBody.mid(84, 2)
            << info_fsnBody.mid(88, 2) << info_fsnBody.mid(92, 2)
            << info_fsnBody.mid(96, 2) << info_fsnBody.mid(100, 2)
            << info_fsnBody.mid(104, 2) << info_fsnBody.mid(108, 2);

        QString SNoInfo;
        for (int i = 0; i < HexStringToInt(CharNUMInfo); i++) {
            SNoInfo = SNoInfo.append(changefromHex_to_ascii(SNo[i]));
        }
        ui->tableWidget->setItem(RowCont, 7, new QTableWidgetItem(SNoInfo));
        //    qDebug() << "冠字号 = " << SNoInfo;

        //获取机具编号MachineSNo[24]

        ui->tableWidget->setItem(RowCont, 9, new QTableWidgetItem(MachineSNoInfo));
        //    qDebug() << "机具号 = " << MachineSNoInfo;

        //获取保留字1 Operateor_No
        QStringList Operateor_No;
        Operateor_No << info_fsnBody.mid(112, 2) << info_fsnBody.mid(114, 2)
                     << info_fsnBody.mid(116, 2) << info_fsnBody.mid(118, 2)
                     << info_fsnBody.mid(120, 2) << info_fsnBody.mid(122, 2)
                     << info_fsnBody.mid(124, 2) << info_fsnBody.mid(126, 2)
                     << info_fsnBody.mid(128, 2) << info_fsnBody.mid(130, 2)
                     << info_fsnBody.mid(132, 2) << info_fsnBody.mid(134, 2)
                     << info_fsnBody.mid(136, 2) << info_fsnBody.mid(138, 2)
                     << info_fsnBody.mid(140, 2) << info_fsnBody.mid(142, 2);

        //    qDebug() << "Operateor_No[0] = " << Operateor_No[0];
        //    qDebug() << "Operateor_No[1] = " << Operateor_No[1];
        ui->tableWidget->setItem(
            RowCont, 10,
            new QTableWidgetItem(
                Operateor_No[0] + Operateor_No[1] + Operateor_No[2] + Operateor_No[3] + Operateor_No[4] + Operateor_No[5] + Operateor_No[6] + Operateor_No[7] + Operateor_No[8] + Operateor_No[9] + Operateor_No[10] + Operateor_No[11] + Operateor_No[12] + Operateor_No[13] + Operateor_No[14] + Operateor_No[15]));
        //    qDebug() << "预留字 = "
        //             << Operateor_No[0] + Operateor_No[1] + Operateor_No[2] +
        //                    Operateor_No[3] + Operateor_No[4] + Operateor_No[5] +
        //                    Operateor_No[6] + Operateor_No[7] + Operateor_No[8] +
        //                    Operateor_No[9] + Operateor_No[10] + Operateor_No[11]
        //                    + Operateor_No[12] + Operateor_No[13] +
        //                    Operateor_No[14] + Operateor_No[15];

        //==================---------++++++++++++++++++++++++++_______________________+++++++++++++++++++++++
        //冠字号图像处理
        if (bFlag) {
            QByteArray image_Data_fsnBody;
            int fsnImageLength = sizeof(TImageSNo); //长度为1544
            image_Data_fsnBody = Data_fsnBody.mid(fsnBodyLength - fsnImageLength + 8, fsnImageLength - 8);
            //        QString image_info_fsnBody =
            //        ByteArrayToHexString(image_Data_fsnBody);
            //      qDebug() <<
            //      "----解析文件图像--------------------------------------------"
            //                  "------------";

            //获取图像冠字号码结构中的字符数  short Num 8个在上面处理
            //        QString fsnImageNum      = image_info_fsnBody.mid(0, 2);
            //        QString fsnImageHeight   = image_info_fsnBody.mid(4, 2);
            //        QString fsnImageWidth    = image_info_fsnBody.mid(8, 2);
            //        QString fsnImageReserve2 = image_info_fsnBody.mid(12, 4);
            //        qDebug() << "图像个数 = " << HexStringToInt(fsnImageNum);
            //        qDebug() << "图像高度 = " << HexStringToInt(fsnImageHeight);
            //        qDebug() << "图像宽度 = " << HexStringToInt(fsnImageWidth);
            //        qDebug() << "图像预留字段 = " << fsnImageReserve2;
            //        QByteArray image_Data_fsnBody_info;
            //        image_Data_fsnBody_info = image_Data_fsnBody.mid(8,
            //        fsnImageLength - 8);

            TImageSNoData sn[12];
            memcpy(&sn[0].Data[0], image_Data_fsnBody.data(), sizeof(TImageSNoData) * 12);
            QImage image;
            if (HexStringToInt(CharNUMInfo) == 10) {
                image = QImage(320, 32, QImage::Format_Mono);
            } else if (HexStringToInt(CharNUMInfo) == 11) {
                image = QImage(352, 32, QImage::Format_Mono);
            } else {
                image = QImage(384, 32, QImage::Format_Mono);
            }

            //qDebug() << "冠字号字符数：HexStringToInt(CharNUMInfo) = " << HexStringToInt(CharNUMInfo);
            for (int count = 0; count < HexStringToInt(CharNUMInfo); count++) {
                for (int i = 0; i < 32; i++) {
                    for (int j = 0; j < 32; j++) {
                        if (((sn[count].Data[i] >> j) & 0x01) == 0x01) {
                            image.setPixel(i + count * 32, (31 - j), 1);
                        } else {
                            image.setPixel(i + count * 32, (31 - j), 0);
                        }
                    }
                }
            }

            //添加图片的第一种方法（耗时严重，不采用）
            //        QLabel *label1 = new QLabel();
            //        label1->setScaledContents(true);  //设置图片适应label
            //        label1->setPixmap(QPixmap::fromImage(image));
            //        ui->tableWidget->setCellWidget(RowCont, 8, label1);  //显示label

            //添加图片的第二种方法（以图标方式显示冠字号图片，在图标后面显示冠字号码
            //-- QIcon(QPixmap::fromImage(image)), SNoInfo)）
            if (HexStringToInt(CharNUMInfo) == 10) {
                ui->tableWidget->setIconSize(QSize(320, 32));
            } else if (HexStringToInt(CharNUMInfo) == 11) {
                ui->tableWidget->setIconSize(QSize(352, 32));
            } else {
                ui->tableWidget->setIconSize(QSize(384, 32));
            }
            ui->tableWidget->setItem(RowCont, 8, new QTableWidgetItem(QIcon(QPixmap::fromImage(image)), ""));
            if (haveImage) {
                //            保存图片
                //            当m_image(一个QImage变量)中已经载入图片数据后，可调用save()进行保存，如：m_image.save(pictrureName, “JPG”, 100);对于这三个参数，解释如下：
                //            1.pictrureName为图片文件的路径，比如："/home/feng/IMG_0.jpg"，需要注意的是路径必须要有权限读写；
                //            2."JPG"为图片的格式，注意不需要带"."；
                //            3.100指的是图片的质量因数，范围必须在0到100之内或-1，指定0以获取小型压缩文件，指定100表示大型未压缩文件，使用-1（默认值）使用默认设置。

                QString pictrureName = QApplication::applicationDirPath() + "/imageTemp/" + QString::number(i) + ".jpg";
                //                qDebug() << i << ":测试图片保存速度->" << pictrureName;
                image.save(pictrureName, "jpg", 100);
            }
        }
        //关闭fsn文件
        file.close();
        if (bFlag) {
            start = start + fsnBodyLength; //加一个1644
        } else {
            start = start + fsnBodyLength - 1544; //加一个1644
        }
    }
}

// TODO 012、文件查询功能
void FsnTool::find(QTableWidget* table, int num, const QString& text)
{
    int rows = table->rowCount();
    int SNoNum = 0;
    bool bRowHidden = true;
    for (int i = 0; i < rows; i++) {
        //成功返回true  text参数表示大小写敏感
        if (num == 5) {
            if (table->item(i, num)->text() == text) { //面值需要=判断
                bRowHidden = false;
                SNoNum++;
            }
            table->setRowHidden(i, bRowHidden);
            bRowHidden = true;

        } else {
            if (table->item(i, num)->text().contains(text, Qt::CaseSensitive)) { //冠字号需要包含判断
                bRowHidden = false;
                SNoNum++;
            }
            table->setRowHidden(i, bRowHidden);
            bRowHidden = true;
        }
    }
    ui->label_fsn_num->setText(QString::number(SNoNum));
    SNoNum = 0;
}

// TODO 013、文件拖放功能，当用户拖动文件到窗口部件上时候，就会触发dragEnterEvent事件
void FsnTool::dragEnterEvent(QDragEnterEvent* event)
{
    qDebug() << "启动拖放文件";
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

// TODO 014、文件拖放后,触发解读文件，当用户放下这个文件后，就会触发dropEvent事件
void FsnTool::dropEvent(QDropEvent* event)
{
    //注意：这里如果有多文件存在，意思是用户一下子拖动了多个文件，而不是拖动一个目录
    //如果想读取整个目录，则在不同的操作平台下，自己编写函数实现读取整个目录文件名
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    //往文本框中追加文件名
    foreach (QUrl url, urls) {
        QString file_name = url.toLocalFile();
        //开始解析
        FsnTool::readyGo(file_name);
    }
}

// TODO 015、返回按钮被单击
void FsnTool::on_pushButton_6_clicked()
{
    find(ui->tableWidget, 7, "");
    qDebug() << "返回按钮被单击";
}

// TODO 016、冠字号查询按钮被单击
void FsnTool::on_pushButton_3_clicked()
{
    QString SNo = ui->lineEdit_SNo->text();
    find(ui->tableWidget, 7, SNo);
    qDebug() << "冠字号查询按钮被单击";
}

// TODO 017、面值查询按钮被单击
void FsnTool::on_pushButton_5_clicked()
{
    QString Valuta = ui->lineEdit_Valuta->text();
    qDebug() << "Valuta" << Valuta;
    if (Valuta == nullptr) {
        on_pushButton_6_clicked();
        return;
    }
    find(ui->tableWidget, 5, Valuta);
    qDebug() << "面值查询按钮被单击";
}

// TODO 018、时间查询按钮被单击
void FsnTool::on_pushButton_4_clicked()
{
    qDebug() << "时间查询按钮被单击";

    QDateTime startDatetime = ui->dateTimeEdit->dateTime();
    QDateTime endDatetime = ui->dateTimeEdit_2->dateTime();

    if (startDatetime > endDatetime) {
        QMessageBox mesg;
        mesg.warning(this, "警告", "查询开始时间晚于结束时间!");
        return;
    }

    int rows = ui->tableWidget->rowCount();
    int SNoNum = 0;
    bool bRowHidden = true;
    for (int i = 0; i < rows; i++) {
        if (QDateTime::fromString(ui->tableWidget->item(i, 0)->text(), "yyyy-MM-dd hh:mm:ss") >= startDatetime && QDateTime::fromString(ui->tableWidget->item(i, 0)->text(), "yyyy-MM-dd hh:mm:ss") <= endDatetime) {
            bRowHidden = false;
            SNoNum++;
        }
        ui->tableWidget->setRowHidden(i, bRowHidden);
        bRowHidden = true;
    }
    ui->label_fsn_num->setText(QString::number(SNoNum));
    SNoNum = 0;
}

// TODO 019、复选框选择
void FsnTool::checkBox_OnClick(int state)
{
    if (state == Qt::Checked) {
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        ui->checkBox_4->setCheckState(Qt::Unchecked);
        find(ui->tableWidget, 1, "Real");
    } else {
        on_pushButton_6_clicked();
    }
}
void FsnTool::checkBox_2_OnClick(int state)
{
    if (state == Qt::Checked) {
        ui->checkBox->setCheckState(Qt::Unchecked);
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        ui->checkBox_4->setCheckState(Qt::Unchecked);
        find(ui->tableWidget, 1, "Fake");
    } else {
        on_pushButton_6_clicked();
    }
}
void FsnTool::checkBox_3_OnClick(int state)
{
    if (state == Qt::Checked) {
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        ui->checkBox->setCheckState(Qt::Unchecked);
        ui->checkBox_4->setCheckState(Qt::Unchecked);
        find(ui->tableWidget, 1, "Damaged");
    } else {
        on_pushButton_6_clicked();
    }
}
void FsnTool::checkBox_4_OnClick(int state)
{
    if (state == Qt::Checked) {
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        ui->checkBox->setCheckState(Qt::Unchecked);
        find(ui->tableWidget, 1, "Old");
    } else {
        on_pushButton_6_clicked();
    }
}
void FsnTool::checkBox_image_OnClick(int state)
{
    if (state == Qt::Checked) {
        haveImage = true;
        qDebug() << "haveImage = true";
        QMessageBox::information(nullptr, "提示", "如果选择带图片导出Excel，需要重新解析一下FSN文件。");
    } else {
        haveImage = false;
        qDebug() << "haveImage = false";
        DelDir(QApplication::applicationDirPath() + "/imageTemp/");
    }
}

// TODO 020-01、ByteArray转QString ByteArrayToHexString
QString FsnTool::ByteArrayToHexString(QByteArray data)
{
    QString ret(data.toHex().toUpper());
    int len = ret.length() / 2;
    for (int i = 1; i < len; i++) {
        ret.insert(2 * i + i - 1, "");
    }
    return ret;
}

// TODO 020-02、十六进制转十进制 HexStringToInt
int FsnTool::HexStringToInt(QString info)
{
    char* str;
    QByteArray ba = info.toLatin1();
    str = ba.data();
    int n = strtol(str, nullptr, 16);
    //    qDebug() << "(" << info << ")转十进制 = " << n;
    //柬埔寨纸币100000元的钞票无法正常显示
    if (n == 34464) {
        n = 100000;
        return n;
    } else {
        return n;
    }
}

// TODO 020-03、十进制转二进制 IntToBinary
QString FsnTool::IntToBinary(int num)
{
    QString info = qPrintable(QString::number(num, 2));
    return info;
}

// TODO 020-04、二进制转10进制 BinaryToInt
int FsnTool::BinaryToInt(QString strBinary)
{
    int j = 1, value = 0;
    for (int i = 0; i < strBinary.length(); i++) {
        value += strBinary.mid(i, 1).toInt() * j;
        j *= 2;
    }
    return value;
}
// TODO 020-05、十进制转十六进制 IntToHexString
QByteArray FsnTool::IntToQByte(int num)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)(0x000000ff & num);
    abyte0[1] = (uchar)((0x0000ff00 & num) >> 8);
    abyte0[2] = (uchar)((0x00ff0000 & num) >> 16);
    abyte0[3] = (uchar)((0xff000000 & num) >> 24);
    return abyte0;
}

// TODO 020-05、返回16进制数的ascii码值 changefromHex_to_ascii
QString FsnTool::changefromHex_to_ascii(QString str)
{
    QString str_hex = str; //获取十六进制数
    int dec = str_hex.toInt(nullptr, 16); //十六进制转十进制
    char st = dec; //十进制数用char类型表示--->必须有此步直接转化不可行
    QString str_ascii = QString(st); //转化为ASCII值
    return str_ascii; //返回十六进制符号的ascii码值
}

// TODO 020-06、将字符串“000000000000029120”前面的0去掉，用递归方法
QString FsnTool::removeFirst0(QString s)
{
    if (!s.left(1).operator==("0"))
        return s;
    else
        return removeFirst0(s.right(s.length() - 1));
}

// TODO 021、Logo单击事件换皮肤
bool FsnTool::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->label_logo) //指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress) // mouse button pressed
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                setStyleSheet("background-color: rgb(120,120,120);"); //灰色
                QFile styleFile(":/fsntool.qss");
                styleFile.open(QIODevice::ReadOnly);
                if (styleFile.isOpen()) {
                    qDebug() << "设置皮肤";
                    QString btnstylesheet = QObject::tr(styleFile.readAll());
                    qApp->setStyleSheet(btnstylesheet);
                    styleFile.close();
                }

                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return FsnTool::eventFilter(obj, event);
    }
}

// TODO 023、看文件错误码
void FsnTool::slot_doubleClicked(int row, int column)
{
    qDebug() << "查看文件错误码,第" << row + 1 << "行,"
             << "第" << column + 1 << "列,被单击！";
    QTableWidgetItem* item = new QTableWidgetItem;
    item = ui->tableWidget->item(row, 7);
    SNo = item->text();

    QTableWidgetItem* item1 = new QTableWidgetItem;
    item1 = ui->tableWidget->item(row, 2);
    //去除获取到的“：”
    QString err = item1->text();
    QString Error1 = err.mid(0, 2);
    QString Error2 = err.mid(2, 2);
    QString Error3 = err.mid(5, 2);
    QString Error4 = err.mid(7, 2);
    QString Error5 = err.mid(10, 2);
    QString Error6 = err.mid(12, 2);
    //    QString Error7          = Error2 + Error1;
    //    QString Error8          = Error4 + Error3;
    //    QString Error9          = Error6 + Error5;
    QString Error7 = Error1 + Error2;
    QString Error8 = Error3 + Error4;
    QString Error9 = Error5 + Error6;

    //    qDebug() << "前 = " << Error7;
    //    qDebug() << "中 = " << Error8;
    //    qDebug() << "后 = " << Error9;

    //    int j = Error7.toInt();
    //    int o = Error8.toInt();
    //    int k = Error9.toInt();
    //    for (int i = 0; i < 16; i++) {
    //        if (j >> i & 0x01) {
    //            qDebug() << j << "-" << i << ":qqqq";
    //        }
    //    }

    QString BitError1 = IntToBinary(HexStringToInt(Error7));
    QString BitError2 = IntToBinary(HexStringToInt(Error8));
    QString BitError3 = IntToBinary(HexStringToInt(Error9));

    //    qDebug() << "BitError1 = " << BitError1;
    //    qDebug() << "BitError2 = " << BitError2;
    //    qDebug() << "BitError3 = " << BitError3;

    if (BitError1.length() != 16) {
        for (int i = BitError1.length(); i < 16; i++) {
            BitError1 = "0" + BitError1;
        }
    }

    if (BitError2.length() != 16) {
        for (int i = BitError2.length(); i < 16; i++) {
            BitError2 = "0" + BitError2;
        }
    }
    if (BitError3.length() != 16) {
        for (int i = BitError3.length(); i < 16; i++) {
            BitError3 = "0" + BitError3;
        }
    }
    QString NewBitError1;
    for (int i = 15; i >= 0; i--) {
        NewBitError1 = NewBitError1 + BitError1.mid(i, 1);
    }
    QString NewBitError2;
    for (int i = 15; i >= 0; i--) {
        NewBitError2 = NewBitError2 + BitError2.mid(i, 1);
    }
    QString NewBitError3;
    for (int i = 15; i >= 0; i--) {
        NewBitError3 = NewBitError3 + BitError3.mid(i, 1);
    }
    //设置全局变量数据
    AllError = NewBitError1 + NewBitError2 + NewBitError3;
    //    QMessageBox::information(nullptr, "提示", AllError);
    //显示错误码界面
    error_windows = new errorForm;
    error_windows->setWindowTitle(
        SNo + "：错误码"); // 此处写应用程序在标题栏上显示的名称
    error_windows->show();
}

// TODO 025、导出EXCEL表格
void FsnTool::on_pushButton_7_clicked()
{
    qDebug() << "导出Excel按钮被单击";
    QString fileName = ui->lineEdit_fsnName->text();
    QFileInfo fi;
    fi = QFileInfo(fileName);
    QString file_name;
    file_name = fi.fileName();
    Table2Excel(ui->tableWidget, file_name);
}
void FsnTool::Table2Excel(QTableWidget* table, QString title)
{
    QString fileName = QFileDialog::getSaveFileName(table, "保存", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Excel 文件(*.xlsx *.xls *.csv)");
    if (fileName != "") {
        QAxObject* excel = new QAxObject;
        if (excel->setControl("Excel.Application")) //连接Excel控件
        {
            excel->dynamicCall("SetVisible (bool Visible)", "false"); //不显示窗体
            excel->setProperty("DisplayAlerts", false); //不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
            QAxObject* workbooks = excel->querySubObject("WorkBooks"); //获取工作簿集合
            workbooks->dynamicCall("Add"); //新建一个工作簿
            QAxObject* workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
            QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);
            int i, j, colcount = table->columnCount();
            QAxObject *cell, *col;
            //标题行
            cell = worksheet->querySubObject("Cells(int,int)", 1, 1);
            cell->dynamicCall("SetValue(const QString&)", title);
            cell->querySubObject("Font")->setProperty("Size", 18);
            //调整行高
            worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
            //合并标题行
            QString cellTitle;
            cellTitle.append("A1:");
            cellTitle.append(QChar(colcount - 1 + 'A'));
            cellTitle.append(QString::number(1));
            QAxObject* range = worksheet->querySubObject("Range(const QString&)", cellTitle);
            range->setProperty("WrapText", true);
            range->setProperty("MergeCells", true);
            range->setProperty("HorizontalAlignment", -4108); // xlCenter
            range->setProperty("VerticalAlignment", -4108); // xlCenter
            //列标题
            for (i = 0; i < colcount; i++) {
                QString columnName;
                columnName.append(QChar(i + 'A'));
                columnName.append(":");
                columnName.append(QChar(i + 'A'));
                col = worksheet->querySubObject("Columns(const QString&)", columnName);
                col->setProperty("ColumnWidth", table->columnWidth(i) / 6);
                cell = worksheet->querySubObject("Cells(int,int)", 2, i + 1);
                columnName = table->horizontalHeaderItem(i)->text();
                cell->dynamicCall("SetValue(const QString&)", columnName);
                cell->querySubObject("Font")->setProperty("Bold", true);
                cell->querySubObject("Interior")->setProperty("Color", QColor(191, 191, 191));
                cell->setProperty("HorizontalAlignment", -4108); // xlCenter
                cell->setProperty("VerticalAlignment", -4108); // xlCenter
            }
            //数据区
            if (haveImage) {
                //num 在excel 中图片的上下位置
                double num = 45;
                for (i = 0; i < table->rowCount(); i++) {
                    for (j = 0; j < colcount; j++) {
                        worksheet->querySubObject("Cells(int,int)", i + 3, j + 1)->dynamicCall("SetValue(const QString&)", table->item(i, j) ? table->item(i, j)->text() : "");
                    }
                    QString picDir = QApplication::applicationDirPath() + "/imageTemp/" + QString::number(i) + ".jpg";
                    QAxObject* shapes = worksheet->querySubObject("Shapes");
                    shapes->dynamicCall("AddPicture( QString&, bool, bool, double, double, double, double)", QDir::toNativeSeparators(picDir), true, true, 521, num, 280, 28);
                    num = num + 13.5;
                }
                //删除图片临时文件夹
                DelDir(QApplication::applicationDirPath() + "/imageTemp/");
            } else {
                for (i = 0; i < table->rowCount(); i++) {
                    for (j = 0; j < colcount; j++) {
                        worksheet->querySubObject("Cells(int,int)", i + 3, j + 1)->dynamicCall("SetValue(const QString&)", table->item(i, j) ? table->item(i, j)->text() : "");
                    }
                }
            }

            //画框线
            QString lrange;
            lrange.append("A2:");
            lrange.append(colcount - 1 + 'A');
            lrange.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", lrange);
            range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
            range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
            //调整数据区行高
            QString rowsName;
            rowsName.append("2:");
            rowsName.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", rowsName);
            range->setProperty("RowHeight", 30);
            workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName)); //保存至fileName
            workbook->dynamicCall("Close()"); //关闭工作簿
            excel->dynamicCall("Quit()"); //关闭excel
            delete excel;
            excel = nullptr;
            if (QMessageBox::question(nullptr, "完成", "文件已经导出，是否现在打开？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                QDesktopServices::openUrl(
                    QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            }
        } else {
            QMessageBox::warning(nullptr, "错误", "未能创建 Excel 对象，请安装 Microsoft Excel。", QMessageBox::Apply);
        }
    }
}
// TODO 026、显示所有FSN文件信息
void FsnTool::on_pushButton_8_clicked()
{
    if (ui->listWidget_fsn->count() == 0) {
        QMessageBox::information(nullptr, "提示", "列表中无FSN文件");
        return;
    }
    int row = ui->tableWidget->rowCount();
    for (int i = row; i > 0; i--) {
        ui->tableWidget->removeRow(0);
    }
    showAll = false;
    for (int j = 0; j < ui->listWidget_fsn->count(); j++) {
        QString fsnFile = ui->listWidget_fsn->item(j)->text();
        FsnTool::readyGo(fsnFile);
    }
    showAll = true;
}

// TODO 027、合并所有FSN文件信息
void FsnTool::on_pushButton_10_clicked()
{
    allFsnVersion = 0;
    int version = 0;
    if (ui->listWidget_fsn->count() < 2) {
        QMessageBox::information(nullptr, "提示", "FSN文件少于2个，无法合并！");
        return;
    }

    QList<QString> files;
    for (int j = 0; j < ui->listWidget_fsn->count(); j++) {
        files.append(ui->listWidget_fsn->item(j)->text());
    }

    FSN_Header_Fromat g_header;
    QByteArray allBuf;
    QFile fileIn(files.at(0));
    fileIn.open(QFile::ReadOnly);
    allBuf = fileIn.readAll();
    fileIn.close();
    memcpy(&g_header, allBuf, sizeof(FSN_Header_Fromat));
    allBuf = allBuf.mid(sizeof(FSN_Header_Fromat));
    readFsnVersion(files.at(0));
    if (allFsnVersion == 2018) {
        QMessageBox::information(nullptr, "警告", "由于2018版FSN文件头不同，所以该功能暂时不支持2018版文件合并！");
        return;
    }
    version = allFsnVersion;

    FSN_Header_Fromat g_header_2;
    for (int i = 1; i < files.length(); i++) {
        readFsnVersion(files.at(i));
        if (version != allFsnVersion) {
            QMessageBox::information(nullptr, "提示", "列表中FSN文件版本不同，无法合并！");
            return;
        }
        QByteArray daBuf;
        QFile file(files.at(i));
        file.open(QFile::ReadOnly);
        daBuf = file.readAll();
        file.close();
        memcpy(&g_header_2, daBuf, sizeof(FSN_Header_Fromat));
        g_header.Counter += g_header_2.Counter;
        allBuf.append(daBuf.mid(sizeof(FSN_Header_Fromat)));
    }

    QDateTime curDateTime = QDateTime::currentDateTime();
    QString fsn = ui->lineEdit->text() + "/" + curDateTime.toString("yyyyMMddhhmmss") + ".fsn";
    QFile fileOut(fsn);
    fileOut.open(QIODevice::Append);
    fileOut.write((const char*)(unsigned char*)(&g_header), sizeof(FSN_Header_Fromat));
    fileOut.write(allBuf);
    fileOut.close();

    QString msgInfo = fsn + '\n' + "是否查看合并后的文件？";
    QMessageBox::StandardButton rb = QMessageBox::question(nullptr, "合并完成", msgInfo, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(ui->lineEdit->text()).absoluteFilePath()));
    }
}

//TODO 027、合并FSN文件->解析2014FSN文件信息。
void FsnTool::readFsnVersion(QString fsnPath)
{
    //读取文件
    QFile file(fsnPath);
    QByteArray Data;
    file.open(QIODevice::ReadOnly);
    Data = file.readAll();
    file.close();

    //数据取前32个字节
    QByteArray Data_fsnHead;
    Data_fsnHead = Data.mid(0, 32);
    QString info_fsnHead = ByteArrayToHexString(Data_fsnHead);
    QString HeadString = info_fsnHead.mid(16, 24);
    //判断fsn文件版本
    int fsnVer = HeadString.mid(4, 2).toInt();
    if (fsnVer == 1) {
        qDebug() << "文件版本 = 2014版FSN";
        allFsnVersion = 2014;
    } else if (fsnVer == 2) {
        qDebug() << "文件版本 = 2018版FSN";
        allFsnVersion = 2018;
        return;
    } else {
        qDebug() << "文件版本 = 无此版本";
        return;
    }
}

// TODO 029、删除文件夹函数
bool FsnTool::DelDir(const QString& path)
{
    if (path.isEmpty()) {
        return false;
    }
    QDir dir(path);
    if (!dir.exists()) {
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
    foreach (QFileInfo file, fileList) { //遍历文件信息
        if (file.isFile()) { // 是文件，删除
            file.dir().remove(file.fileName());
        } else { // 递归删除
            DelDir(file.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath()); // 删除文件夹
}

void FsnTool::on_pushButton_11_clicked()
{
    Table2Sql(ui->tableWidget);
}

void FsnTool::Table2Sql(QTableWidget* table)
{
    QString fileName = QFileDialog::getSaveFileName(table, "Save", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Sql(*.db)");
    if (fileName != "") {
        QSqlDatabase database;
        if (QSqlDatabase::contains("qt_sql_default_connection")) {
            database = QSqlDatabase::database("qt_sql_default_connection");
        } else {
            database = QSqlDatabase::addDatabase("QSQLITE");
            database.setDatabaseName(fileName);
            //        database.setUserName("julong");
            //        database.setPassword("123456");
        }
        if (!database.open()) {
            qDebug() << "Error: Failed to connect database." << database.lastError();
        } else {
            QSqlQuery sql_query;
            QString create_sql = "create table fsndata (id int primary key, MoneyFlag int, SNo varchar(30))";
            sql_query.prepare(create_sql);
            if (!sql_query.exec()) {
                qDebug() << "Error: Fail to create table." << sql_query.lastError();
            } else {
                qDebug() << "Table created!";
            }

            //add data
            QString insert_sql = "insert into fsndata values (?, ?, ?)";
            sql_query.prepare(insert_sql);
            int i = table->columnCount();
            for (i = 0; i < table->rowCount(); i++) {
                QString MoneyFlag = table->item(i, 3)->text();
                QString SNo = table->item(i, 7)->text();
                sql_query.addBindValue(QString::number(i + 1));
                sql_query.addBindValue(MoneyFlag);
                sql_query.addBindValue(SNo);
                if (!sql_query.exec()) {
                    qDebug() << sql_query.lastError();
                }
            }
            database.close();
            QMessageBox::information(nullptr, "", "Finish！");
        }
    }
}
