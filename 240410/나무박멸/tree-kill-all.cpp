#include <iostream>

#define MAX_N 22

int N, M, K, C;

int map[MAX_N][MAX_N];
int tmp_map[MAX_N][MAX_N];
int drug[MAX_N][MAX_N];

int result = 0;

int dx[8] = {-1, 0, 1, 0, -1, 1, 1, -1};
int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};

using namespace std;

void print_map() {
    cout << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void get_input() {
    cin >> N >> M >> K >> C;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
}

bool check_valid(int x, int y) {
    return !(x < 0 || y < 0 || x == N || y == N );
}

int count_tree(int x, int y) {
    int tmp = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!check_valid(nx, ny))
            continue;
        if (map[nx][ny] > 0)
            tmp++;
    }
    return tmp;
}
int count_space(int x, int y) {
    int tmp = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!check_valid(nx, ny))
            continue;
        if (map[nx][ny] == 0 && drug[nx][ny] == 0)
            tmp++;
    }
    return tmp;
}

void grow_up() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] <= 0)
                continue;
            int treeCnt = count_tree(i, j);
            map[i][j] += treeCnt;
        }
    }
}
void grop_over() {
    // clear tmp
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tmp_map[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] <= 0)
                continue;
            int spaceCnt = count_space(i, j);
            if (spaceCnt == 0)
                continue;
            for (int d = 0; d < 4; d++) {
                int nx = i + dx[d];
                int ny = j + dy[d];
                if (!check_valid(nx, ny))
                    continue;
                if (map[nx][ny] == 0 && drug[nx][ny] == 0)
                    tmp_map[nx][ny] += map[i][j] / spaceCnt;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tmp_map[i][j] > 0)
                map[i][j] = tmp_map[i][j];
        }
    }
}

void push_drug() {
    int max_tree = 0;
    int max_x, max_y;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] <= 0)
                continue;
            int tmp_tree = map[i][j];
            for (int d = 4; d < 8; d++) {
                for (int k = 1; k <= K; k++) {
                    int nx = i + dx[d] * k;
                    int ny = j + dy[d] * k;
                    if (!check_valid(nx, ny))
                        continue;
                    if (drug[nx][ny] > 0)
                        continue;
                    if (map[nx][ny] == -1)
                        break;
                    tmp_tree += map[nx][ny];
                }
            }
            if (tmp_tree > max_tree) {
                max_tree = tmp_tree;
                max_x = i;
                max_y = j;
            }
        }
    }
    result += max_tree;

    for (int d = 4; d < 8; d++) {
        for (int k = 1; k <= K; k++) {
            int nx = max_x + dx[d] * k;
            int ny = max_y + dy[d] * k;
            if (!check_valid(nx, ny))
                continue;
            if (map[nx][ny] == -1)
                break;
            map[nx][ny] = 0;
            drug[nx][ny] = C;
        }
    }   
}

int main() {
    // 여기에 코드를 작성해주세요.
    get_input();
    while (M--) {
        grow_up();
        grop_over();
        push_drug();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (drug[i][j] > 0)
                    drug[i][j]--;
            }
        }
    }
    cout << result;
    return 0;
}