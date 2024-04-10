#include <iostream>

using namespace std;

#define MAX_N 22
#define MAX_M 5

struct Line {
    int startX;
    int startY;
    int endX;
    int endY;
} line[MAX_M];

int N, M, K;
int map[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];



int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

int arrowX = 1;
int arrowY = 1;
int arrowD = 0;
int arrowFlag = 0;
int ax[4] = {1, 0, -1, 0};
int ay[4] = {0, 1, 0, -1};

int result = 0;

void print_map() {
    cout << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}


void get_input() {
    cin >> N >> M >> K;
    int flag = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) {
                line[flag].startX = i;
                line[flag].startY = j;
                flag++;
            }
        }
    }
}

void move() {
    for (int i = 0; i < M; i++) {
        int fromX = line[i].startX;
        int fromY = line[i].startY;
        int toX, toY;
        bool ifStartWithEnd = false;
        for (int d = 0; d < 4; d++) {
            int nx = fromX + dx[d];
            int ny = fromY + dy[d];
            if (map[nx][ny] == 4) {
                toX = nx;
                toY = ny;
                break;
            }
            if (map[nx][ny] == 3) {
                for (int dd = 0; dd < 4; dd++) {
                    int nnx = nx + dx[dd];
                    int nny = ny + dy[dd];
                    if (map[nnx][nny] == 2) {
                        map[fromX][fromY] = 2;
                        map[nx][ny] = 1;
                        map[nnx][nny] = 3;
                        line[i].startX = nx;
                        line[i].startY = ny;
                        line[i].endX = nnx;
                        line[i].endY = nny;
                        ifStartWithEnd = true;
                        break;
                    }
                }
                break;
            }
        }
        if (ifStartWithEnd)
            continue;
        line[i].startX = toX;
        line[i].startY = toY;
        while(map[fromX][fromY] != 4) {
            map[toX][toY] = map[fromX][fromY];
            for (int d = 0; d < 4; d++) {
                int nx = fromX + dx[d];
                int ny = fromY + dy[d];
                if (nx == toX && ny == toY)
                    continue;
                if (map[nx][ny] > 0) {
                    toX = fromX;
                    toY = fromY;
                    fromX = nx;
                    fromY = ny;
                    break;
                }
            }
        }
        line[i].endX = fromX;
        line[i].endY = fromY;
        map[toX][toY] = 4;
    }
}

int get_point(int x, int y) {
    int score = 1;
    if (map[x][y] == 1)
        return 1;
    for (int i = 0; i < M; i++) {
        int fromX = line[i].startX;
        int fromY = line[i].startY;
        while(1) {
            score++;
            bool ifIsTail = false;
            visited[fromX][fromY] = 1;
            for (int d = 0; d < 4; d++) {
                int nx = fromX + dx[d];
                int ny = fromY + dy[d];
                if (visited[nx][ny])
                    continue;
                if (nx == x && ny == y)
                    return score;
                if (map[nx][ny] == 3) {
                    ifIsTail = true;
                    break;
                }
                if (map[nx][ny] == 2) {
                    fromX = nx;
                    fromY = ny;
                    break;
                }
            }
            if (ifIsTail)
                break;
        }
    }
}

void shoot() {
    int nowArrowX = arrowX;
    int nowArrowY = arrowY;
    int personX, personY;
    int ifHasPerson = false;
    for (int step = 0; step < N; step++) {
        nowArrowX = arrowX + dx[arrowD] * step;
        nowArrowY = arrowY + dy[arrowD] * step;
        if (map[nowArrowX][nowArrowY] > 0 && map[nowArrowX][nowArrowY] < 4) {
            ifHasPerson = true;
            personX = nowArrowX;
            personY = nowArrowY;
            break;
        }
    }
    if (!ifHasPerson)
        return;
    for (int i = 0; i <= N + 1; i++) {
        for (int j = 0; j <= N + 1; j++) {
            visited[i][j] = 0;
        }
    }
    int tmp = get_point(personX, personY);
    result += tmp * tmp;
    //change
    int nx = arrowX + ax[arrowD];
    int ny = arrowY + ay[arrowD];
    if (nx == 0 || ny == 0 || nx == N+1 || ny == N+1) {
        arrowD++;
        if (arrowD == 4)
            arrowD = 0;
        return;
    }
    arrowX = nx;
    arrowY = ny;
}
int main() {
    // 여기에 코드를 작성해주세요.
    get_input();
    while(K--) {
        move();
        shoot();
    }
    cout << result;
    return 0;
}