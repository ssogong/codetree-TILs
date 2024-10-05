#include <iostream>
#include <queue>

#define MAX_L 70

using namespace std;

int node_C[1010];

int R, C, K; // 행, 열, 골렘의 개수를 의미합니다
int A[MAX_L+3][MAX_L]; // 실제 숲을 [3~R+2][0~C-1]로 사용하기위해 행은 3만큼의 크기를 더 갖습니다
int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};
bool isExit[MAX_L+3][MAX_L]; // 해당 칸이 골렘의 출구인지 저장합니다
int answer; // 각 정령들이 도달할 수 있는 최하단 행의 총합을 저장합니다

// (y, x)가 숲의 범위 안에 있는지 확인하는 함수입니다
bool inRange(int y, int x) {
    return 3 <= y && y < R+3 && 0 <= x && x < C;
}

// 숲에 있는 골렘들이 모두 빠져나갑니다
void resetMap() {
    for (int i=0;i<R+3;i++){
        for (int j=0;j<C;j++){
            A[i][j] = 0;
            isExit[i][j] = false;
        }
    }
}

// 골렘의 중심이 y, x에 위치할 수 있는지 확인합니다.
// 북쪽에서 남쪽으로 내려와야하므로 중심이 (y, x)에 위치할때의 범위와 (y-1, x)에 위치할떄의 범위 모두 확인합니다
bool canGo(int y, int x) {
    bool flag = 0 <= x-1 && x+1 < C && y+1 < R+3;
    flag = flag && (A[y-1][x-1] == 0);
    flag = flag && (A[y-1][x] == 0);
    flag = flag && (A[y-1][x+1] == 0);
    flag = flag && (A[y][x-1] == 0);
    flag = flag && (A[y][x] == 0);
    flag = flag && (A[y][x+1] == 0);
    flag = flag && (A[y+1][x] == 0);
    return flag;
}

// 정령이 움직일 수 있는 모든 범위를 확인하고 도달할 수 있는 최하단 행을 반환합니다
int bfs(int y, int x) {
    int result = y;
    queue<pair<int, int> > q;
    bool visit[MAX_L+3][MAX_L];
    for (int i=0;i<R+3;i++){
        for (int j=0;j<C;j++){
            visit[i][j] = false;
        }
    }

    q.push(make_pair(y, x));
    visit[y][x] = true;
    while(!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        for (int k=0; k<4; k++) {
            int ny = cur.first + dy[k], nx = cur.second + dx[k];
            // 정령의 움직임은 골렘 내부이거나
            // 골렘의 탈출구에 위치하고 있다면 다른 골렘으로 옮겨 갈 수 있습니다
            if (inRange(ny, nx) && !visit[ny][nx] && (A[ny][nx] == A[cur.first][cur.second] || (A[ny][nx] != 0 && isExit[cur.first][cur.second]))) {
                q.push(make_pair(ny, nx));
                visit[ny][nx] = true;
                result = max(result, ny);
            }
        }
    }
    return result;
}

// 골렘id가 중심 (y, x), 출구의 방향이 d일때 규칙에 따라 움직임을 취하는 함수입니다
// 1. 남쪽으로 한 칸 내려갑니다.
// 2. (1)의 방법으로 이동할 수 없으면 서쪽 방향으로 회전하면서 내려갑니다.
// 3. (1)과 (2)의 방법으로 이동할 수 없으면 동쪽 방향으로 회전하면서 내려갑니다.
void down(int y, int x, int d, int id) {
    if (canGo(y+1, x)) {
        // 아래로 내려갈 수 있는 경우입니다
        down(y+1, x, d, id);
    }
    else if (canGo(y+1, x-1)) {
        // 왼쪽 아래로 내려갈 수 있는 경우입니다
        down(y+1, x-1, (d+3)%4, id);
    }
    else if (canGo(y+1, x+1)) {
        // 오른쪽 아래로 내려갈 수 있는 경우입니다
        down(y+1, x+1, (d+1)%4, id);
    }
    else {
        // 1, 2, 3의 움직임을 모두 취할 수 없을떄 입니다.
        if (!inRange(y-1, x-1) || !inRange(y+1, x+1)) {
            // 숲을 벗어나는 경우 모든 골렘이 숲을 빠져나갑니다
            resetMap();
        } else {
            // 골렘이 숲 안에 정착합니다
            A[y][x] = id;
            for (int k = 0; k < 4; k++)
                A[y+dy[k]][x+dx[k]] = id;
            // 골렘의 출구를 기록하고
            isExit[y+dy[d]][x+dx[d]] = true;
            // bfs를 통해 정령이 최대로 내려갈 수 있는 행를 계산하여 누적합니다
            answer += bfs(y, x) - 3 + 1;
        }
    }
}

int main() {
    cin >> R >> C >> K;
    for (int id = 1; id <= K; id++) { // 골렘 번호 id
        int x, d;
        cin >> node_C[id] >> d; // 골렘의 출발 x좌표, 방향 d를 입력받습니다
        x = node_C[id];
        x--;
        down(0, x, d, id);
    }
    cout << answer << endl;
    return 0;
}