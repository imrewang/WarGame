#include "mainscene.h"
#include "gamescene.h"
#include "character.h"
#include "config.h"
#include <QApplication>
#include <QMetaType>

int main(int argc, char* argv[])
{
    // 设置伪随机种子
    srand(time(0));

    QApplication a(argc, argv);

    

    MainScene w;
    w.show();
    return a.exec();
}