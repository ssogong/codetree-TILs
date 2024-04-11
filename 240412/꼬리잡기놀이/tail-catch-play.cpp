// 꼬리잡기놀이.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 22
#define MAX_M 6

int N, M, K;
int map[MAX_N][MAX_N];
int map_idx[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

vector<pair<int, int>> line[MAX_M];
int tail_idx[MAX_M];

int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };

int arrowX = 1;
int arrowY = 1;
int arrowD = 0;
int ax[4] = { 1, 0, -1, 0 };
int ay[4] = { 0, 1, 0, -1 };

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

void DFS(int x, int y, int idx) {

    map_idx[x][y] = idx;
    if (map[x][y] == 3) {
        tail_idx[idx] = line[idx].size() - 1;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (visited[nx][ny])
            continue;
        if (map[nx][ny] == 0)
            continue;
        if (line[idx].size() == 1 && map[nx][ny] != 2)
            continue;
        visited[nx][ny] = 1;
        line[idx].push_back({ nx, ny });
        DFS(nx, ny, idx);
    }
}

void get_input() {
    cin >> N >> M >> K;
    int flag = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1)
                line[flag++].push_back({ i, j });
        }
    }
    for (int i = 1; i <= M; i++) {
        int startX = line[i].front().first;
        int startY = line[i].front().second;
        visited[startX][startY] = 1;
        DFS(startX, startY, i);
    }
}

void move() {
    for (int i = 1; i <= M; i++) {
        int len = line[i].size();
        pair<int, int> tmp = line[i][len - 1];
        for (int j = len - 1; j > 0; j--) {
            line[i][j] = line[i][j - 1];
        }
        line[i][0] = tmp;
    }
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < line[i].size(); j++) {
            int x = line[i][j].first;
            int y = line[i][j].second;
            if (j == 0) map[x][y] = 1;
            else if (j < tail_idx[i]) map[x][y] = 2;
            else if (j == tail_idx[i]) map[x][y] = 3;
            else map[x][y] = 4;
        }
    }
}

int get_point(int x, int y) {
    int idx = map_idx[x][y];
    int i;
    for (i = 0; i < line[idx].size(); i++) {
        if (line[idx][i].first == x && line[idx][i].second == y)
            return i + 1;
    }
}
void reserve(int idx) {
    vector<pair<int, int>> tmp_line;
    int tail = tail_idx[idx];
    for (int i = tail; i >= 0; i--) {
        tmp_line.push_back(line[idx][i]);
    }
    for (int i = line[idx].size() - 1; i > tail; i--) {
        tmp_line.push_back(line[idx][i]);
    }
    for (int i = 0; i < tmp_line.size(); i++) {
        line[idx][i] = tmp_line[i];
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

    int tmp = get_point(personX, personY);
    result += tmp * tmp;

    // reserve
    int idx = map_idx[personX][personY];
    reserve(idx);
}


int main()
{
    get_input();
    while (K--) {
        move();
        shoot();
        int nx = arrowX + ax[arrowD];
        int ny = arrowY + ay[arrowD];
        if (nx == 0 || ny == 0 || nx == N + 1 || ny == N + 1) {
            arrowD++;
            if (arrowD == 4)
                arrowD = 0;
            continue;
        }
        arrowX = nx;
        arrowY = ny;
    }
    cout << result;
    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.