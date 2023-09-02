#pragma once

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QDialog>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QTextCodec>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRgb>
#include <QThread>
#include <QSound>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QMovie>

// 主窗口参数
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 960
#define WINDOW_BOUNDARY 64
#define CELL_SIZE 64
#define MAP_HEIGHT gameMap.m_height
#define MAP_WIDTH gameMap.m_width

// QTimer参数
#define MOUSE_MOVE_TIMER_INTERVAL 150
#define ANIMATION_DURATION 200
#define ZOOM_DURATION 300
#define CAPTURE_SCREEN_INTERVAL 3000

// 游戏参数
#define HP_HEIGHT 6
#define HP_DISTANCE 10
#define RELIVE 8



// 图片路径
#define MAP_PATH  "pic/map.png"
#define EGG_PATH "pic/EW/base.png"
#define WARRIOR_PATH "pic/EW/role1.png"
#define ASSASSIN_PATH "pic/EW/role2.png"
#define SHOOTER_PATH "pic/EW/role3.png"
#define MASTER_PATH "pic/EW/role4.png"
#define TANK_PATH "pic/EW/role5.png"
#define GUIDE1_PATH "pic/EWGuide/guide1.png"
#define GUIDE2_PATH "pic/EWGuide/guide2.png"
#define GUIDE3_PATH "pic/EWGuide/guide3.png"
#define GUIDE4_PATH "pic/EWGuide/guide4.png"
#define GUIDE5_PATH "pic/EWGuide/guide5.png"
#define GUIDE6_PATH "pic/EWGuide/guide6.png"
#define DLG_PATH "pic/EW/dlg.png"

#define HINT_BLUE_PATH "pic/EW/hintblue.png"
#define HINT_RED_PATH "pic/EW/hintred.png"
#define HINT_PATH "pic/EW/hint.png"

#define MAIN_SCENE_BACKGROUND_PATH "pic/EW/map1.webp"
#define MAIN_SCENE_GUIDE_BUTTON_PATH "pic/EW/GuideButton.png"
#define MAIN_SCENE_ONE_PLAYER_BUTTON_PATH "pic/EW/OnePlayerButton.png"
#define MAIN_SCENE_TWO_PLAYERS_BUTTON_PATH "pic/EW/TwoPlayersButton.png"
#define MAIN_SCENE_ICON_PATH "pic/EW/William.png"
#define MAIN_SCENE_BUTTON_PATH "pic/EW/button5.png"

// 音乐路径
#define BGM_PATH "music/bgm.wav"
#define ATTRACK_MUSIC_PATH "music/attrack.wav"
#define CLICK_MUSIC_PATH "music/click.wav"
#define GAME_BGM_PATH "music/gamebgm.wav"


//设置地图参数
#define MAP_ROW 15
#define MAP_COL 25
const int MAP[MAP_ROW + 1][MAP_COL + 1] = {
    {0,  0, 0, 0, 0, 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0},

    {0,  0, 0, 0, 0, 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
    {0,  0, 1, 1, 1, 1,     1, 1, 3, 1, 1,  1, 3, 0, 3, 1,  1, 1, 1, 3, 1,  1, 1, 1, 1, 0},
    {0,  0, 1, 3, 1, 1,     1, 1, 3, 1, 1,  1, 3, 3, 3, 1,  1, 1, 3, 2, 3,  0, 0, 3, 0, 0},
    {0,  0, 1, 1, 1, 1,     1, 3, 2, 3, 1,  1, 3, 3, 3, 1,  1, 0, 1, 3, 1,  1, 1, 1, 1, 0},
    {0,  0, 1, 1, 1, 1,     1, 1, 3, 1, 1,  0, 1, 1, 1, 1,  0, 1, 1, 1, 1,  1, 1, 1, 1, 0},

    {0,  0, 1, 1, 1, 1,     1, 1, 1, 1, 1,  1, 1, 1, 1, 3,  1, 1, 1, 1, 1,  1, 1, 1, 1, 0},
    {0,  0, 1, 1, 1, 1,     1, 3, 3, 3, 1,  1, 0, 3, 0, 1,  1, 2, 2, 2, 1,  1, 1, 1, 1, 0},
    {0,  0, 3, 2, 3, 3,     1, 3, 2, 3, 1,  1, 3, 1, 2, 1,  1, 2, 3, 2, 1,  2, 2, 3, 2, 0},
    {0,  0, 1, 1, 1, 1,     1, 3, 3, 3, 1,  1, 0, 2, 0, 1,  1, 2, 2, 2, 1,  1, 1, 1, 1, 0},
    {0,  0, 1, 1, 1, 1,     1, 1, 1, 1, 1,  2, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 0},

    {0,  0, 1, 1, 1, 1,     1, 1, 1, 1, 0,  1, 1, 1, 1, 0,  1, 1, 2, 1, 1,  1, 1, 1, 1, 0},
    {0,  0, 1, 1, 1, 1,     1, 2, 1, 0, 1,  1, 2, 2, 2, 1,  1, 2, 3, 2, 1,  1, 1, 1, 1, 0},
    {0,  0, 0, 2, 0, 0,     2, 3, 2, 1, 1,  1, 2, 2, 2, 1,  1, 1, 2, 1, 1,  1, 1, 2, 1, 0},
    {0,  0, 1, 1, 1, 1,     1, 2, 1, 1, 1,  1, 2, 0, 2, 1,  1, 1, 2, 1, 1,  1, 1, 1, 1, 0},
    {0,  0, 0, 0, 0, 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0}
};




// 最大最小值函数
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

// 常见变量名的别名
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int, int> node;

// 定义曼哈顿距离
inline int ManhattanDist(node x, node y)
{
    return abs(x.first - y.first) + abs(x.second - y.second);
}
inline int ManhattanDist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

// 一些枚举变量
enum BELONGING { RED, BLUE };
enum DERECTION { UP, DOWN, LEFT, RIGHT };

