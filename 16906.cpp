// 시간제한 1초
// 메모리 제한 512MB

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

// 트라이 구조체
struct Trie {
    int nxt[2], flag;
    Trie() : nxt{}, flag(0) {}
};
vector<Trie> node(1); // 루트 노드 생성

// 길이가 n인 이진 문자열 생성 (트라이에 삽입하면서)
string Sol(int n) {
    string ret;

    function<bool(int, int)> DFS = [&](int cur, int dep) -> bool {
        if (dep == n) {
            if (node[cur].flag) return false;  // 이미 누군가의 접두어
            return node[cur].flag = 1;         // 사용 확정
        }
        for (int i = 0; i < 2; ++i) {
            if (!node[cur].nxt[i]) {
                node[cur].nxt[i] = node.size();
                node.push_back(Trie());
            }
            ret.push_back(i + '0');
            if (DFS(node[cur].nxt[i], dep + 1)) {
                node[cur].flag = 1;
                return true;
            }
            ret.pop_back(); // 백트래킹
        }
        return false;
    };

    if (DFS(0, 0)) return ret;
    return ""; // 실패 시 빈 문자열 반환
}

int main() {
    fastio;
    int n;
    cin >> n;

    vector<pair<int, int>> lengths(n);
    for (int i = 0; i < n; ++i) {
        cin >> lengths[i].first;
        lengths[i].second = i; // 원래 인덱스 기억
    }

    sort(lengths.rbegin(), lengths.rend()); // 긴 길이부터 배치
    vector<string> ans(n);

    for (auto& [len, idx] : lengths) {
        ans[idx] = Sol(len);
        if (ans[idx].empty()) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << 1 << '\n';
    for (const auto& s : ans) cout << s << '\n';
}