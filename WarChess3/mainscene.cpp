#include "mainscene.h"
#include "config.h"
#include <QTime>
#include "gamescene.h"
#include <QSharedPointer>

/*  MainScene是关于首页的类，有几个按钮和选择、教程两个页面等变量 */

MainScene::MainScene(QWidget* parent) :
	QDialog(parent)
{
	// 初始配置
	setWindowFlags(Qt::WindowCloseButtonHint);//Qt.WindowCloseButtonHint	窗口只有一个关闭按钮
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	setMouseTracking(true);
	setWindowTitle(QString("欧陆战争"));
	setWindowIcon(QPixmap(MAIN_SCENE_ICON_PATH));

	m_background.load(MAIN_SCENE_BACKGROUND_PATH);
	m_background = m_background.scaled(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_bgm = new QSound(BGM_PATH, this);
	m_bgm->setLoops(QSound::Infinite);
	m_bgm->play();

	// 设置三个按键
	QPixmap m_button_pixmap = QPixmap(MAIN_SCENE_BUTTON_PATH);


	// 按键1：显示教程
	m_button[0] = new ClickLabel(400, 152, m_button_pixmap, this, ClickLabel::TRANSPARENTSTYLE, "新手教程");
	m_button[0]->move(610, 150);
	m_button[0]->raise();
	m_button[0]->show();

	// 按键2：人机模式
	m_button[1] = new ClickLabel(400, 152, m_button_pixmap, this, ClickLabel::TRANSPARENTSTYLE, "单人模式");
	m_button[1]->move(610, 425);
	m_button[1]->raise();
	m_button[1]->show();

	// 按键3：双人模式
	m_button[2] = new ClickLabel(400, 152, m_button_pixmap, this, ClickLabel::TRANSPARENTSTYLE, "双人模式");
	m_button[2]->move(610, 700);
	m_button[2]->raise();
	m_button[2]->show();

	m_guideScene = new GuideScene(this);

	connect(m_button[0], &ClickLabel::clickedSignal, this, [=]() {

		zoom(m_button[0]);

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {

			m_guideScene->show();

			QTime dieTime = QTime::currentTime().addMSecs(300);//延时300毫秒
			while (QTime::currentTime() < dieTime) {
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}

			this->hide();

			});

		});

	// 按键2：人机模式
	connect(m_button[1], &ClickLabel::clickedSignal, this, [=]() {
		zoom(m_button[1]);
		m_bgm->stop();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			
			m_lastGameMode = SINGLE_PLAYER;
			createGameScene(SINGLE_PLAYER);

			QTime dieTime = QTime::currentTime().addMSecs(300);//延时300毫秒
			while (QTime::currentTime() < dieTime) {
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}

			this->hide();
			});

		});

	// 按键3：双人模式
	connect(m_button[2], &ClickLabel::clickedSignal, this, [=]() {
		zoom(m_button[2]);
		m_bgm->stop();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			
			m_lastGameMode = TWO_PLAYER;
			createGameScene(TWO_PLAYER);

			QTime dieTime = QTime::currentTime().addMSecs(300);//延时300毫秒
			while (QTime::currentTime() < dieTime) {
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}

			this->hide();
			});

		});
}

void MainScene::createGameScene(const int gameMode)
{
	// 下一关的函数
	m_gameScene = new GameScene(gameMode);
	//QSharedPointer<GameScene> m_gameScene(new GameScene(gameMode));

	//qDebug() << "mainscene.cpp MainScene::createGameScene 111" << endl;

	// 处理游戏界面的退出信号
	connect(m_gameScene, &GameScene::exitSignal, this, [=]() {
		//qDebug() << "mainscene.cpp MainScene::createGameScene exitSignal" << endl;
		m_gameScene->close();
		
		//delete gameScene;
		//delete m_gameScene;
		m_gameScene = nullptr;

		m_bgm->play();
		this->show();
		});

	// 处理游戏界面的重新开始游戏界面
	connect(m_gameScene, &GameScene::restartSignal, this, [&]() {
		//qDebug() << "mainscene.cpp MainScene::createGameScene restartSignal" << endl;
		m_gameScene->close();
		//delete gameScene;
		//delete m_gameScene;//设置了setAttribute(Qt::WA_DeleteOnClose);所以不用了吧

		m_gameScene = nullptr;
		createGameScene(m_lastGameMode);
		});

	m_gameScene->show();
	//qDebug() << "mainscene.cpp MainScene::createGameScene 222" << endl;
	//this->hide();
}


void MainScene::paintEvent(QPaintEvent*)
{
	// 画背景
	QPainter painter(this);
	painter.drawPixmap(0, 0, m_background);
}

