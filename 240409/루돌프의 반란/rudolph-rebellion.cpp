#include <iostream>

using namespace std;

#define MAX_P 31

int N, M, P, C, D;

int sanX[MAX_P];
int sanY[MAX_P];
int status[MAX_P];
int luX, luY;
// 상, 우, 하, 좌, 상우, 하우, 하좌, 상우
int dx[8] = {-1, 0, 1, 0, -1, 1, 1, -1};
int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

int result = 0;


void print_lu() {
    cout << endl;
    cout << "lu : " << luX << luY;
}
void print_san() {
    cout << endl;
    for (int i = 1; i < P; i++) {
        cout << " san" << i << ": " << sanX[i] << " " << sanY[i];
    }
}

int check_dist(int x1, int y1, int x2, int y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}
bool check_valueble(int x, int y) {
    if (x <= 0 || y <= 0 || x >= N+1 || y >= N+1)
        return false;
    return true;
}

void move_lu() {
    int min_dist = 123456789;
    int maxX ,maxY;
    for (int i = 1; i <= P; i++) {
        int tmp_dist = check_dist(luX, luY, sanX[i], sanY[i]);
        if (tmp_dist < min_dist) {
            min_dist = tmp_dist;
            maxX = sanX[i];
            maxY = sanY[i];
        }
        if (tmp_dist == min_dist) {
            if (sanX[i] < maxX)
                continue;
            if (sanX[i] == maxX && sanY[i] < maxY)
                continue;
            maxX = sanX[i];
            maxY = sanY[i];
        }
    }
    int minX, minY;
    min_dist = 123456789;
    for (int d = 0; d < 8; d++) {
        int tmpX = luX + dx[d];
        int tmpY = luY + dy[d];
        int tmpDist = check_dist(tmpX, tmpY, maxX, maxY);
        if (!check_valueble(tmpX, tmpY))
            continue;
        if (tmpDist < min_dist) {
            min_dist = tmpDist;
            minX = tmpX;
            minY = tmpY;
        }
    }
    luX = minX;
    luY = minY;
}
void move_san() {
    for (int i = 1; i <= P; i++) {
        if (status[i] == -1)
            continue;
        if (status[i] == 1) {
            status[i] = 0;
            continue;
        }
        int dist = check_dist(luX, luY, sanX[i], sanY[i]);
        for (int d = 0; d < 4; d++) {
            int tmpX = sanX[i] + dx[d];
            int tmpY = sanY[i] + dy[d];
            if (!check_valueble(tmpX, tmpY))
                continue;
            bool ifHasSan = false;
            for (int j = 1; j <= P; j++) {
                if (sanX[j] == tmpX && sanY[j] == tmpY) {
                    ifHasSan = true;
                    break;
                }
            }
            if (ifHasSan)
                continue;
            int tmp_dist = check_dist(luX, luY, tmpX, tmpY);
            if (tmp_dist < dist) {
                sanX[i] = tmpX;
                sanY[i] = tmpY;
                break;
            }
        }
    }
}

void getInput() {
    cin >> N >> M >> P >> C >> D;
    cin >> luX >> luY;

    for (int i = 1; i <= P; i++) {
        int tmp;
        cin >> tmp;
        cin >> sanX[tmp] >> sanY[tmp];
    }
}

int main() {
    // 여기에 코드를 작성해주세요.
    getInput();
    //while (M--) {
        move_lu();
        print_san();
        move_san();
        print_san();
    //}

    return 0;
}