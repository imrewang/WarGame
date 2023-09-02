#include "HomePage.h"


/*  MainScene是关于首页的类，有几个按钮和选择、教程两个页面等变量 */

HomePage::HomePage(QWidget* parent) :
	QDialog(parent)
{
	// 初始配置
	setWindowFlags(Qt::WindowCloseButtonHint);//Qt.WindowCloseButtonHint	窗口只有一个关闭按钮
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	setMouseTracking(true);
	setWindowTitle(QString("欧陆战争"));
	setWindowIcon(QPixmap(MAIN_SCENE_ICON_PATH));

	background.load(MAIN_SCENE_BACKGROUND_PATH);
	background = background.scaled(WINDOW_WIDTH, WINDOW_HEIGHT);

	homeBGM = new QSound(BGM_PATH, this);
	homeBGM->setLoops(QSound::Infinite);
	homeBGM->play();

	// 设置三个按键
	QPixmap buttonPixmap = QPixmap(MAIN_SCENE_BUTTON_PATH);


	// 按键1：显示教程
	homeButton[0] = new ClickLabel(400, 152, buttonPixmap, this, ClickLabel::TRANSPARENTSTYLE, "新手教程");
	homeButton[0]->move(610, 150);
	homeButton[0]->raise();
	homeButton[0]->show();

	// 按键2：人机模式
	homeButton[1] = new ClickLabel(400, 152, buttonPixmap, this, ClickLabel::TRANSPARENTSTYLE, "单人模式");
	homeButton[1]->move(610, 425);
	homeButton[1]->raise();
	homeButton[1]->show();

	// 按键3：双人模式
	homeButton[2] = new ClickLabel(400, 152, buttonPixmap, this, ClickLabel::TRANSPARENTSTYLE, "双人模式");
	homeButton[2]->move(610, 700);
	homeButton[2]->raise();
	homeButton[2]->show();

	tutorial = new Tutorial(this);

	connect(homeButton[0], &ClickLabel::clickedSignal, this, [=]() {

		zoom(homeButton[0]);

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {

			tutorial->show();

			QTime delayTime = QTime::currentTime().addMSecs(300);//延时300毫秒
			while (QTime::currentTime() < delayTime) {
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}

			this->hide();

			});

		}, Qt::UniqueConnection);

	// 按键2：人机模式
	connect(homeButton[1], &ClickLabel::clickedSignal, this, [=]() {
		zoom(homeButton[1]);
		homeBGM->stop();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			
			gameMode = HomePage::SINGLE_PLAYER;
			createGameScene(HomePage::SINGLE_PLAYER);

			QTime delayTime = QTime::currentTime().addMSecs(300);//延时300毫秒
			while (QTime::currentTime() < delayTime) {
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}

			this->hide();
			});

		}, Qt::UniqueConnection);

	// 按键3：双人模式
	connect(homeButton[2], &ClickLabel::clickedSignal, this, [=]() {
		zoom(homeButton[2]);
		homeBGM->stop();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			
			gameMode = HomePage::TWO_PLAYER;
			createGameScene(HomePage::TWO_PLAYER);

			QTime delayTime = QTime::currentTime().addMSecs(300);//延时300毫秒
			while (QTime::currentTime() < delayTime) {
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}

			this->hide();
			});

		}, Qt::UniqueConnection);
}

void HomePage::createGameScene(const int gameMode)
{
	// 下一关的函数
	gameScene = new GameScene(gameMode);

	// 处理游戏界面的退出信号
	connect(gameScene, &GameScene::exitSignal, this, [=]() {
		gameScene->close();
		
		gameScene = nullptr;

		homeBGM->play();
		this->show();
		}, Qt::UniqueConnection);

	// 处理游戏界面的重新开始游戏界面
	connect(gameScene, &GameScene::restartSignal, this, [&]() {
		gameScene->close();

		gameScene = nullptr;
		createGameScene(gameMode);
		}, Qt::UniqueConnection);

	gameScene->show();
}


void HomePage::paintEvent(QPaintEvent*)
{
	// 画背景
	QPainter painter(this);
	painter.drawPixmap(0, 0, background);
}

