#include <iostream>
#include <deque>
using namespace std;

int map[80][80];

int R, C, K;

int nodeC[1050];
int nodeD[1010];
int nodeX[1010];
int nodeY[1010];
int visited[1010];

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int result = 0;

void clearMap() {
	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			map[i][j] = 0;
		}
	}
}
void printMap() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void getInput() {
	cin >> R >> C >> K;
	for (int i = 1; i <= K; i++) {
		cin >> nodeC[i] >> nodeD[i];
	}
}

bool checkValid(int x, int y) {
	if (x == R)
		return false;
	if (y == 1 || y == C)
		return false;
	//left, right, down
	if (map[x][y - 1] > 0 || map[x][y + 1] > 0 || map[x + 1][y] > 0)
		return false;
	return true;
}

int main() {
	getInput();
	for (int i = 1; i <= K; i++) {
		int nowY = nodeC[i];
		int nowX = -1;

		while (1) {
			// checkDown
			int tmpNodeX = nowX + 1;
			int tmpNodeY = nowY;
			if (checkValid(tmpNodeX, tmpNodeY)) {
				nowX = tmpNodeX;
				nowY = tmpNodeY;
				continue;
			}
			// checkLeft
			tmpNodeX = nowX;
			tmpNodeY = nowY - 1;
			if (checkValid(tmpNodeX, tmpNodeY) && checkValid(tmpNodeX+1, tmpNodeY)) {
				nowX = tmpNodeX;
				nowY = tmpNodeY;
				//출구
				nodeD[i] -= 1;
				if (nodeD[i] == -1)
					nodeD[i] = 3;
				continue;
			}
			// check right
			tmpNodeX = nowX;
			tmpNodeY = nowY + 1;
			if (checkValid(tmpNodeX, tmpNodeY) && checkValid(tmpNodeX+1, tmpNodeY)) {
				nowX = tmpNodeX;
				nowY = tmpNodeY;
				//출구
				nodeD[i] += 1;
				if (nodeD[i] == 4)
					nodeD[i] = 0;
				continue;
			}
			break;
		}
		// reset
		if (nowX <= 1) {
			clearMap();
			continue;
		}
		//write
		nodeX[i] = nowX;
		nodeY[i] = nowY;
		map[nowX][nowY] = i;
		for (int d = 0; d < 4; d++) {
			map[nowX + dx[d]][nowY + dy[d]] = i;
		}
	
		//printMap();
		// 정령 이동
		int maxX = nowX + 1;
		for (int vi = 0; vi < K; vi++)
			visited[vi] = 0;
		deque<int> q;
		int nowNode = i;
		visited[nowNode] = 1;
		q.push_back(i);
		while (!q.empty()) {
			nowNode = q.front();
			q.pop_front();
			nowX = nodeX[nowNode];
			nowY = nodeY[nowNode];
			
			if (nowX + 1 > maxX)
				maxX = nowX + 1;

			int exitX = nodeX[nowNode] + dx[nodeD[nowNode]];
			int exitY = nodeY[nowNode] + dy[nodeD[nowNode]];
			for (int d = 0; d < 4; d++) {
				int tmpX = exitX + dx[d];
				int tmpY = exitY + dy[d];
				if (tmpX == 0 || tmpY == 0 || tmpX == R + 1 || tmpY == C + 1)
					continue;

				int tmpNode = map[tmpX][tmpY];
				if (tmpNode != nowNode && !visited[tmpNode]) {
					visited[tmpNode] = 1;
					q.push_back(tmpNode);
				}
			}
		}
		//cout << maxX << endl;
		result += maxX;
	}
	cout << result;


	return 0;
}