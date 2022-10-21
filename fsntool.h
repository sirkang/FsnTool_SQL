#ifndef FSNTOOL_H
#define FSNTOOL_H

#include "errorform.h"
#include <QListWidgetItem>
#include <QMainWindow>
#include <QTableWidget>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class FsnTool;
}
QT_END_NAMESPACE

/**
* @SirKang 文件头
*/
typedef struct
{
    USHORT HeadStart[4]; /**< 开始标识 */
    USHORT HeadString[6]; /**< 文件基础信息 */
    UINT Counter; /**< 冠字号张数 */
    USHORT HeadEnd[4]; /**< 结束标识 */
} FSN_Header_Fromat;

#pragma pack(1) //设置结构体为1字节对齐
typedef struct {
    USHORT HeadStart[4]; /*开始标识 */
    USHORT HeadString[6]; /*文件基础信息 */
    USHORT HeadDatatypeFlag; /*机具信息记录格式标识*/
    UINT Counter; /*冠字号张数 */
    USHORT FinanIns[6]; /*金融机构缩写*/
    UINT Enabletime; /*设备启用时间*/
    USHORT MachineSNo[24]; /*机具编号*/
    USHORT MachineType[15]; /*机具类型*/
    USHORT MachineModel[24]; /*机具型号*/
    USHORT HardVerNo[24]; /*硬件版本号*/
    USHORT AuthSoftVerNo[24]; /*软件版本号*/
    USHORT Appli_denom[6]; /*适用券别*/
    USHORT FinanInst[14]; /*报送银行*/
    USHORT FinanInstOutlet[14]; /*报送网点*/
    USHORT Operator[4]; /*操作人员*/
    USHORT Reserve1; /*保留字1*/
    USHORT HeadEnd[4]; /*文件头结束标识*/
} FSN_2018Header_Fromat;
#pragma pack() //结束结构体对齐设置
/**
* @SirKang 单个图像结构
*/
typedef struct
{
    unsigned int Data[32]; /**< 图像冠字号点阵数据 */
} TImageSNoData;

/**
* @SirKang 图像冠字号码结构
*/
typedef struct
{
    short Num; /**< 字符数 */
    short Height, Width; /**< 每个图像字符高度和宽度 */
    short Reserve2; /**< 保留字2 */
    TImageSNoData SNo[12];
} TImageSNo;

/**
* @SirKang 文件记录结构
*/
typedef struct
{
    USHORT Date; /**< 验钞启动日期 Date=((Year-1980)<<9)+(Month<<5)+Day*/
    USHORT Time; /**< 验钞启动时间 Time=(Hour<<11)+(Minute<<5)+(Second>>1)*/
    USHORT tfFlag; /**< 真、假、残和旧币标志 */
    USHORT ErrorCode[3]; /**< 错误码(3个) */
    USHORT MoneyFlag[4]; /**< 货币标志 */
    USHORT Ver; /**< 版本号 */
    USHORT Valuta; /**< 币值 */
    USHORT CharNUM; /**< 冠字号码字符数 */
    USHORT SNo[12]; /**< 冠字号码 */
    USHORT MachineSNo[24]; /**< 机具编号 */
    USHORT Operateor_No; /**< 保留字1 */
    TImageSNo ImageSNo; /**< 冠字号码图像 */
} FSN_BodyData_Fromat;

typedef struct {
    USHORT Date; //验钞启动日期
    USHORT Time; //验钞启动时间
    USHORT tfFlag; //真、假、残和旧币标志
    USHORT ErrorCode[3]; //错误码(3个)
    USHORT MoneyFlag[4]; //货币标志
    USHORT Ver; //版本号
    ULONG Valuta; //币值
    USHORT CharNUM; //冠字号码字符数
    USHORT SNo[12]; //冠字号码
    USHORT Reserve2[16]; //保留字2
    TImageSNo ImageSNo; //图像冠字号码
} FSN_2108BodyData_Fromat;

class FsnTool : public QMainWindow {
    Q_OBJECT

public:
    FsnTool(QWidget* parent = nullptr);
    ~FsnTool();
    void findFile(QString path);
    void fsnRead(QString fanPath);
    void fsnReadFor2018(QString);
    void toInfo();
    void OpenFileSLOT();
    void readyGo(QString fsnFile);
    QString ByteArrayToHexString(QByteArray data);
    int HexStringToInt(QString info);
    QString IntToBinary(int Sum);
    int BinaryToInt(QString strBinary);
    QByteArray IntToQByte(int num);
    QString changefromHex_to_ascii(QString str);
    QString removeFirst0(QString s);
    void find(QTableWidget* table, int num, const QString& text);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    void checkBox_OnClick(int state);
    void checkBox_2_OnClick(int state);
    void checkBox_3_OnClick(int state);
    void checkBox_4_OnClick(int state);
    void checkBox_image_OnClick(int state);
    bool eventFilter(QObject* obj, QEvent* event);
    void setAppSize(int remainH);
    Ui::FsnTool* ui;

    void Table2Sql(QTableWidget* table);
    void Table2Excel(QTableWidget* table, QString title);
private slots:
    void on_pushButton_clicked();
    void on_listWidget_fsn_currentTextChanged(const QString& fsnFile);
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void slot_doubleClicked(int row, int column);
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();

private:
    errorForm* error_windows;

public slots:
    bool DelDir(const QString& path);
    void readFsnVersion(QString fsnPath);
};

#endif // FSNTOOL_H
