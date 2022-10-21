#include "fsntool.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    FsnTool w;
    w.show();
    //文件设置默认打开，导入的dat文件名argv[1]
    if (argv[1] != nullptr) {
        w.readyGo(QString::fromLocal8Bit(argv[1]));
    }
    return a.exec();
}
