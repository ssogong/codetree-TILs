#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int map[20][20];
int timeMap[20][20];
int fromMapX[20][20];
int fromMapY[20][20];
int relatedMap[20][20];
int TIME = 1;
int N, M, K;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int dx2[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };
int dy2[8] = { 1, 0, -1, 0, -1, 1, -1, 1 };

int minNodeX, minNodeY;
int maxNodeX, maxNodeY;



void priintMap() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void getInput() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> map[i][j];
        }
    }
}

void findMinMax() {
    minNodeX = 0, minNodeY = 0;
    maxNodeX = 0, maxNodeY = 0;
    int minVal = 5500;
    int maxVal = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == 0)
                continue;
            if (map[i][j] > maxVal)
                maxVal = map[i][j];
            if (map[i][j] < minVal)
                minVal = map[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == 0)
                continue;
            if (map[i][j] == minVal) {
                if (minNodeX != 0 &&
                    (timeMap[i][j] < timeMap[minNodeX][minNodeY] ||
                        i + j < minNodeX + minNodeY ||
                        j < minNodeY))
                    continue;
                minNodeX = i;
                minNodeY = j;
            }
            if (map[i][j] == maxVal) {
                if (maxNodeX != 0 &&
                    (timeMap[i][j] < timeMap[maxNodeX][maxNodeY] ||
                        i + j < maxNodeX + maxNodeY ||
                        j < maxNodeY))
                    continue;
                maxNodeX = i;
                maxNodeY = j;
            }
        }
    }
}

void getNextPos(int& nextX, int& nextY) {
    if (nextX == 0) nextX = N;
    if (nextX == N + 1) nextX = 1;
    if (nextY == 0) nextY = M;
    if (nextY == M + 1) nextY = 1;
}

bool tryRazer() {
    bool reachedFlag = false;
    int nowX = minNodeX;
    int nowY = minNodeY;
    fromMapX[nowX][nowY] = -1;
    fromMapY[nowX][nowY] = -1;
    deque<pair<int, int>> q;
    q.push_back(make_pair(nowX, nowY));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            fromMapX[i][j] = 0;
            fromMapY[i][j] = 0;
        }
    }
    while (!q.empty()) {
        nowX = q.front().first;
        nowY = q.front().second;
        q.pop_front();
        if (nowX == maxNodeX && nowY == maxNodeY) {
            reachedFlag = true;
            break;
        }
        for (int d = 0; d < 4; d++) {
            int nextX = nowX + dx[d];
            int nextY = nowY + dy[d];
            getNextPos(nextX, nextY);
            if (map[nextX][nextY] == 0 || fromMapX[nextX][nextY] != 0)
                continue;
            fromMapX[nextX][nextY] = nowX;
            fromMapY[nextX][nextY] = nowY;
            q.push_back(make_pair(nextX, nextY));
        }
    }
    if (reachedFlag == false)
        return false;
    int power = map[minNodeX][minNodeY];
    map[maxNodeX][maxNodeY] -= power;
    if (map[maxNodeX][maxNodeY] < 0) map[maxNodeX][maxNodeY] = 0;
    power = power / 2;
    nowX = fromMapX[maxNodeX][maxNodeY];
    nowY = fromMapY[maxNodeX][maxNodeY];
    while (!(nowX == minNodeX && nowY == minNodeY)) {
        map[nowX][nowY] -= power;
        if (map[nowX][nowY] < 0) map[nowX][nowY] = 0;
        relatedMap[nowX][nowY] = 1;

        int tmpX = nowX, tmpY = nowY;
        nowX = fromMapX[tmpX][tmpY];
        nowY = fromMapY[tmpX][tmpY];
    }

    return true;
}

void cannonAttack() {
    int power = map[minNodeX][minNodeY];
    map[maxNodeX][maxNodeY] -= power;
    if (map[maxNodeX][maxNodeY] < 0) map[maxNodeX][maxNodeY] = 0;
    power = power / 2;
    for (int d = 0; d < 8; d++) {
        int nextX = maxNodeX + dx2[d];
        int nextY = maxNodeY + dy2[d];
        getNextPos(nextX, nextY);
        if (nextX == minNodeX && nextY == minNodeY)
            continue;
        if (map[nextX][nextY] == 0)
            continue;
        map[nextX][nextY] -= power;
        if (map[nextX][nextY] < 0) map[nextX][nextY] = 0;
        relatedMap[nextX][nextY] = 1;
    }
}

void retire() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] > 0 && relatedMap[i][j] == 0)
                map[i][j]++;
        }
    }
}

void printResult() {
    int maxVal = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] > maxVal)
                maxVal = map[i][j];
        }
    }
    cout << maxVal << endl;
}

int main() {
    // 여기에 코드를 작성해주세요.
    getInput();
    //priintMap();
    for (; TIME <= K + 1; TIME++) {
        //priintMap();
        findMinMax();
        //cout << "min : " << minNodeX << " " << minNodeY << endl;
        //cout << "max : " << maxNodeX << " " << maxNodeY << endl;
        timeMap[minNodeX][minNodeY] = TIME;
        if (minNodeX == maxNodeX && minNodeY == maxNodeY)
            break;
        map[minNodeX][minNodeY] += N + M;

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                relatedMap[i][j] = 0;
            }
        }
        relatedMap[minNodeX][minNodeY] = 1;
        relatedMap[maxNodeX][maxNodeY] = 1;

        bool successFlag = tryRazer();
        if (successFlag == true) {
            //priintMap();
            retire();
            //priintMap();
            //cout << "-------------" << endl;
            continue;
        }
        cannonAttack();
        //priintMap();
        retire();
        //priintMap();
        //cout << "-------------" << endl;
    }
    printResult();

    return 0;
}