#include "algorithm.h"
#include "config.h"
#include "gamemap.h"


/*  此文件包含为人物寻路和寻找攻击范围的内容
 *  采用的寻路算法为dfs搜索
 */

FindPathAlgorithm::FindPathAlgorithm()
{
	init();
}
// 数据初始化
void FindPathAlgorithm::init()
{
	memset(m_resultMap, -1, sizeof m_resultMap);
	m_availableCell.clear();
	m_foundPathOrNot = false;
	m_path.clear();
}
void FindPathAlgorithm::init(int t_move, Role* t_nowCharacter)
{
	init();
	m_totalMove = t_move;
	m_nowCharacter = t_nowCharacter;
	m_foundPathOrNot = false;
}
// bfs寻找可行域
void FindPathAlgorithm::findAvailableCell(const int x, const  int y, const int depth, Role* character[], const  int characterNum)
{
	for (int i = 0; i < characterNum; i++) {
		if (character[i] != m_nowCharacter && character[i]->pieceState != Role::DEAD) {
			if (character[i]->pieceState != m_nowCharacter->belong) { //遇见有人挡路绕不过去
				m_resultMap[character[i]->cellX][character[i]->cellY] = -9;
			}
		}
	}
	
	QQueue<node> qNode;

	qNode.enqueue(node(x, y));
	m_resultMap[x][y] = 0;
	m_availableCell.push_back(std::make_pair(x, y));
	while (!qNode.empty()) {
		node tempN = qNode.dequeue();
		int tempx = tempN.first;
		int tempy = tempN.second;
		int tmoved = m_resultMap[tempx][tempy];
		findNextCell(qNode, tempx - 1, tempy, tmoved);
		findNextCell(qNode, tempx + 1, tempy, tmoved);
		findNextCell(qNode, tempx, tempy - 1, tmoved);
		findNextCell(qNode, tempx, tempy + 1, tmoved);
	}
}
void FindPathAlgorithm::findNextCell(QQueue<node>& que, int tx, int ty, int tmd)
{
	if (GameMap::binMap[tx][ty] != 0 && m_resultMap[tx][ty] != -9) {
		int moved;
		if (GameMap::binMap[tx][ty] == 2 || GameMap::binMap[tx][ty] == 3) { // 如果是水或者火，则行动力减少得更多
			moved = tmd + 2;
		}
		else {
			moved = tmd + 1;
		}

		if (moved<=m_totalMove) {
			if (m_resultMap[tx][ty] < 0) // 如果此点还没确定可行，则更新为可行
			{
				m_resultMap[tx][ty] = moved;
				m_availableCell.push_back(std::make_pair(tx, ty));
				que.enqueue(node(tx, ty));
			}
			else if (moved < m_resultMap[tx][ty]) {//如果此点已经可行，则比较已知最短路和当前路哪个更短
				m_resultMap[tx][ty] = moved;
				que.enqueue(node(tx, ty));
			}

		}
	}
}
// 找当前点到达可行域点的路径，以DIRECTION的enum值存入vector
void FindPathAlgorithm::findPath(int x, int y, int endx, int endy, int tempsteps, int totalsteps)
{
	if (m_foundPathOrNot) {
		return; // 找到路了，剪枝
	}
	if (tempsteps > m_resultMap[x][y] ) {
		return; // 如果当前路径消耗的行动点数大于已知最少行动点数，则当前路径不为所求
	}
	if (x == endx && y == endy)
	{
		// 走到终点，且消耗的行动点数最少，则当前路就是要寻找的路
		m_foundPathOrNot = true;
		return;
	}

	if (x - 1 >= 1 && GameMap::binMap[x - 1][y] != 0) //向左走
	{
		m_path.push_back(LEFT); // 标记当前路径
		if (GameMap::binMap[x - 1][y] == 1) {
			findPath(x - 1, y, endx, endy, tempsteps + 1, totalsteps);
		}
		else { // 如果是水或者火，则行动力减少得更多
			findPath(x - 1, y, endx, endy, tempsteps + 2, totalsteps);
		}
		if (m_foundPathOrNot) {
			return;
		}
		m_path.pop_back(); // 解除标记
	}
	if (x + 1 <= MAP_COL && GameMap::binMap[x + 1][y] != 0) // 向右走
	{
		m_path.push_back(RIGHT); // 标记当前路径
		if (GameMap::binMap[x + 1][y] == 1) {
			findPath(x + 1, y, endx, endy, tempsteps + 1, totalsteps);
		}
		else { // 如果是水或者火，则行动力减少得更多
			findPath(x + 1, y, endx, endy, tempsteps + 2, totalsteps);
		}
		if (m_foundPathOrNot) {
			return;
		}
		m_path.pop_back(); // 解除标记
	}
	if (y + 1 <= MAP_ROW && GameMap::binMap[x][y + 1] != 0) // 向下走
	{
		m_path.push_back(DOWN); // 标记当前路径
		if (GameMap::binMap[x][y + 1] == 1) {
			findPath(x, y + 1, endx, endy, tempsteps + 1, totalsteps);
		}
		else {// 如果是水或者火，则行动力减少得更多
			findPath(x, y + 1, endx, endy, tempsteps + 2, totalsteps);
		}
		if (m_foundPathOrNot) {
			return;
		}
		m_path.pop_back(); // 解除标记
	}
	if (y - 1 >= 1 && GameMap::binMap[x][y - 1] != 0) // 向上走
	{
		m_path.push_back(UP); // 标记当前路径
		if (GameMap::binMap[x][y - 1] == 1) {
			findPath(x, y - 1, endx, endy, tempsteps + 1, totalsteps);
		}
		else { // 如果是水或者火，则行动力减少得更多
			findPath(x, y - 1, endx, endy, tempsteps + 2, totalsteps);
		}
		if (m_foundPathOrNot) {
			return;
		}
		m_path.pop_back(); // 解除标记
	}
}
