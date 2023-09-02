#include "GameAI.h"

/* GameAI是模拟AI运行的类，通过调用Algorithm寻路，并调用Animation绘制动画 */

GameAI::GameAI()
{
}
// 移动某角色，传入所有角色和行动的角色
void GameAI::moveCharacter(const int id, Role* t_character[], const int characterNum)
{
	// 初始化
	m_character = t_character;
	this->id = id;
	this->characterNum = characterNum;
	m_nowCharacter = m_character[id];
	m_Al.init(m_nowCharacter->curMove, m_nowCharacter);

	int tempx = m_nowCharacter->cellX;
	int tempy = m_nowCharacter->cellY;

	// 算法寻找移动可行域
	m_Al.findAvailableCell(tempx, tempy, 0, m_character, characterNum);

	// 寻找距离其他角色的最近距离的初始化
	m_minDist = 0x3f3f3f3f;
	// m_minDist = 0;
	node minNode{ -1,-1 };
	m_attrackid = -1;
	//int attrack_score = -1;

	// 寻找距离对手的最近距离
	for (ull i = 0; i < m_Al.m_availableCell.size(); i++)
	{
		bool over = false;
		for (int k = 0; k < characterNum; k++) {
			if (k != id && m_character[k]->pieceState != Role::DEAD) {
				if (m_character[k]->cellX == m_Al.m_availableCell[i].first && m_character[k]->cellY == m_Al.m_availableCell[i].second) { //友军可以通行但不能重叠
					over = true;
					break;
				}
			}
		}
		if (over == true) {
			continue;
		}

		for (int j = 0; j < characterNum; j++)
			if (m_character[j]->belong == BLUE && m_character[j]->pieceState != Role::DEAD)
			{
				//if(character[1]->characterState==Character::DEAD)qDebug()<<"DEAD";else qDebug()<<"EXISTING";
				int tempDist = ManhattanDist(m_Al.m_availableCell[i], std::make_pair(m_character[j]->cellX, m_character[j]->cellY));
				//int tempScore = 0;

				if (m_minDist > tempDist)
				{

					minNode = m_Al.m_availableCell[i];
					m_minDist = tempDist;
					m_attrackid = j;
				}



			}
	}
	// 寻找如何到达上述最近距离
	m_Al.findPath(m_nowCharacter->cellX, m_nowCharacter->cellY, minNode.first, minNode.second, 0, m_Al.m_resultMap[minNode.first][minNode.second]);

	connect(m_nowCharacter->moveAnimation, &MoveAnimation::animationFinished, this, &GameAI::attrackCharacter, Qt::UniqueConnection);//
	//qDebug() << "x" << minNode.first << "y" << minNode.second << endl;
	m_nowCharacter->movePos(m_Al.m_resultMap[minNode.first][minNode.second], m_Al.m_path);
}
// 进行攻击操作
void GameAI::attrackCharacter()const
{
	//qDebug() << " GameAI::attrackCharacter()" << m_minDist << endl;
	// 如果在最近距离可攻击到敌人，则攻击
	connect(m_nowCharacter->attackAnimation, &AttrackAnimation::nonFinalAnimationEnd, this, [=]() {
		qDebug() << "AA nonFinalAnimationEnd" << endl;

		emit m_character[m_attrackid]->beAttackedSignal(m_nowCharacter->attackPoints);
		}, Qt::UniqueConnection);
	connect(m_nowCharacter->attackAnimation, &AttrackAnimation::attackAnimationFinished, this, [=]() {
		qDebug() << "AA animationFinished" << endl;
		emit m_character[m_attrackid]->beAttackedSignal(m_nowCharacter->attackPoints);
		waitFunc();
		disconnect(m_nowCharacter->attackAnimation, 0, this, 0);
		}, Qt::UniqueConnection);
	connect(m_nowCharacter->attackAnimation, &AttrackAnimation::nonFinalAnimationEnd, this, &GameAI::oneAttackOverSignal, Qt::UniqueConnection);
	qDebug() << "现在行动力>>" << m_nowCharacter->curMove << endl;
	if (m_minDist <= m_nowCharacter->attackRange && m_nowCharacter->curMove >= 0)
	{

		
		if (m_nowCharacter->curMove > 3) {
			m_nowCharacter->curMove -= 3;
			m_nowCharacter->attackAnimation->startMove(m_nowCharacter, m_nowCharacter->cellX, m_nowCharacter->cellY,
				m_character[m_attrackid]->cellX, m_character[m_attrackid]->cellY, false);
		}
		else {
			m_nowCharacter->curMove = 0;
			m_nowCharacter->attackAnimation->startMove(m_nowCharacter, m_nowCharacter->cellX, m_nowCharacter->cellY,
				m_character[m_attrackid]->cellX, m_character[m_attrackid]->cellY, true);
		}
	}
	// 否则结束
	else
	{
		qDebug() << "否则结束thisCharacterFinished" << endl;
		emit thisCharacterFinished();
	}
}
// 等待攻击结束后发送ai执行完毕指令
void GameAI::waitFunc()const
{
	qDebug() << "执行完毕指令thisCharacterFinished" << endl;

	//emit m_character[m_attrackid]->beAttackedSignal(m_nowCharacter->attackPoints);
	QTimer::singleShot(10, [=]() {emit thisCharacterFinished(); });
}
