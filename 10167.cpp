#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define press(v) (v).erase(unique(all(v)), (v).end())
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> pii;

const int MAX = 3011;
const ll INF = 1e16;

struct Point {
    ll x, y, cost;
};

struct Node {
    ll lsum, rsum, sum, maxsum;
};

// 전역 변수
ll Mx = 1, My = 1, N;
ll ans = -INF;
ll a[MAX][MAX];
Point p[MAX];
pl tmpX[MAX], tmpY[MAX];
vector<pl> yList[MAX]; // y좌표별로 (압축된 x좌표, cost)
Node tree[1 << 14];

// 세그먼트 트리 merge 연산
Node merge(Node A, Node B) {
    return {
        max(A.lsum, A.sum + B.lsum),
        max(B.rsum, B.sum + A.rsum),
        A.sum + B.sum,
        max({A.maxsum, B.maxsum, A.rsum + B.lsum})
    };
}

// 세그먼트 트리 구간 쿼리
Node query(int node, int s, int e, int left, int right) {
    if (e < left || right < s) return {-INF, -INF, -INF, -INF};
    if (left <= s && e <= right) return tree[node];
    int mid = (s + e) / 2;
    return merge(
        query(node * 2, s, mid, left, right),
        query(node * 2 + 1, mid + 1, e, left, right)
    );
}

// 세그먼트 트리 업데이트
void update(int node, int s, int e, int idx, ll val) {
    if (idx < s || e < idx) return;
    
    tree[node].lsum += val;
    tree[node].rsum += val;
    tree[node].sum += val;
    tree[node].maxsum += val;

    if (s != e) {
        int mid = (s + e) / 2;
        update(node * 2, s, mid, idx, val);
        update(node * 2 + 1, mid + 1, e, idx, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> p[i].x >> p[i].y >> p[i].cost;
        tmpX[i] = {p[i].x, i};
        tmpY[i] = {p[i].y, i};
    }

    // 좌표 압축 (X)
    sort(tmpX + 1, tmpX + N + 1);
    for (int i = 1; i <= N; i++) {
        if (i != 1 && tmpX[i - 1].first != tmpX[i].first) Mx++;
        p[tmpX[i].second].x = Mx;
    }

    // 좌표 압축 (Y)
    sort(tmpY + 1, tmpY + N + 1);
    for (int i = 1; i <= N; i++) {
        if (i != 1 && tmpY[i - 1].first != tmpY[i].first) My++;
        p[tmpY[i].second].y = My;
    }

    // 데이터 재배치
    for (int i = 1; i <= N; i++) {
        a[p[i].x][p[i].y] = p[i].cost;
        yList[p[i].y].emplace_back(p[i].x, p[i].cost);
    }

    // 모든 y-구간 쌍에 대해 Kadane's algorithm + 세그먼트 트리
    for (int yStart = 1; yStart <= My; yStart++) {
        memset(tree, 0, sizeof(tree));
        for (int yEnd = yStart; yEnd <= My; yEnd++) {
            for (auto [x, cost] : yList[yEnd]) {
                update(1, 1, N, x, cost);
            }
            ans = max(ans, query(1, 1, N, 1, N).maxsum);
        }
    }

    cout << ans << "\n";
    return 0;
}