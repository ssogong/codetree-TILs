// 코드트리오모카세.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

int L, Q;


set<string> names;
unordered_map<string, int> entry_time;
unordered_map<string, int> exit_time;
unordered_map<string, int> position;


int person_num = 0, sushi_num = 0;

class Query {
public:
    int cmd, t, x, n;
    string name;

    Query(int cmd, int t, int x, int n, string name) {
        this->cmd = cmd;
        this->t = t;
        this->x = x;
        this->n = n;
        this->name = name;
    }
};

bool cmp(Query q1, Query q2) {
    if (q1.t != q2.t)
        return q1.t < q2.t;
    return q1.cmd < q2.cmd;
}

vector<Query> querys;
unordered_map<string, vector<Query>> p_querys;

void get_input() {
    cin >> L >> Q;
    while (Q--) {
        int cmd = -1, t = -1, x = -1, n = -1;
        string name;
        cin >> cmd;
        if (cmd == 100) {
            cin >> t >> x >> name;
            p_querys[name].push_back(Query(cmd, t, x, n, name));
        }
        else if (cmd == 200) {
            cin >> t >> x >> name >> n;

            names.insert(name);
            position[name] = x;
            entry_time[name] = t;
        }
        else {
            cin >> t;
        }
        querys.push_back(Query(cmd, t, x, n, name));
    }
}

int main()
{
    get_input();

    for (auto name : names) {
        exit_time[name] = 0;
        for (auto q : p_querys[name]) {
            int time_to_removed = 0;
            if (q.t < entry_time[name]) {
                int t_sushi_x = (q.x + (entry_time[name] - q.t)) % L;
                int additional_time = (position[name] - t_sushi_x + L) % L;
                time_to_removed = entry_time[name] + additional_time;
            }
            else {
                int additional_time = (position[name] - q.x + L) % L;
                time_to_removed = q.t + additional_time;
            }
            exit_time[name] = max(exit_time[name], time_to_removed);

            querys.push_back(Query(111, time_to_removed, -1, -1, name));
        }
    }

    for (auto name : names) {
        querys.push_back(Query(222, exit_time[name], -1, -1, name));
    }

    sort(querys.begin(), querys.end(), cmp);

    for (int i = 0; i < querys.size(); i++) {
        if (querys[i].cmd == 100)
            sushi_num++;
        else if (querys[i].cmd == 111)
            sushi_num--;
        else if (querys[i].cmd == 200)
            person_num++;
        else if (querys[i].cmd == 222)
            person_num--;
        else
            cout << person_num << " " << sushi_num << endl;
    }

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