#include "GameScene.h"


/*  GameScene是关于游戏页面的类，包含游戏运行的所有内容，可以视为游戏的运行引擎 */

void GameScene::interfaceInit() {
	// 设置屏幕格式
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	setMouseTracking(true);
	setWindowTitle(QString("欧陆战争"));
	setWindowIcon(QPixmap(MAIN_SCENE_ICON_PATH));
	setAttribute(Qt::WA_DeleteOnClose);

	mouseGridX = 0; mouseGridY = 0;
	gameState = GameScene::START;
	roundNum = 1;
	totalRolesNum = 10;

	for (int i = 0; i < totalRolesNum; i++) {
		waitRevivedRoles[i] = -1;
	}

	// 设置音乐和音效
	backgroundMusic = new QSound(GAME_BGM_PATH, this);
	backgroundMusic->setLoops(QSound::Infinite);
	attackSound = new QSound(ATTRACK_MUSIC_PATH, this);
	clickSound = new QSound(CLICK_MUSIC_PATH, this);

	// 设置左上角四个按钮
	setButtons();

	// 设置消息提示框
	hintLabel = new HintLabel(this);
	hintLabel->hide();
}

GameScene::GameScene(const int gameMode, QWidget* parent)
	: QDialog(parent), gameMap(GameMap())
{

	interfaceInit();


	// 角色创建相关内容
	createRoles();
	createBases();
	aliveNum[RED] = aliveNum[BLUE] = 0;
	for (int i = 0; i < totalRolesNum; i++) {
		aliveNum[rolesArray[i]->belong]++;
	}
	roundBelong = BLUE;
	showHintSlot("蓝方回合", BLUE);
	canMoveNum[RED] = aliveNum[RED];
	canMoveNum[BLUE] = aliveNum[BLUE];

	currentRole = nullptr;
	// 与角色相关的信号与槽
	for (int i = 0; i < totalRolesNum; i++)
	{

		rolesArray[i]->installEventFilter(this);
		// 重绘屏幕
		connect(rolesArray[i], &Role::repaintScreenSignal, this, [=]() { repaint(); });
		// 触发人物移动事件
		connect(rolesArray[i], &Role::roleMoveSignal, this, &GameScene::findPathSlot);
		// 触发人物攻击事件
		connect(rolesArray[i], &Role::roleAttackSignal, this, &GameScene::findEnemiesSlot);
		// 触发跳过一个人事件
		connect(rolesArray[i], &Role::roleSkipSignal, this, &GameScene::roleEndSlot);
		// 触发死去一个人事件
		connect(rolesArray[i], &Role::killRoleSignal, this, &GameScene::roleDiesSlot);
		// 触发显示提示框事件
		void (GameScene:: * studentSlot)(QString) = &GameScene::showHintSlot;
		connect(rolesArray[i], &Role::displayHintLabelSignal, this, studentSlot);
		// 触发隐藏取消键事件
		connect(rolesArray[i], &Role::hideCancelButtonSignal, this, [=]() {emit cancelButton->clickedSignal(); });

	}

	//  与基地有关的信号与槽
	RedBase->installEventFilter(this);
	connect(RedBase, &Base::repaintScreenSignal, this, [=]() {repaint(); });
	connect(RedBase, &Base::killBaseSignal, this, &GameScene::baseDestroyedSlot);

	BlueBase->installEventFilter(this);
	connect(BlueBase, &Base::repaintScreenSignal, this, [=]() {repaint(); });
	connect(BlueBase, &Base::killBaseSignal, this, &GameScene::baseDestroyedSlot);


	// 与AI有关的初始化
	isAIOpen = gameMode;
	aiController = new AIController(rolesArray, totalRolesNum, this);
	connect(aiController, &AIController::AIRoundBegin, this, [=]() {skipButton->hide(); });
	connect(aiController, &AIController::AIRoundFinished, this, [=]() {skipButton->show(); nextRound(RED); });

	// 与显示游戏结果有关的初始化
	resultMenu = new ResultMenu(this);
	resultMenu->hide();

	connect(resultMenu, &ResultMenu::exitGame, this, [=]() {backgroundMusic->stop(); emit &GameScene::exitSignal; });
	connect(resultMenu, &ResultMenu::restartGame, this, [=]() {backgroundMusic->stop(); emit &GameScene::restartSignal; });
	connect(this, &GameScene::myWinSignal, [=]() {
		hintLabel->close();
		skipButton->close();
		menuButton->close();
		musicButton->close();
		resultMenu->setResult(1, isAIOpen);
		resultMenu->show();
		resultMenu->raise();
		//这里要加一个让当前回合角色不被选中的东西
		});
	connect(this, &GameScene::myLossSignal, [=]() {
		hintLabel->close();
		skipButton->close();
		menuButton->close();
		musicButton->close();

		resultMenu->setResult(0, isAIOpen);
		//QTimer::singleShot(500, this, [=]() {

		resultMenu->show();
		resultMenu->raise();
		//});
		});




	// 与游戏时菜单按钮有关的初始化
	playingMenu = new PlayingMenu(this);
	playingMenu->hide();
	connect(playingMenu, &PlayingMenu::exitGame, this, [=]() {backgroundMusic->stop(); emit &GameScene::exitSignal; });
	connect(playingMenu, &PlayingMenu::restartGame, this, [=]() {backgroundMusic->stop(); emit &GameScene::restartSignal; });


	// 初始时重绘人物
	for (int i = 0; i < totalRolesNum; i++)
	{
		redrawRoleSlot();
		if (rolesArray[i]->pieceState != Role::DEAD) {
			rolesArray[i]->updateInfoSlot();
		}
	}
	//绘制一下基地
	redrawBaseSlot();

}

GameScene::~GameScene()
{
	qDebug() << "~GameScene()析构函数" << endl;
}


// 创建人物函数
void GameScene::createRoles()
{
	// 初始人物个数：10
	totalRolesNum = 10;
	// 临时记录人物的格子位置
	int tempx[10], tempy[10];

	// 循环随机生成位置直至位置合法
	for (int i = 0; i < totalRolesNum; i++)
	{
		while (true)
		{
			bool success = true;
			// 随机生成位置
			tempx[i] = rand() % gameMap.m_maxCellx + 1;
			tempy[i] = rand() % gameMap.m_maxCelly + 1;
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
	rolesArray[0] = new Sultan(tempx[0], tempy[0], BLUE, this);
	rolesArray[1] = new Teutonic(tempx[1], tempy[1], BLUE, this);
	rolesArray[2] = new Hussars(tempx[2], tempy[2], BLUE, this);
	rolesArray[3] = new Dragoon(tempx[3], tempy[3], BLUE, this);
	rolesArray[4] = new Mamluk(tempx[4], tempy[4], BLUE, this);
	// 为红方设置人物
	rolesArray[5] = new Sultan(tempx[5], tempy[5], RED, this);
	rolesArray[6] = new Teutonic(tempx[6], tempy[6], RED, this);
	rolesArray[7] = new Hussars(tempx[7], tempy[7], RED, this);
	rolesArray[8] = new Dragoon(tempx[8], tempy[8], RED, this);
	rolesArray[9] = new Mamluk(tempx[9], tempy[9], RED, this);
}

void GameScene::createBases()
{
	RedBase = new Base(13, 2, RED, this);
	BlueBase = new Base(13, 14, BLUE, this);
}

// 设置事件过滤器，防止人物将主界面挡住无法获取鼠标坐标
bool GameScene::eventFilter(QObject* watched, QEvent* event)
{
	// 如果被观察的是Character类
	if (watched->metaObject()->className() == QStringLiteral("Role"))
	{
		Role* now = qobject_cast<Role*>(watched);
		// 如果鼠标触发进入人物事件，则根据人物坐标更新当前鼠标坐标
		if (event->type() == QEvent::Enter)
		{
			mouseGridX = now->cellX;
			mouseGridY = now->cellY;
			repaint();
			return false;
		}
	}
	return false;
}

// 设置屏幕四个按钮
void GameScene::setButtons()
{
	int GAME_BUTTON_WIDTH = CELL_SIZE;
	int GAME_BUTTON_HEIGHT = CELL_SIZE;
	// 取消按钮
	cancelButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/cancel_button.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	cancelButton->setGeometry(1 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	cancelButton->setStyleSheet("border:none;");
	cancelButton->hide();

	// 跳过按钮
	skipButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/skip_button.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	skipButton->setGeometry(2 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	skipButton->setStyleSheet("border:none;");
	skipButton->raise();

	// 音乐按钮
	musicButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/music_button_off.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	musicButton->setGeometry(3 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	musicButton->setStyleSheet("border:none;");
	musicButton->raise();

	// 菜单按钮
	menuButton = new ClickLabel(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, QPixmap("pic/menu_button.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation), this, ClickLabel::TRANSPARENTSTYLE);
	menuButton->setGeometry(4 * CELL_SIZE, 0, GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT);
	menuButton->setStyleSheet("border:none;");
	menuButton->raise();


	// 如果触发取消按钮，则取消寻路/攻击，展开人物操作栏
	connect(cancelButton, &ClickLabel::clickedSignal, this, [=]() {

		zoom(cancelButton);
		clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {

			if (currentRole->pieceState == Role::DEAD) {
				return;
			}
			currentRole->pieceState = Role::BEGIN;
			//m_nowCharacter->m_selectionDlg->show();
			//m_nowCharacter->m_selectionDlg->raise();
			gameState = START;
			cancelButton->hide();
			repaint();

			});

		});

	// 如果触发跳过按钮，则开启下一轮
	connect(skipButton, &ClickLabel::clickedSignal, this, [=]() {
		zoom(skipButton);
		clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			cancelButton->hide();
			if (currentRole) {
				currentRole->selection->hide();
			}
			nextRound(roundBelong);
			});

		});


	// 如果触发音乐按钮，则判断当前音乐状态并切换图片和音乐状态
	connect(musicButton, &ClickLabel::clickedSignal, this, [=]() {
		zoom(musicButton);
		clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {

			if (backgroundMusic->isFinished() == true)
			{
				musicButton->setPixmap(QPixmap("pic/music_button_on.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
				musicButton->repaint();
				backgroundMusic->play();
			}
			else
			{
				musicButton->setPixmap(QPixmap("pic/music_button_off.png").scaled(GAME_BUTTON_WIDTH, GAME_BUTTON_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation));
				musicButton->repaint();
				backgroundMusic->stop();
			}
			});
		});
	// 如果触发菜单按键，则展开菜单
	connect(menuButton, &ClickLabel::clickedSignal, this, [=]() {
		zoom(menuButton);
		clickSound->play();

		QTimer::singleShot(ZOOM_DURATION * 1.5, this, [=]() {
			playingMenu->show();
			playingMenu->raise();
			});
		});
}
void GameScene::redrawRoleSlot()const
{
	// 重画所有人物
	for (int i = 0; i < totalRolesNum; i++)
	{
		// 如果人物已死则不画
		if (rolesArray[i]->pieceState == Role::DEAD) {
			continue;
		}
		rolesArray[i]->setGeometry((rolesArray[i]->cellX - 1) * CELL_SIZE,
			(rolesArray[i]->cellY - 1) * CELL_SIZE, 64, 64);
		rolesArray[i]->show();
	}
}

void GameScene::redrawBaseSlot()const
{
	if (RedBase->pieceState == Base::BEGIN) {
		RedBase->show();
		RedBase->setGeometry((RedBase->cellX - 1) * CELL_SIZE,
			(RedBase->cellY -1) * CELL_SIZE, CELL_SIZE, CELL_SIZE);

		RedBase->updateInfoSlot();
	}
	if (BlueBase->pieceState == Base::BEGIN) {
		BlueBase->show();
		BlueBase->setGeometry((BlueBase->cellX - 1) * CELL_SIZE,
			(BlueBase->cellY - 1) * CELL_SIZE, CELL_SIZE, CELL_SIZE);

		BlueBase->updateInfoSlot();
	}
}

void GameScene::reviveRole(int id) {
	qDebug() << "GameScene::ReliveCharacter(int id)::" << id << endl;
	rolesArray[id]->pieceState = Role::BEGIN;
	rolesArray[id]->curMove = rolesArray[id]->maxMove;
	rolesArray[id]->curHp = rolesArray[id]->maxHp;

	int tempx, tempy;
	while (true) {
		bool success = true;
		tempx = rand() % MAP_COL + 1;
		tempy = rand() % MAP_ROW + 1;

		if (GameMap::binMap[tempx][tempy] == 0) {
			success = false;
		}
		for (int i = 0; i < totalRolesNum; i++) {
			if (rolesArray[i]->pieceState != Role::DEAD && i != id &&
				tempx == rolesArray[i]->cellX && tempy == rolesArray[i]->cellY) {
				success = false;
			}
		}
		if (success) {
			break;
		}
	}
	rolesArray[id]->cellX = tempx;
	rolesArray[id]->cellY = tempy;

	aliveNum[rolesArray[id]->belong] ++;

	rolesArray[id]->updateInfoSlot();
	redrawRoleSlot();
}
void GameScene::nextRound(int last)
{
	if (gameState == END) {
		return;
	}

	// 改变游戏基本状态
	int next = last ^ 1;//1-1，0+1
	roundBelong = next;
	gameState = START;

	if (RedBase->belong == last) {
		emit RedBase->beAttackedSignal(-30);
	}
	else {
		emit BlueBase->beAttackedSignal(-30);
	}

	for (int i = 0; i < totalRolesNum; i++)
	{
		// 人物已死则不操作
		if (rolesArray[i]->pieceState == Role::DEAD) {
			continue;
		}
		// 更新下一回合character，满血、满行动力
		if (rolesArray[i]->belong == next)
		{
			rolesArray[i]->pieceState = Role::BEGIN;
			rolesArray[i]->curMove = rolesArray[i]->maxMove;
			emit rolesArray[i]->infoChangedSignal();//character.cpp33
		}
		// 更新上一回合character，看看在哪一种地形上，如果是相同属性的话就加血，不同属性则扣血
		else
		{
			rolesArray[i]->selection->hide();

			if (rolesArray[i]->belong == RED) {
				if (GameMap::binMap[rolesArray[i]->cellX][rolesArray[i]->cellY] == 3) {
					emit rolesArray[i]->beAttackedSignal(-20);
				}
				else if (GameMap::binMap[rolesArray[i]->cellX][rolesArray[i]->cellY] == 2) {
					emit rolesArray[i]->beAttackedSignal(20);
					
				}
			}
			else {
				if (GameMap::binMap[rolesArray[i]->cellX][rolesArray[i]->cellY] == 3) {
					
					emit rolesArray[i]->beAttackedSignal(20);
					
				}
				else if (GameMap::binMap[rolesArray[i]->cellX][rolesArray[i]->cellY] == 2) {
					emit rolesArray[i]->beAttackedSignal(-20);
				}
			}
		}
	}//for (int i = 0; i < totalRolesNum; i++)

	canMoveNum[next] = aliveNum[next];


	for (int i = 0; i < totalRolesNum; i++) {
		if (rolesArray[i]->pieceState == Role::DEAD) {
			if (waitRevivedRoles[i] == RELIVE) {//RELIVE 16
				waitRevivedRoles[i] = -1;
				reviveRole(i);

			}
			else {
				waitRevivedRoles[i] += 1;
			}

		}
	}
	roundNum++;

	// 如果没开ai则提示红方/蓝方
	if (isAIOpen == false)
	{
		if (next == RED) {
			showHintSlot("红方回合", RED);
		}
		else {
			showHintSlot("蓝方回合", BLUE);
		}
	}
	else// 如果开了ai则提示对方/己方
	{
		if (next == RED) {
			showHintSlot("对方回合", RED);
		}
		else {
			showHintSlot("我方回合", BLUE);
		}
	}

	// 如果开了ai且下一轮为ai，则调用函数
	if (isAIOpen == true && next == RED)
	{
		gameState = AI;
		startAIRound();
	}
	repaint();
}

// 调用aicontroller以完成ai回合
void GameScene::startAIRound()const
{
	aiController->reset(aliveNum[RED]);
	aiController->start();
}

// 人物将要移动
void GameScene::findPathSlot(Role* t_nowCharacter)
{
	// 改变人物状态
	gameState = NAVIGATE;
	cancelButton->show();
	currentRole = t_nowCharacter;
	int tempx = currentRole->cellX;
	int tempy = currentRole->cellY;
	// 让Algorithm为人物寻路
	moveAl.init(currentRole->curMove, currentRole);
	moveAl.findAvailableCell(tempx, tempy, 0, rolesArray, totalRolesNum);
	// 如果四周都没有路，则给出提示
	if (moveAl.m_resultMap[tempx + 1][tempy] < 0 && moveAl.m_resultMap[tempx - 1][tempy] < 0
		&& moveAl.m_resultMap[tempx][tempy + 1] < 0 && moveAl.m_resultMap[tempx][tempy - 1] < 0)
	{
		showHintSlot("没有可移至的地块");
		emit cancelButton->clickedSignal();
	}
	repaint();
}
void GameScene::findEnemiesSlot(Role* t_nowCharacter)
{
	// 改变人物状态
	gameState = SEARCH_ENEMIES;
	cancelButton->show();
	currentRole = t_nowCharacter;
	attrackAl.init(currentRole->attackRange, currentRole);
	bool findOneOrNot = false;
	//寻找可攻击目标并标出


	if (RedBase->belong != roundBelong) {
		EnemyBase = RedBase;
	}
	else {
		EnemyBase = BlueBase;
	}

	if (ManhattanDist(EnemyBase->cellX, EnemyBase->cellY,
		currentRole->cellX, currentRole->cellY) <= currentRole->attackRange)
	{
		attrackAl.m_resultMap[EnemyBase->cellX][EnemyBase->cellY] = 1;
		attrackAl.m_availableCell.push_back(node(EnemyBase->cellX, EnemyBase->cellY));
		findOneOrNot = true;
	}

	for (int i = 0; i < totalRolesNum; i++)
	{
		if (rolesArray[i]->belong == roundBelong || rolesArray[i]->pieceState == Role::DEAD) {
			continue;//友军
		}


		if (ManhattanDist(rolesArray[i]->cellX, rolesArray[i]->cellY,
			currentRole->cellX, currentRole->cellY) <= currentRole->attackRange)
		{
			attrackAl.m_resultMap[rolesArray[i]->cellX][rolesArray[i]->cellY] = 1;
			attrackAl.m_availableCell.push_back(node(rolesArray[i]->cellX, rolesArray[i]->cellY));
			findOneOrNot = true;
		}
	}

	repaint();

	// 如果没有可攻击的对象
	if (findOneOrNot == false)
	{
		showHintSlot("没有可攻击的对象");
		QTimer::singleShot(500, this, [=]() {emit cancelButton->clickedSignal(); });
	}
}
// 跳过一个人后触发
void GameScene::roleEndSlot(Role* endedCharacter)
{
	int id = -1;
	// 找到跳过的人id
	for (int i = 0; i < totalRolesNum; i++)
	{
		if (rolesArray[i] == endedCharacter)
		{
			id = i;
			break;
		}
	}
	// 当前回合人物数改变，如果为0则下一回合
	canMoveNum[rolesArray[id]->belong]--;

	qDebug() << "endOneCharacterEvent   :::" << canMoveNum[rolesArray[id]->belong] << endl;

	cancelButton->hide();

	if (canMoveNum[rolesArray[id]->belong] == 0) {
		nextRound(rolesArray[id]->belong);
	}
}
// 死人后触发
void GameScene::roleDiesSlot(Role* deadCharacter)
{
	int id = -1;
	// 找到死人id
	for (int i = 0; i < totalRolesNum; i++)
	{
		if (rolesArray[i] == deadCharacter)
		{
			id = i;
			break;
		}
	}
	/*int alive = 0;
	for (int i = 0; i < totalRolesNum; i++) {
		if (m_character[i]->m_belong == deadCharacter->m_belong && id != i && m_character[i]->m_characterState != Character::DEAD) {
			alive++;
		}
	}

	aliveNum[m_character[id]->m_belong] = alive;*/
	aliveNum[rolesArray[id]->belong]--;

	// 如果人死完了则判定游戏结果
	if (aliveNum[rolesArray[id]->belong] == 0)
	{
		hintLabel->hide();
		gameState = END;
		if (rolesArray[id]->belong == BLUE) {
			emit& GameScene::myLossSignal;
		}
		else {
			emit& GameScene::myWinSignal;
		}
		return;
	}
	repaint();
}

void GameScene::baseDestroyedSlot(Base* deadBase) {
	gameState = END;
	if (deadBase->belong == BLUE) {
		emit &GameScene::myLossSignal;
	}
	else {
		emit &GameScene::myWinSignal;
	}
	return;
}

void GameScene::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	// 画背景图
	painter.drawPixmap(0, 0, gameMap.m_pic);
	// 如果游戏结束就不画了
	if (gameState == END) {
		return;
	}

	// 将右下角四个按钮置顶
	if (skipButton->isHidden() == false) {
		skipButton->raise();
	}
	if (cancelButton->isHidden() == false) {
		cancelButton->raise();
	}
	menuButton->raise();
	musicButton->raise();



	// 画右上角回合提示
	if (roundBelong == RED) {
		painter.setBrush(QBrush(QColor(117, 27, 19)));
	}
	else {
		painter.setBrush(QBrush(QColor(36, 169, 255)));
	}
	painter.drawRect((MAP_COL - 6) * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
	painter.setBrush(Qt::white);
	painter.drawRect((MAP_COL - 5) * CELL_SIZE, 0, CELL_SIZE * 5, CELL_SIZE);
	painter.setBrush(Qt::NoBrush);

	if (roundBelong == RED) {
		painter.setPen(QColor(117, 57, 59));
	}
	else {
		painter.setPen(QColor(36, 199, 205));
	}
	QFont font("宋体", 16, 40, false);
	font.setPixelSize(CELL_SIZE * 1);
	painter.setFont(font);
	painter.drawText((MAP_COL - 5) * CELL_SIZE + 16, CELL_SIZE - 10, QString("第%1轮%2人").arg((roundNum - 1) / 2 + 1).arg(aliveNum[roundBelong]));
	painter.setPen(Qt::NoPen);

	// 当前地块用方框标白
	painter.setPen(QPen(Qt::white, 4));
	if (gameMap.binMap[mouseGridX][mouseGridY] != 0) {
		painter.drawRect((mouseGridX - 1) * CELL_SIZE,
			(mouseGridY - 1) * CELL_SIZE,
			CELL_SIZE, CELL_SIZE);
	}
	painter.setPen(Qt::NoPen);

	// 如果游戏状态是寻路状态，则标可行域
	if (gameState == NAVIGATE)
	{
		for (int i = 1; i <= gameMap.m_maxCellx; i++)
			for (int j = 1; j <= gameMap.m_maxCelly; j++)
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
	else if (gameState == SEARCH_ENEMIES)
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
		for (int i = currentRole->cellX - currentRole->attackRange; i <= currentRole->cellX + currentRole->attackRange; i++)
			for (int j = currentRole->cellY - currentRole->attackRange; j <= currentRole->cellY + currentRole->attackRange; j++)
			{
				if (i <= 1 || i >= MAP_COL) {
					continue;
				}
				if (j <= 1 || j >= MAP_ROW) {
					continue;
				}
				if (ManhattanDist(i, j, currentRole->cellX, currentRole->cellY) > currentRole->attackRange) {
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
		if (cancelButton->isHidden() == false) {
			emit cancelButton->clickedSignal();
		}
		return;
	}
	// 更新当前鼠标位置
	updateMousePosition(event);

	// 如果是ai回合则不用等待进一步处理点击
	if (isAIOpen == true && gameState == AI) {
		return;
	}


	// 如果是选择人物阶段
	if (gameState == START)
	{
		//选择对话框
		for (int i = 0; i < totalRolesNum; i++)
		{
			// 人物并非被选择阶段则跳过
			if (rolesArray[i]->pieceState == Role::DEAD) {
				continue;
			}
			// 敌军跳过
			if (rolesArray[i]->belong != roundBelong) {
				continue;
			}
			else
			{   // 点错收回选择框
				if (rolesArray[i]->selection->isHidden() == false) {
					rolesArray[i]->selection->hide();
				}
			}
			// 点中了人物则展示操作框
			if (mouseGridX == rolesArray[i]->cellX && mouseGridY == rolesArray[i]->cellY)
			{
				// 如果跳过了或/////////////////////////////////////////////////////
				if (rolesArray[i]->pieceState == Role::FINISH)
				{
					showHintSlot("本回合该角色已结束");
					//qDebug() << "本回合已跳过已结束";
					continue;
				}
				else if (rolesArray[i]->pieceState == Role::DEAD) {
					continue;
				}

				clickSound->play();
				//显示选择框
				if (rolesArray[i]->selection->isHidden())
				{
					rolesArray[i]->selection->show();
					//m_character[i]->m_selectionDlg->updateData(mouseGridX, mouseGridY);
					rolesArray[i]->selection->updateSelectionData(rolesArray[i]->cellX, rolesArray[i]->cellY);
					rolesArray[i]->selection->raise();
				}
				break;
			}
			else
			{   //点错收回选择框
				if (rolesArray[i]->selection->isHidden() == false) {
					rolesArray[i]->selection->hide();
				}
			}
		}

	}
	// 如果是寻路阶段
	else if (gameState == NAVIGATE)
	{
		// 如果点中可行域，则执行人物移动
		if (moveAl.m_resultMap[mouseGridX][mouseGridY] >= 0)
		{
			for (int i = 0; i < totalRolesNum; i++) {
				if (rolesArray[i]->belong == currentRole->belong&& rolesArray[i] != currentRole && rolesArray[i]->pieceState != Role::DEAD) {
					if (rolesArray[i]->cellX == mouseGridX&& rolesArray[i]->cellY == mouseGridY) { //友军可以通行但不能重叠
						return;
					}
				}
			}
			clickSound->play();
			moveAl.findPath(currentRole->cellX, currentRole->cellY, mouseGridX, mouseGridY, 0, moveAl.m_resultMap[mouseGridX][mouseGridY]);
			currentRole->movePos(moveAl.m_resultMap[mouseGridX][mouseGridY], moveAl.m_path);
			cancelButton->hide();
			gameState = START;
			if (currentRole->pieceState != Role::DEAD) {
				currentRole->pieceState = Role::BEGIN;
			}

			// 等待移动完毕，发动结算机制
			if (currentRole->curMove <= 0) {
				connect(currentRole->moveAnimation, &MoveAnimation::animationFinished, this, [=]() {
					gameState = START;
					//m_nowCharacter->m_characterState = BGEIN;
					if (currentRole->curMove <= 0) {
						//m_nowCharacter->m_move = 0;

						currentRole->pieceState = Role::FINISH;
						currentRole->selection->hide();
						emit currentRole->roleSkipSignal(currentRole);
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
	else if (gameState == SEARCH_ENEMIES)
	{
		//在攻击范围内
		if (attrackAl.m_resultMap[mouseGridX][mouseGridY] != -1)
		{
			//是否还可以继续攻击判断
			if(currentRole->curMove<=3){
				currentRole->curMove = 0;
			}
			else {
				currentRole->curMove -= 3;
			}
			currentRole->updateInfoSlot();

			attackSound->play();

			//敌方基地判断
			if (RedBase->belong != roundBelong) {
				EnemyBase = RedBase;
			}
			else {
				EnemyBase = BlueBase;
			}

			//这个是判断是否是基地
			if (EnemyBase->cellX == mouseGridX && EnemyBase->cellY == mouseGridY)//点中
			{

				cancelButton->hide();
				currentRole->attackAnimation->startMove(currentRole, currentRole->cellX, currentRole->cellY,
					EnemyBase->cellX, EnemyBase->cellY);
				// 等待攻击完毕，发动结算机制
				connect(currentRole->attackAnimation, &AttrackAnimation::animationFinished, this, [=]() {
					emit EnemyBase->beAttackedSignal(currentRole->attackPoints);
					disconnect(currentRole->attackAnimation, 0, this, 0); //仅结算一次，因此要断连
					gameState = START;
					//m_nowCharacter->m_characterState = BGEIN;
					if (currentRole->curMove == 0) {
						//m_nowCharacter->m_move = 0;
						currentRole->pieceState = Role::FINISH;
						currentRole->selection->hide();
						emit currentRole->roleSkipSignal(currentRole);
					}
					});
			}


			//这个是遍历人物
			//qDebug() << "mx:" << mouseGridX << "my:" << mouseGridY << endl;
			for (int i = 0; i < totalRolesNum; i++)
			{
				//qDebug() << "x:" << m_character[i]->m_cellx << "y:" << m_character[i]->m_celly << endl;
				if (rolesArray[i]->cellX == mouseGridX && rolesArray[i]->cellY == mouseGridY&& rolesArray[i]->pieceState != Role::DEAD)//点中
				{
					//qDebug() << "m_attrack:" << m_character[i]->m_attrack << endl;
					if (rolesArray[i]->belong == roundBelong )//友军
					{
						clickSound->play();
						gameState = START;
						currentRole->pieceState = Role::BEGIN;
						break;
					}
					//qDebug() << "m_armor:" << m_character[i]->m_armor << endl;
					
					cancelButton->hide();
					currentRole->attackAnimation->startMove(currentRole, currentRole->cellX, currentRole->cellY,
						rolesArray[i]->cellX, rolesArray[i]->cellY);
					// 等待攻击完毕，发动结算机制
					connect(currentRole->attackAnimation, &AttrackAnimation::animationFinished, this, [=]() {
						emit rolesArray[i]->beAttackedSignal(currentRole->attackPoints);
						disconnect(currentRole->attackAnimation, 0, this, 0); //仅结算一次，因此要断连
						
						gameState = START;
						//m_nowCharacter->m_characterState = BGEIN;
						if (currentRole->curMove == 0) {
							//m_nowCharacter->m_move = 0;
							currentRole->pieceState = Role::FINISH;
							currentRole->selection->hide();
							emit currentRole->roleSkipSignal(currentRole);
						}
						});
					break;
				}
			}
		}
		else//偷懒了
		{
			gameState = START;
			currentRole->pieceState = Role::BEGIN;
		}
		repaint();
	}

}
// 调用则显示提示框
void GameScene::showHintSlot(const QString str, const bool next)const
{
	hintLabel->setText(str, next);
	hintLabel->show();
	hintLabel->raise();
	QTimer::singleShot(1500, this, [=]() { hintLabel->hide(); });
}

// 调用则显示提示框
void GameScene::showHintSlot(QString str)
{
	hintLabel->setText(str, 2);
	hintLabel->show();
	hintLabel->raise();
	QTimer::singleShot(1500, this, [=]() { hintLabel->hide(); });
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
	mouseX = point.x();
	mouseY = point.y();
	// 绝对格子坐标
	mouseGridX = (mouseX) / CELL_SIZE + 1;
	mouseGridY = (mouseY) / CELL_SIZE + 1;
	// 相对格子坐标

}




