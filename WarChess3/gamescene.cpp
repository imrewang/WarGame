#include "gamescene.h"


/*  GameScene是关于游戏页面的类，包含游戏运行的所有内容，可以视为游戏的运行引擎 */

void GameScene::InterfaceInit() {
	// 设置屏幕格式
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	setMouseTracking(true);
	setWindowTitle(QString("欧陆战争"));
	setWindowIcon(QPixmap(MAIN_SCENE_ICON_PATH));
	setAttribute(Qt::WA_DeleteOnClose);

	m_mouseCellx = 0; m_mouseCelly = 0;
	m_gameState = GameScene::BEGIN;
	m_game_number = 1;
	m_characterNum = 10;

	for (int i = 0; i < m_characterNum; i++) {
		m_character_relive[i] = -1;
	}

	// 设置音乐和音效
	m_bgm = new QSound(GAME_BGM_PATH, this);
	m_bgm->setLoops(QSound::Infinite);
	m_attrackSound = new QSound(ATTRACK_MUSIC_PATH, this);
	m_clickSound = new QSound(CLICK_MUSIC_PATH, this);

	// 设置左上角四个按钮
	setButton();

	// 设置消息提示框
	m_hint = new HintLabel(this);
	m_hint->hide();
}

GameScene::GameScene(const int gameMode, QWidget* parent)
	: QDialog(parent), m_map(GameMap())
{

	InterfaceInit();


	// 角色创建相关内容
	createCharacter();
	createBase();
	m_aliveNum[RED] = m_aliveNum[BLUE] = 0;
	for (int i = 0; i < m_characterNum; i++) {
		m_aliveNum[m_character[i]->m_belong]++;
	}
	m_roundBelonged = BLUE;
	receiveHint("蓝方回合", BLUE);
	m_roundNum[RED] = m_aliveNum[RED];
	m_roundNum[BLUE] = m_aliveNum[BLUE];

	m_nowCharacter = nullptr;
	// 与角色相关的信号与槽
	for (int i = 0; i < m_characterNum; i++)
	{

		m_character[i]->installEventFilter(this);
		// 重绘屏幕
		connect(m_character[i], &Character::repaintScreen, this, [=]() {repaint(); });
		// 触发人物移动事件
		connect(m_character[i], &Character::characterMoveAction, this, &GameScene::characterMoveEvent);
		// 触发人物攻击事件
		connect(m_character[i], &Character::characterAttrackAction, this, &GameScene::characterAttrackEvent);
		// 触发跳过一个人事件
		connect(m_character[i], &Character::endOneCharacter, this, &GameScene::endOneCharacterEvent);
		// 触发死去一个人事件
		connect(m_character[i], &Character::dieOneCharacter, this, &GameScene::dieOneCharacterEvent);
		// 触发显示提示框事件
		void (GameScene:: * studentSlot)(QString) = &GameScene::receiveHint;
		connect(m_character[i], &Character::submitHint, this, studentSlot);
		// 触发隐藏取消键事件
		connect(m_character[i], &Character::hideCancelButton, this, [=]() {emit m_cancelButton->clicked(); });

	}

	//  与基地有关的信号与槽
	RedBase->installEventFilter(this);
	connect(RedBase, &Base::repaintScreen, this, [=]() {repaint(); });
	connect(RedBase, &Base::dieOneBase, this, &GameScene::dieOneBaseEvent);

	BlueBase->installEventFilter(this);
	connect(BlueBase, &Base::repaintScreen, this, [=]() {repaint(); });
	connect(BlueBase, &Base::dieOneBase, this, &GameScene::dieOneBaseEvent);


	// 与AI有关的初始化
	m_AIOpenOrNot = gameMode;
	m_aiController = new AIController(m_character, m_characterNum, this);
	connect(m_aiController, &AIController::AIRoundBegin, this, [=]() {m_skipButton->hide(); });
	connect(m_aiController, &AIController::AIRoundFinished, this, [=]() {m_skipButton->show(); nextRound(RED); });

	// 与显示游戏结果有关的初始化
	m_resultMenu = new ResultMenu(this);
	m_resultMenu->hide();

	connect(m_resultMenu, &ResultMenu::exitGame, this, [=]() {m_bgm->stop(); emit exit(); });
	connect(m_resultMenu, &ResultMenu::restartGame, this, [=]() {m_bgm->stop(); emit restart(); });
	connect(this, &GameScene::myWin, [=]() {
		m_hint->close();
		m_skipButton->close();
		m_menuButton->close();
		m_musicButton->close();
		m_resultMenu->setResult(1, m_AIOpenOrNot);
		m_resultMenu->show();
		m_resultMenu->raise();
		//这里要加一个让当前回合角色不被选中的东西
		});
	connect(this, &GameScene::myLoss, [=]() {
		m_hint->close();
		m_skipButton->close();
		m_menuButton->close();
		m_musicButton->close();

		m_resultMenu->setResult(0, m_AIOpenOrNot);
		//QTimer::singleShot(500, this, [=]() {

		m_resultMenu->show();
		m_resultMenu->raise();
		//});
		});




	// 与游戏时菜单按钮有关的初始化
	m_playingMenu = new PlayingMenu(this);
	m_playingMenu->hide();
	connect(m_playingMenu, &PlayingMenu::exitGame, this, [=]() {m_bgm->stop(); emit exit(); });
	connect(m_playingMenu, &PlayingMenu::restartGame, this, [=]() {m_bgm->stop(); emit restart(); });


	// 初始时重绘人物
	for (int i = 0; i < m_characterNum; i++)
	{
		redrawCharacter();
		if (m_character[i]->m_characterState != Character::DEAD) {
			m_character[i]->updateInfo();
		}
	}
	//绘制一下基地
	redrawBase();

}

GameScene::~GameScene()
{
	qDebug() << "~GameScene()析构函数" << endl;
}


// 创建人物函数
void GameScene::createCharacter()
{
	// 初始人物个数：10
	m_characterNum = 10;
	// 临时记录人物的格子位置
	int tempx[10], tempy[10];

	// 循环随机生成位置直至位置合法
	for (int i = 0; i < m_characterNum; i++)
	{
		while (true)
		{
			bool success = true;
			// 随机生成位置
			tempx[i] = rand() % m_map.m_maxCellx + 1;
			tempy[i] = rand() % m_map.m_maxCelly + 1;
			// 生成的在阻挡地形上则不成功
			if (GameMap::binMap[tempx[i]][tempy[i]] == 0) {
				success = false;
			}
			// 生成的与前面重复则不成功
			for (int j = 0; j < i; j++)
			{
				if (tempx[j] == tempx[i] && tempy[j] == tempy[i])
					success = false;
			}
			// 成功则退出循环
			if (success) {
				break;
			}
		}
	}
	// 为蓝方设置人物
	m_character[0] = new Sultan(tempx[0], tempy[0], BLUE, this);
	m_character[1] = new Teutonic(tempx[1], tempy[1], BLUE, this);
	m_character[2] = new Hussars(tempx[2], tempy[2], BLUE, this);
	m_character[3] = new Dragoon(tempx[3], tempy[3], BLUE, this);
	m_character[4] = new Mamluk(tempx[4], tempy[4], BLUE, this);
	// 为红方设置人物
	m_character[5] = new Sultan(tempx[5], tempy[5], RED, this);
	m_character[6] = new Teutonic(tempx[6], tempy[6], RED, this);
	m_character[7] = new Hussars(tempx[7], tempy[7], RED, this);
	m_character[8] = new Dragoon(tempx[8], tempy[8], RED, this);
	m_character[9] = new Mamluk(tempx[9], tempy[9], RED, this);
}

void GameScene::createBase()
{
	RedBase = new Egg(13, 2, RED, this);
	BlueBase = new Egg(13, 14, BLUE, this);
}

// 设置事件过滤器，防止人物将主界面挡住无法获取鼠标坐标
bool GameScene::eventFilter(QObject* watched, QEvent* event)
{
	// 如果被观察的是Character类
	if (watched->metaObject()->className() == QStringLiteral("Character"))
	{
		Character* now = qobject_cast<Character*>(watched);
		// 如果鼠标触发进入人物事件，则根据人物坐标更新当前鼠标坐标
		if (event->type() == QEvent::Enter)
		{
			m_mouseCellx = now->m_cellx;
			m_mouseCelly = now->m_celly;
			repaint();
			return false;
		}
	}
	return false;
}
// 设置屏幕四个按钮
void GameScene::setButton()
{
	int GAME_BUTTON_WIDTH = CELL_SIZE;
	int GAME_BUTTON_HEIGHT = CELL_SIZE;
	// 取消按钮
	m_cancelButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/cancel_button.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	m_cancelButton->setGeometry(1 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	m_cancelButton->setStyleSheet("border:none;");
	m_cancelButton->hide();

	// 跳过按钮
	m_skipButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/skip_button.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	m_skipButton->setGeometry(2 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	m_skipButton->setStyleSheet("border:none;");
	m_skipButton->raise();

	// 音乐按钮
	m_musicButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/music_button_off.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	m_musicButton->setGeometry(3 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	m_musicButton->setStyleSheet("border:none;");
	m_musicButton->raise();

	// 菜单按钮
	m_menuButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/menu_button.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	m_menuButton->setGeometry(4 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	m_menuButton->setStyleSheet("border:none;");
	m_menuButton->raise();


	// 如果触发取消按钮，则取消寻路/攻击，展开人物操作栏
	connect(m_cancelButton, &ClickLabel::clicked, this, [=]() {

		zoom(m_cancelButton);
		m_clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {

			if (m_nowCharacter->m_characterState == Character::DEAD) {
				return;
			}
			m_nowCharacter->m_characterState = Character::BEGIN;
			//m_nowCharacter->m_selectionDlg->show();
			//m_nowCharacter->m_selectionDlg->raise();
			m_gameState = BEGIN;
			m_cancelButton->hide();
			repaint();

			});

		});

	// 如果触发跳过按钮，则开启下一轮
	connect(m_skipButton, &ClickLabel::clicked, this, [=]() {
		zoom(m_skipButton);
		m_clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			m_cancelButton->hide();
			if (m_nowCharacter) {
				m_nowCharacter->m_selectionDlg->hide();
			}
			nextRound(m_roundBelonged);
			});

		});


	// 如果触发音乐按钮，则判断当前音乐状态并切换图片和音乐状态
	connect(m_musicButton, &ClickLabel::clicked, this, [=]() {
		zoom(m_musicButton);
		m_clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {

			if (m_bgm->isFinished() == true)
			{
				m_musicButton->setPixmap(QPixmap("pic/music_button_on.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
				m_musicButton->repaint();
				m_bgm->play();
			}
			else
			{
				m_musicButton->setPixmap(QPixmap("pic/music_button_off.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
				m_musicButton->repaint();
				m_bgm->stop();
			}
			});
		});
	// 如果触发菜单按键，则展开菜单
	connect(m_menuButton, &ClickLabel::clicked, this, [=]() {
		zoom(m_menuButton);
		m_clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			m_playingMenu->show();
			m_playingMenu->raise();
			});
		});
}
void GameScene::redrawCharacter()const
{
	// 重画所有人物
	for (int i = 0; i < m_characterNum; i++)
	{
		// 如果人物已死则不画
		if (m_character[i]->m_characterState == Character::DEAD) {
			continue;
		}
		m_character[i]->setGeometry((m_character[i]->m_cellx - 1) * CELL_SIZE,
			(m_character[i]->m_celly - 1) * CELL_SIZE, 64, 64);
		m_character[i]->show();
	}
}

void GameScene::redrawBase()const
{
	if (RedBase->ALIVE == true) {
		RedBase->show();
		RedBase->setGeometry((RedBase->m_cellx - 1) * CELL_SIZE,
			(RedBase->m_celly -1) * CELL_SIZE, CELL_SIZE, CELL_SIZE);

		RedBase->updateInfo();
	}
	if (BlueBase->ALIVE == true) {
		BlueBase->show();
		BlueBase->setGeometry((BlueBase->m_cellx - 1) * CELL_SIZE,
			(BlueBase->m_celly - 1) * CELL_SIZE, CELL_SIZE, CELL_SIZE);

		BlueBase->updateInfo();
	}
}

void GameScene::ReliveCharacter(int id) {
	qDebug() << "GameScene::ReliveCharacter(int id)" << id << endl;
	m_character[id]->m_characterState = Character::BEGIN;
	m_character[id]->m_attrackedOrNot = false;
	m_character[id]->m_move = m_character[id]->m_fullmove;
	m_character[id]->m_hp = m_character[id]->m_fullhp;

	int tempx, tempy;
	while (true) {
		bool success = true;
		tempx = rand() % MAP_COL + 1;
		tempy = rand() % MAP_ROW + 1;

		if (GameMap::binMap[tempx][tempy] == 0) {
			success = false;
		}
		for (int i = 0; i < m_characterNum; i++) {
			if (m_character[i]->m_characterState != Character::DEAD && i != id &&
				tempx == m_character[i]->m_cellx && tempy == m_character[i]->m_celly) {
				success = false;
			}
		}
		if (success) {
			break;
		}
	}
	m_character[id]->m_cellx = tempx;
	m_character[id]->m_celly = tempy;

	m_aliveNum[m_character[id]->m_belong] ++;

	m_character[id]->updateInfo();
	redrawCharacter();
}
void GameScene::nextRound(int last)
{
	if (m_gameState == END) {
		return;
	}

	// 改变游戏基本状态
	int next = last ^ 1;//1-1，0+1
	m_roundBelonged = next;
	m_gameState = BEGIN;

	if (RedBase->m_belong == last) {
		emit RedBase->beAttracked(-30);
	}
	else {
		emit BlueBase->beAttracked(-30);
	}

	for (int i = 0; i < m_characterNum; i++)
	{
		// 人物已死则不操作
		if (m_character[i]->m_characterState == Character::DEAD) {
			continue;
		}
		// 更新下一回合character，满血、满行动力
		if (m_character[i]->m_belong == next)
		{
			m_character[i]->m_characterState = Character::BEGIN;
			m_character[i]->m_attrackedOrNot = false;
			m_character[i]->m_move = m_character[i]->m_fullmove;
			emit m_character[i]->infoChanged();//character.cpp33
		}
		// 更新上一回合character，看看在哪一种地形上，如果是相同属性的话就加血，不同属性则扣血
		else
		{
			m_character[i]->m_selectionDlg->hide();

			if (m_character[i]->m_belong == RED) {
				if (GameMap::binMap[m_character[i]->m_cellx][m_character[i]->m_celly] == 3) {
					emit m_character[i]->beAttracked(-20);
				}
				else if (GameMap::binMap[m_character[i]->m_cellx][m_character[i]->m_celly] == 2) {
					emit m_character[i]->beAttracked(20);
					
				}
			}
			else {
				if (GameMap::binMap[m_character[i]->m_cellx][m_character[i]->m_celly] == 3) {
					
					emit m_character[i]->beAttracked(20);
					
				}
				else if (GameMap::binMap[m_character[i]->m_cellx][m_character[i]->m_celly] == 2) {
					emit m_character[i]->beAttracked(-20);
				}
			}
		}
	}//for (int i = 0; i < m_characterNum; i++)

	m_roundNum[next] = m_aliveNum[next];


	for (int i = 0; i < m_characterNum; i++) {
		if (m_character[i]->m_characterState == Character::DEAD) {
			if (m_character_relive[i] == RELIVE) {//RELIVE 16
				m_character_relive[i] = -1;
				ReliveCharacter(i);

			}
			else {
				m_character_relive[i] += 1;
			}

		}
	}
	m_game_number++;

	// 如果没开ai则提示红方/蓝方
	if (m_AIOpenOrNot == false)
	{
		if (next == RED) {
			receiveHint("红方回合", RED);
		}
		else {
			receiveHint("蓝方回合", BLUE);
		}
	}
	else// 如果开了ai则提示对方/己方
	{
		if (next == RED) {
			receiveHint("对方回合", RED);
		}
		else {
			receiveHint("我方回合", BLUE);
		}
	}

	// 如果开了ai且下一轮为ai，则调用函数
	if (m_AIOpenOrNot == true && next == RED)
	{
		m_gameState = AI;
		AIRound();
	}
	repaint();
}

// 调用aicontroller以完成ai回合
void GameScene::AIRound()const
{
	m_aiController->reset(m_aliveNum[RED]);
	m_aiController->start();
}

// 人物将要移动
void GameScene::characterMoveEvent(Character* t_nowCharacter)
{
	// 改变人物状态
	m_gameState = FINDPATH;
	m_cancelButton->show();
	m_nowCharacter = t_nowCharacter;
	int tempx = m_nowCharacter->m_cellx;
	int tempy = m_nowCharacter->m_celly;
	// 让Algorithm为人物寻路
	moveAl.init(m_nowCharacter->m_move, m_nowCharacter);
	moveAl.findAvailableCell(tempx, tempy, 0, m_character, m_characterNum);
	// 如果四周都没有路，则给出提示
	if (moveAl.m_resultMap[tempx + 1][tempy] < 0 && moveAl.m_resultMap[tempx - 1][tempy] < 0
		&& moveAl.m_resultMap[tempx][tempy + 1] < 0 && moveAl.m_resultMap[tempx][tempy - 1] < 0)
	{
		receiveHint("没有可移至的地块");
		emit m_cancelButton->clicked();
	}
	repaint();
}
void GameScene::characterAttrackEvent(Character* t_nowCharacter)
{
	// 改变人物状态
	m_gameState = FINDATTRACK;
	m_cancelButton->show();
	m_nowCharacter = t_nowCharacter;
	attrackAl.init(m_nowCharacter->m_attrackable, m_nowCharacter);
	bool findOneOrNot = false;
	//寻找可攻击目标并标出


	if (RedBase->m_belong != m_roundBelonged) {
		EnemyBase = RedBase;
	}
	else {
		EnemyBase = BlueBase;
	}

	if (ManhattanDist(EnemyBase->m_cellx, EnemyBase->m_celly,
		m_nowCharacter->m_cellx, m_nowCharacter->m_celly) <= m_nowCharacter->m_attrackable)
	{
		attrackAl.m_resultMap[EnemyBase->m_cellx][EnemyBase->m_celly] = 1;
		attrackAl.m_availableCell.push_back(node(EnemyBase->m_cellx, EnemyBase->m_celly));
		findOneOrNot = true;
	}

	for (int i = 0; i < m_characterNum; i++)
	{
		if (m_character[i]->m_belong == m_roundBelonged || m_character[i]->m_characterState == Character::DEAD) {
			continue;//友军
		}


		if (ManhattanDist(m_character[i]->m_cellx, m_character[i]->m_celly,
			m_nowCharacter->m_cellx, m_nowCharacter->m_celly) <= m_nowCharacter->m_attrackable)
		{
			attrackAl.m_resultMap[m_character[i]->m_cellx][m_character[i]->m_celly] = 1;
			attrackAl.m_availableCell.push_back(node(m_character[i]->m_cellx, m_character[i]->m_celly));
			findOneOrNot = true;
		}
	}

	repaint();

	// 如果没有可攻击的对象
	if (findOneOrNot == false)
	{
		receiveHint("没有可攻击的对象");
		QTimer::singleShot(500, this, [=]() {emit m_cancelButton->clicked(); });
	}
}
// 跳过一个人后触发
void GameScene::endOneCharacterEvent(Character* endedCharacter)
{
	int id = -1;
	// 找到跳过的人id
	for (int i = 0; i < m_characterNum; i++)
	{
		if (m_character[i] == endedCharacter)
		{
			id = i;
			break;
		}
	}
	// 当前回合人物数改变，如果为0则下一回合
	m_roundNum[m_character[id]->m_belong]--;

	qDebug() << "endOneCharacterEvent   :::" << m_roundNum[m_character[id]->m_belong] << endl;

	m_cancelButton->hide();

	if (m_roundNum[m_character[id]->m_belong] == 0) {
		nextRound(m_character[id]->m_belong);
	}
}
// 死人后触发
void GameScene::dieOneCharacterEvent(Character* deadCharacter)
{
	int id = -1;
	// 找到死人id
	for (int i = 0; i < m_characterNum; i++)
	{
		if (m_character[i] == deadCharacter)
		{
			id = i;
			break;
		}
	}
	/*int alive = 0;
	for (int i = 0; i < m_characterNum; i++) {
		if (m_character[i]->m_belong == deadCharacter->m_belong && id != i && m_character[i]->m_characterState != Character::DEAD) {
			alive++;
		}
	}

	m_aliveNum[m_character[id]->m_belong] = alive;*/
	m_aliveNum[m_character[id]->m_belong]--;

	// 如果人死完了则判定游戏结果
	if (m_aliveNum[m_character[id]->m_belong] == 0)
	{
		m_hint->hide();
		m_gameState = END;
		if (m_character[id]->m_belong == BLUE) {
			emit myLoss();
		}
		else {
			emit myWin();
		}
		return;
	}
	repaint();
}

void GameScene::dieOneBaseEvent(Base* deadBase) {
	m_gameState = END;
	if (deadBase->m_belong == BLUE) {
		emit myLoss();
	}
	else {
		emit myWin();
	}
	return;
}

void GameScene::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	// 画背景图
	painter.drawPixmap(0, 0, m_map.m_pic);
	// 如果游戏结束就不画了
	if (m_gameState == END) {
		return;
	}

	// 将右下角四个按钮置顶
	if (m_skipButton->isHidden() == false) {
		m_skipButton->raise();
	}
	if (m_cancelButton->isHidden() == false) {
		m_cancelButton->raise();
	}
	m_menuButton->raise();
	m_musicButton->raise();



	// 画右上角回合提示
	if (m_roundBelonged == RED) {
		painter.setBrush(QBrush(QColor(117, 27, 19)));
	}
	else {
		painter.setBrush(QBrush(QColor(36, 169, 255)));
	}
	painter.drawRect((MAP_COL - 6) * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
	painter.setBrush(Qt::white);
	painter.drawRect((MAP_COL - 5) * CELL_SIZE, 0, CELL_SIZE * 5, CELL_SIZE);
	painter.setBrush(Qt::NoBrush);

	if (m_roundBelonged == RED) {
		painter.setPen(QColor(117, 57, 59));
	}
	else {
		painter.setPen(QColor(36, 199, 205));
	}
	QFont font("宋体", 16, 40, false);
	font.setPixelSize(CELL_SIZE * 1);
	painter.setFont(font);
	painter.drawText((MAP_COL - 5) * CELL_SIZE + 16, CELL_SIZE - 10, QString("第%1轮%2人").arg((m_game_number - 1) / 2 + 1).arg(m_aliveNum[m_roundBelonged]));
	painter.setPen(Qt::NoPen);

	// 当前地块用方框标白
	painter.setPen(QPen(Qt::white, 4));
	if (m_map.binMap[m_mouseCellx][m_mouseCelly] != 0) {
		painter.drawRect((m_mouseCellx - 1) * CELL_SIZE,
			(m_mouseCelly - 1) * CELL_SIZE,
			CELL_SIZE, CELL_SIZE);
	}
	painter.setPen(Qt::NoPen);

	// 如果游戏状态是寻路状态，则标可行域
	if (m_gameState == FINDPATH)
	{
		for (int i = 1; i <= m_map.m_maxCellx; i++)
			for (int j = 1; j <= m_map.m_maxCelly; j++)
				if (moveAl.m_resultMap[i][j] >= 0)
				{
					painter.setPen(QPen(QColor(64, 116, 52), 1, Qt::DotLine));//painter.setPen(QPen(QColor(64, 116, 52), 2, Qt::DotLine));
					painter.setBrush(QBrush(QColor(57, 84, 116, 82)));
					painter.drawRect((i - 1) * CELL_SIZE,
						(j - 1) * CELL_SIZE,
						CELL_SIZE, CELL_SIZE);
					painter.setPen(Qt::NoPen);
					painter.setBrush(Qt::NoBrush);
				}
	}

	// 如果游戏状态是寻找攻击对象状态，则标出攻击范围和可攻击对象
	else if (m_gameState == FINDATTRACK)
	{
		// 寻找可攻击对象
		for (ull i = 0; i < attrackAl.m_availableCell.size(); i++)
		{
			painter.setPen(QPen(Qt::red, 1));
			painter.setBrush(QBrush(QColor(205, 20, 57, 180)));
			painter.drawRect((attrackAl.m_availableCell[i].first - 1) * CELL_SIZE,
				(attrackAl.m_availableCell[i].second - 1) * CELL_SIZE,
				CELL_SIZE, CELL_SIZE);
			painter.setPen(Qt::NoPen);
			painter.setBrush(Qt::NoBrush);
		}
		// 画可攻击范围
		for (int i = m_nowCharacter->m_cellx - m_nowCharacter->m_attrackable; i <= m_nowCharacter->m_cellx + m_nowCharacter->m_attrackable; i++)
			for (int j = m_nowCharacter->m_celly - m_nowCharacter->m_attrackable; j <= m_nowCharacter->m_celly + m_nowCharacter->m_attrackable; j++)
			{
				if (i <= 1 || i >= MAP_COL) {
					continue;
				}
				if (j <= 1 || j >= MAP_ROW) {
					continue;
				}
				if (ManhattanDist(i, j, m_nowCharacter->m_cellx, m_nowCharacter->m_celly) > m_nowCharacter->m_attrackable) {
					continue;
				}
				painter.setPen(QPen(QColor(255, 150, 0), 1, Qt::DotLine));
				painter.drawRect((i - 1) * CELL_SIZE,
					(j - 1) * CELL_SIZE,
					CELL_SIZE, CELL_SIZE);
				painter.setPen(Qt::NoPen);
			}
	}
}
void GameScene::mousePressEvent(QMouseEvent* event)
{

	// 如果是右击则相当于取消按钮
	if (event->button() == Qt::RightButton)
	{
		if (m_cancelButton->isHidden() == false) {
			emit m_cancelButton->clicked();
		}
		return;
	}
	// 更新当前鼠标位置
	updateMousePosition(event);

	// 如果是ai回合则不用等待进一步处理点击
	if (m_AIOpenOrNot == true && m_gameState == AI) {
		return;
	}


	// 如果是选择人物阶段
	if (m_gameState == BEGIN)
	{
		//选择对话框
		for (int i = 0; i < m_characterNum; i++)
		{
			// 人物并非被选择阶段则跳过
			if (m_character[i]->m_characterState == Character::DEAD) {
				continue;
			}
			// 敌军跳过
			if (m_character[i]->m_belong != m_roundBelonged) {
				continue;
			}
			else
			{   // 点错收回选择框
				if (m_character[i]->m_selectionDlg->isHidden() == false) {
					m_character[i]->m_selectionDlg->hide();
				}
			}
			// 点中了人物则展示操作框
			if (m_mouseCellx == m_character[i]->m_cellx && m_mouseCelly == m_character[i]->m_celly)
			{
				// 如果跳过了或/////////////////////////////////////////////////////
				if (m_character[i]->m_characterState == Character::END)
				{
					receiveHint("本回合该角色已结束");
					//qDebug() << "本回合已跳过已结束";
					continue;
				}
				else if (m_character[i]->m_characterState == Character::DEAD) {
					continue;
				}

				m_clickSound->play();
				//显示选择框
				if (m_character[i]->m_selectionDlg->isHidden())
				{
					m_character[i]->m_selectionDlg->show();
					//m_character[i]->m_selectionDlg->updateData(m_mouseCellx, m_mouseCelly);
					m_character[i]->m_selectionDlg->updateData(m_character[i]->m_cellx, m_character[i]->m_celly);
					m_character[i]->m_selectionDlg->raise();
				}
				break;
			}
			else
			{   //点错收回选择框
				if (m_character[i]->m_selectionDlg->isHidden() == false) {
					m_character[i]->m_selectionDlg->hide();
				}
			}
		}

	}
	// 如果是寻路阶段
	else if (m_gameState == FINDPATH)
	{
		// 如果点中可行域，则执行人物移动
		if (moveAl.m_resultMap[m_mouseCellx][m_mouseCelly] >= 0)
		{
			for (int i = 0; i < m_characterNum; i++) {
				if (m_character[i]->m_belong == m_nowCharacter->m_belong&& m_character[i] != m_nowCharacter && m_character[i]->m_characterState != Character::DEAD) {
					if (m_character[i]->m_cellx == m_mouseCellx&& m_character[i]->m_celly == m_mouseCelly) { //友军可以通行但不能重叠
						return;
					}
				}
			}
			m_clickSound->play();
			moveAl.findPath(m_nowCharacter->m_cellx, m_nowCharacter->m_celly, m_mouseCellx, m_mouseCelly, 0, moveAl.m_resultMap[m_mouseCellx][m_mouseCelly]);
			m_nowCharacter->movePos(moveAl.m_resultMap[m_mouseCellx][m_mouseCelly], moveAl.m_path);
			m_cancelButton->hide();
			m_gameState = BEGIN;
			if (m_nowCharacter->m_characterState != Character::DEAD) {
				m_nowCharacter->m_characterState = Character::BEGIN;
			}

			// 等待移动完毕，发动结算机制
			if (m_nowCharacter->m_move <= 0) {
				connect(m_nowCharacter->m_mover, &MoveAnimation::animationFinished, this, [=]() {
					m_gameState = BEGIN;
					//m_nowCharacter->m_characterState = BEGIN;
					if (m_nowCharacter->m_move <= 0) {
						//m_nowCharacter->m_move = 0;
						m_nowCharacter->m_attrackedOrNot = true;

						m_nowCharacter->m_characterState = Character::END;
						m_nowCharacter->m_selectionDlg->hide();
						emit m_nowCharacter->endOneCharacter(m_nowCharacter);
					}
					});
			}

			repaint();
		}
		else {
			return;
		}
		
	}

	// 如果是寻找攻击目标阶段
	else if (m_gameState == FINDATTRACK)
	{
		//在攻击范围内
		if (attrackAl.m_resultMap[m_mouseCellx][m_mouseCelly] != -1)
		{
			//是否还可以继续攻击判断
			if(m_nowCharacter->m_move<=3){
				m_nowCharacter->m_move = 0;
			}
			else {
				m_nowCharacter->m_move -= 3;
			}
			m_nowCharacter->updateInfo();


			//敌方基地判断
			if (RedBase->m_belong != m_roundBelonged) {
				EnemyBase = RedBase;
			}
			else {
				EnemyBase = BlueBase;
			}

			//这个是判断是否是基地
			if (EnemyBase->m_cellx == m_mouseCellx && EnemyBase->m_celly == m_mouseCelly)//点中
			{

				m_cancelButton->hide();
				m_nowCharacter->m_attracker->startMove(m_nowCharacter, m_nowCharacter->m_cellx, m_nowCharacter->m_celly,
					EnemyBase->m_cellx, EnemyBase->m_celly);
				// 等待攻击完毕，发动结算机制
				connect(m_nowCharacter->m_attracker, &AttrackAnimation::animationFinished, this, [=]() {
					emit EnemyBase->beAttracked(m_nowCharacter->m_attrack);
					disconnect(m_nowCharacter->m_attracker, 0, this, 0); //仅结算一次，因此要断连
					m_gameState = BEGIN;
					//m_nowCharacter->m_characterState = BEGIN;
					if (m_nowCharacter->m_move == 0) {
						//m_nowCharacter->m_move = 0;
						m_nowCharacter->m_attrackedOrNot = true;

						m_nowCharacter->m_characterState = Character::END;
						m_nowCharacter->m_selectionDlg->hide();
						emit m_nowCharacter->endOneCharacter(m_nowCharacter);
					}
					});
			}


			//这个是遍历人物
			//qDebug() << "mx:" << m_mouseCellx << "my:" << m_mouseCelly << endl;
			for (int i = 0; i < m_characterNum; i++)
			{
				//qDebug() << "x:" << m_character[i]->m_cellx << "y:" << m_character[i]->m_celly << endl;
				if (m_character[i]->m_cellx == m_mouseCellx && m_character[i]->m_celly == m_mouseCelly&& m_character[i]->m_characterState != Character::DEAD)//点中
				{
					//qDebug() << "m_attrack:" << m_character[i]->m_attrack << endl;
					if (m_character[i]->m_belong == m_roundBelonged )//友军
					{
						m_clickSound->play();
						m_gameState = BEGIN;
						m_nowCharacter->m_characterState = Character::BEGIN;
						m_nowCharacter->m_attrackedOrNot = false;
						break;
					}
					//qDebug() << "m_armor:" << m_character[i]->m_armor << endl;
					
					m_cancelButton->hide();
					m_nowCharacter->m_attracker->startMove(m_nowCharacter, m_nowCharacter->m_cellx, m_nowCharacter->m_celly,
						m_character[i]->m_cellx, m_character[i]->m_celly);
					// 等待攻击完毕，发动结算机制
					connect(m_nowCharacter->m_attracker, &AttrackAnimation::animationFinished, this, [=]() {
						emit m_character[i]->beAttracked(m_nowCharacter->m_attrack);
						disconnect(m_nowCharacter->m_attracker, 0, this, 0); //仅结算一次，因此要断连
						
						m_gameState = BEGIN;
						//m_nowCharacter->m_characterState = BEGIN;
						if (m_nowCharacter->m_move == 0) {
							//m_nowCharacter->m_move = 0;
							m_nowCharacter->m_attrackedOrNot = true;

							m_nowCharacter->m_characterState = Character::END;
							m_nowCharacter->m_selectionDlg->hide();
							emit m_nowCharacter->endOneCharacter(m_nowCharacter);
						}
						});
					break;
				}
			}
		}
		else//偷懒了
		{
			m_gameState = BEGIN;
			m_nowCharacter->m_characterState = Character::BEGIN;
			m_nowCharacter->m_attrackedOrNot = false;
		}
		repaint();
	}

}
// 调用则显示提示框
void GameScene::receiveHint(const QString str, const bool next)const
{
	m_hint->setText(str, next);
	m_hint->show();
	m_hint->raise();
	QTimer::singleShot(1500, this, [=]() { m_hint->hide(); });
}

// 调用则显示提示框
void GameScene::receiveHint(QString str)
{
	m_hint->setText(str, 2);
	m_hint->show();
	m_hint->raise();
	QTimer::singleShot(1500, this, [=]() { m_hint->hide(); });
}

// 如果鼠标移动则更新鼠标坐标
void GameScene::mouseMoveEvent(QMouseEvent* event)
{
	updateMousePosition(event);
	update();
}
// 更新鼠标坐标
void GameScene::updateMousePosition(QMouseEvent* event)
{
	QPointF point = event->localPos();
	// 绝对坐标
	m_mousex = point.x();
	m_mousey = point.y();
	// 绝对格子坐标
	m_mouseCellx = (m_mousex) / CELL_SIZE + 1;
	m_mouseCelly = (m_mousey) / CELL_SIZE + 1;
	// 相对格子坐标

}




