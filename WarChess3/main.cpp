#include "HomePage.h"
#include "GameScene.h"
#include "Role.h"
#include "config.h"
#include <QApplication>
#include <QMetaType>

int main(int argc, char* argv[])
{
    // 设置伪随机种子
    srand(time(0));

    QApplication a(argc, argv);

    HomePage w;
    w.show();
    return a.exec();
}