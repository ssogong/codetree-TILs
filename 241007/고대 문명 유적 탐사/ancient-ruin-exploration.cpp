#include <iostream>
#include <deque>
using namespace std;

int K, M;
int map[6][6];
int numList[330];
int idx = 0;

int result = 0;

int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };

void print_map() {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void get_input() {
    cin >> K >> M;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        cin >> numList[i];
    }
}

int check_value() {
    int value = 0;
    int visited[6][6] = { 0 };
    deque<pair<int, int>> q;

    //print_map();

    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (visited[i][j])
                continue;
            visited[i][j] = 1;
            int nowNum = map[i][j];
            int cnt = 1;
            
            q.push_back(make_pair(i, j));
            while (!q.empty()) {
                int nowX = q.front().first;
                int nowY = q.front().second;
                q.pop_front();
                for (int d = 0; d < 4; d++) {
                    int nextX = nowX + dx[d];
                    int nextY = nowY + dy[d];
                    if (nextX == 6 || nextY == 6 || visited[nextX][nextY] || map[nextX][nextY] != nowNum)
                        continue;
                    visited[nextX][nextY] = 1;
                    cnt++;
                    q.push_back(make_pair(nextX, nextY));
                }
            }
            if (cnt >= 3) {
                value += cnt;
            }
        }
    }

    return value;
}

void rotate_90(int centerX, int centerY) {
    int startX = centerX - 1;
    int startY = centerY - 1;
    int tmp_map[3][3];
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            tmp_map[j][2-i] = map[startX + i][startY + j];
        }
    }
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            map[startX + i][startY + j] = tmp_map[i][j];
        }
    }
}


void break_and_fill() {
    int visited[6][6] = { 0 };
    deque<pair<int, int>> q;
    deque<pair<int, int>> node_q;

    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (visited[i][j])
                continue;
            visited[i][j] = 1;
            int nowNum = map[i][j];
            int cnt = 1;

            q.push_back(make_pair(i, j));
            while (!q.empty()) {
                int nowX = q.front().first;
                int nowY = q.front().second;
                q.pop_front();
                for (int d = 0; d < 4; d++) {
                    int nextX = nowX + dx[d];
                    int nextY = nowY + dy[d];
                    if (nextX == 6 || nextY == 6 || visited[nextX][nextY] || map[nextX][nextY] != nowNum)
                        continue;
                    visited[nextX][nextY] = 1;
                    cnt++;
                    q.push_back(make_pair(nextX, nextY));
                }
            }
            if (cnt >= 3) {
                node_q.push_back(make_pair(i, j));
            }
        }
    }

    while (!node_q.empty()) {
        deque<pair<int, int>> que;
        int nowX = node_q.front().first;
        int nowY = node_q.front().second;
        int start_num = map[nowX][nowY];
        map[nowX][nowY] = 10;
        node_q.pop_front();
        que.push_back(make_pair(nowX, nowY));
        while (!que.empty()) {
            nowX = que.front().first;
            nowY = que.front().second;
            que.pop_front();
            for (int d = 0; d < 4; d++) {
                int nextX = nowX + dx[d];
                int nextY = nowY + dy[d];
                if (nextX == 6 || nextY == 6 || map[nextX][nextY] != start_num)
                    continue;
                map[nextX][nextY] = 10;
                que.push_back(make_pair(nextX, nextY));
            }
        }
    }

    for (int j = 1; j <= 5; j++) {
        for (int i = 5; i >= 1; i--) {
            if (map[i][j] == 10) {
                map[i][j] = numList[idx++];
            }
        }
    }
}

bool try_find() {
    int maxResult = 0;
    int maxX, maxY, maxR = 3;
    for (int j = 2; j <= 4; j++) {
        for (int i = 2; i <= 4; i++) {
            for (int r = 0; r < 3; r++) {
                //print_map();
                rotate_90(i, j);
                //print_map();
                int tmpResult = check_value();
                if (tmpResult > maxResult || (tmpResult == maxResult && r < maxR)) {
                    maxResult = tmpResult;
                    maxX = i;
                    maxY = j;
                    maxR = r;
                }
            }
            rotate_90(i, j);
        }
    }
    if (maxResult > 0) {
        for (int r = 0; r <= maxR; r++)
            rotate_90(maxX, maxY);
        result += maxResult;

        //print_map();
        
        break_and_fill();
        //print_map();
        //cout << "-------------" << endl;
        int chain_value = check_value();
        while (chain_value > 0) {
            result += chain_value;
            break_and_fill();
            chain_value = check_value();
        }
        return true;
    }
    return false;
}


int main() {
    // 여기에 코드를 작성해주세요.
    get_input();
    bool result_flag = false;
    for (int i = 0; i < K; i++) {
        if (try_find() == false)
            break;
        cout << result << " ";
        result = 0;
        result_flag = true;
    }
    if (!result_flag)
        cout << 0 << endl;
    return 0;
}