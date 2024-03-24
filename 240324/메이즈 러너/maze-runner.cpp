#include <iostream>

#define MAX_N 10
#define MAX_M 10

using namespace std;

typedef struct {
    int x;
    int y;
}Node;

int N, M, K;
int result = 0;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int sx, sy, sd;

int map[MAX_N + 1][MAX_N + 1];
int tmp_map[MAX_N + 1][MAX_N + 1];
Node person[MAX_M + 1];
Node e;

void print() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void getInput() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        cin >> person[i].x >> person[i].y;
    }
    cin >> e.x >> e.y;
}

void movePerson() {
    for (int i = 0; i < M; i++) {
        if (person[i].x == e.x && person[i].y == e.y)
            continue;
        int distance = abs(e.x - person[i].x) + abs(e.y - person[i].y);
        for (int j = 0; j < 4; j++) {
            int nx = person[i].x + dx[j];
            int ny = person[i].y + dy[j];
            if (nx < 1 || ny < 1 || nx > N || ny > N)
                continue;
            if (map[nx][ny] >= 1)
                continue;
            int nd = abs(e.x - nx) + abs(e.y - ny);
            if (distance <= nd)
                continue;
            person[i].x = nx;
            person[i].y = ny;
            result++;
            break;
        }
    }
}

void findSquare() {
    for (sd = 2; sd <= N; sd++) {
        for (sx = 1; sx <= N - sd + 1; sx++) {
            for (sy = 1; sy <= N - sd + 1; sy++) {
                if (e.x < sx || e.x > sx + sd - 1 || e.y < sy || e.y > sy + sd - 1)
                    continue;
                for (int i = 0; i < M; i++) {
                    if (person[i].x >= sx && person[i].x <= sx + sd - 1
                        && person[i].y >= sy && person[i].y <= sy + sd - 1) {
                        if (person[i].x != e.x || person[i].y != e.y) {
                            return;
                        }
                    }
                }

            }
        }
    }
}

void rotation() {
    for (int i = sx; i <= sx + sd - 1; i++) {
        for (int j = sy; j <= sy + sd - 1; j++) {
            int ox = i - sx;
            int oy = j - sy;
            int rx = oy;
            int ry = sd - ox - 1;
            tmp_map[sx + rx][sy + ry] = map[i][j];
        }
    }
    for (int i = sx; i <= sx + sd - 1; i++) {
        for (int j = sy; j <= sy + sd - 1; j++) {
            map[i][j] = tmp_map[i][j];
            if (map[i][j] > 0)
                map[i][j]--;
        }
    }

    // rotation person
    for (int i = 0; i < M; i++) {
        if (person[i].x >= sx && person[i].x <= sx + sd - 1
            && person[i].y >= sy && person[i].y <= sy + sd - 1) {
            int ox = person[i].x - sx;
            int oy = person[i].y - sy;
            int rx = oy;
            int ry = sd - ox - 1;
            person[i].x = rx + sx;
            person[i].y = ry + sy;
        }
    }

    // rotation exit
    int ox = e.x - sx;
    int oy = e.y - sy;
    int rx = oy;
    int ry = sd - ox - 1;
    e.x = rx + sx;
    e.y = ry + sy;
}

bool ifAllExit() {
    for (int i = 0; i <= M; i++) {
        if (person[i].x != e.x || person[i].y != e.y)
            return false;
    }
    return true;
}

void printResult() {
    cout << result << endl;
    cout << e.x << " " << e.y;
}

int main() {
    // 여기에 코드를 작성해주세요.
    getInput();
    while (K--) {
        movePerson();
        if (ifAllExit())
            break;
        findSquare();
        rotation();
    }

    printResult();
    return 0;
}