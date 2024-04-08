// 왕실의기사대결.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_L 45
#define MAX_N 35

typedef struct {
    int r;
    int c;
    int h;
    int w;
    int k;
    int d;
} Knight;

int map[MAX_L][MAX_L];
Knight knight[MAX_N];
Knight tmp_knight[MAX_N];

int visited[MAX_N];

int L, N, Q;
int result = 0;

// up, right, down, left
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

vector<int> q;

void print() {
    cout << endl;
    for (int i = 0; i <= L + 1; i++) {
        for (int j = 0; j <= L + 1; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void getInput() {
    cin >> L >> N >> Q;
    for (int i = 0; i <= L + 1; i++) {
        for (int j = 0; j <= L + 1; j++) {
            if (i == 0 || j == 0 || i == L + 1 || j == L + 1) {
                map[i][j] = 2;
                continue;
            }
            cin >> map[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        cin >> knight[i].r >> knight[i].c >> knight[i].h >> knight[i].w >> knight[i].k;
    }
}

int main()
{
    getInput();

    while (Q--) {
        q.clear();
        int first_i, d;
        cin >> first_i >> d;
        
        bool stop_flag = false;

        if (knight[first_i].k <= 0)
            continue;

        for (int a = 0; a < MAX_N; a++) {
            visited[a] = 0;
        }
        for (int a = 0; a <= N; a++) {
            tmp_knight[a].r = knight[a].r;
            tmp_knight[a].c = knight[a].c;
        }

        queue<int> que;
        que.push(first_i);
        visited[first_i] = 1;

        knight[first_i].r = knight[first_i].r + dx[d];
        knight[first_i].c = knight[first_i].c + dy[d];

        while (!que.empty()) {
            int i = que.front();
            que.pop();


            int new_r = knight[i].r;
            int new_c = knight[i].c;

            int tmp_r, tmp_c, tmp_w, tmp_h;
            // up
            if (d == 0) {
                tmp_r = new_r;
                tmp_c = new_c;
                tmp_w = knight[i].w;
                tmp_h = 1;
            }
            // right
            else if (d == 1) {
                tmp_r = new_r;
                tmp_c = new_c + knight[i].w - 1;
                tmp_w = 1;
                tmp_h = knight[i].h;
            }
            // down
            else if (d == 2) {
                tmp_r = new_r + knight[i].h - 1;
                tmp_c = new_c;
                tmp_w = knight[i].w;
                tmp_h = 1;
            }
            // left
            else {
                tmp_r = new_r;
                tmp_c = new_c;
                tmp_w = 1;
                tmp_h = knight[i].h;
            }

            // check wall
            for (int a = 0; a < tmp_h; a++) {
                for (int b = 0; b < tmp_w; b++) {
                    int x = tmp_r + a;
                    int y = tmp_c + b;
                    if (map[x][y] == 2)
                        stop_flag = true;
                }
            }
            if (stop_flag)
                break;

            // check knight
            for (int a = 0; a < tmp_h; a++) {
                for (int b = 0; b < tmp_w; b++) {
                    int x = tmp_r + a;
                    int y = tmp_c + b;

                    for (int c = 1; c <= N; c++) {
                        if (visited[c] || c == i || knight[c].k <= 0)
                            continue;
                        if (x < knight[c].r || x >= knight[c].r + knight[c].h || y < knight[c].c || y >= knight[c].c + knight[c].w)
                            continue;
                        visited[c] = true;
                        knight[c].r = knight[c].r + dx[d];
                        knight[c].c = knight[c].c + dy[d];
                        que.push(c);
                    }
                }
            }
            if (stop_flag)
                break;
            q.push_back(i);
        }
        if (stop_flag) {
            for (int a = 0; a <= N; a++) {
                knight[a].r = tmp_knight[a].r;
                knight[a].c = tmp_knight[a].c;
            }
            continue;
        }

        // damange
        for (auto a : q) {
            if (a == first_i)
                continue;
            for (int w = 0; w < knight[a].h; w++) {
                for (int h = 0; h < knight[a].w; h++) {
                    if (knight[a].k == 0)
                        break;
                    int x = knight[a].r + w;
                    int y = knight[a].c + h;
                    if (map[x][y] == 1) {
                        knight[a].k--;
                        knight[a].d++;
                    }
                }
            }
        }
    }
    for (int a = 1; a <= N; a++) {
        if (knight[a].k > 0)
            result += knight[a].d;
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