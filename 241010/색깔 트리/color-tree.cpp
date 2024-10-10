#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int Q;
int parent[110000] = { 0 };
int color[110000] = { 0 };
int colors[110000] = { 0 };
int max_depth[110000] = { 0 };
vector<int> childs[110000];
vector<int> results;

bool check_add(int p_id) {
    int now_nodes = 1;
    while (p_id != -1) {
        now_nodes++;
        if (max_depth[p_id] < now_nodes)
            return false;
        p_id = parent[p_id];
    }
    return true;
}

void update_colors(int p_id) {
    while (p_id != -1) {
        int tmp_color = color[p_id];
        colors[p_id] = 1 << --tmp_color;
        for (auto c : childs[p_id]) {
            colors[p_id] = colors[p_id] | colors[c];
        }
        p_id = parent[p_id];
    }
}

int main()
{
    cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        if (q == 100) {
            int m_id, p_id, c, max_d;
            cin >> m_id >> p_id >> c >> max_d;
            if (check_add(p_id) == true) {
                parent[m_id] = p_id;
                color[m_id] = c;
                max_depth[m_id] = max_d;
                colors[m_id] = 1 << --c;
                if (p_id != -1) {
                    childs[p_id].push_back(m_id);
                }

                update_colors(p_id);
            }
        }
        else if (q == 200) {
            int m_id, c;
            cin >> m_id >> c;
            deque<int> que;
            que.push_back(m_id);
            while (!que.empty()) {
                int now_node = que.front();
                que.pop_front();
                color[now_node] = c;
                int tmp_c = c;
                colors[now_node] = 1 << --tmp_c;
                for (auto child : childs[now_node]) {
                    que.push_back(child);
                }
            }
            update_colors(parent[m_id]);
        }
        else if (q == 300) {
            int m_id;
            cin >> m_id;
            results.push_back(color[m_id]);
        }
        else if (q == 400) {
            int score = 0;
            for (int i = 1; i <= 100001; i++) {
                if (parent[i] == 0)
                    continue;
                int cnt = 0;
                int color_byte = colors[i];
                while (color_byte > 0) {
                    if (color_byte & 1) {
                        cnt++;
                    }
                    color_byte = color_byte >> 1;
                }
                score += cnt * cnt;
            }
            results.push_back(score);
        }
    }
    for (auto s : results) {
        cout << s << endl;
    }
    return 0;
}