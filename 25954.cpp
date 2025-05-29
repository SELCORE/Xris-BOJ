#include <bits/stdc++.h>
using namespace std;

const int MAXN = 7070;

int rowTransition[MAXN][MAXN];
int colTransition[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    int n = a.size(), m = b.size();

    // 첫 번째 행과 열 초기화
    for (int j = 0; j <= m; ++j) rowTransition[0][j] = j;
    for (int i = 0; i <= n; ++i) colTransition[i][0] = 0;

    // 동적 계획법 계산
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                rowTransition[i][j] = colTransition[i][j - 1];
                colTransition[i][j] = rowTransition[i - 1][j];
            } else {
                rowTransition[i][j] = max(rowTransition[i - 1][j], colTransition[i][j - 1]);
                colTransition[i][j] = min(rowTransition[i - 1][j], colTransition[i][j - 1]);
            }
        }
    }

    // 최종 결과 계산
    long long answer = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int segmentLen = j - rowTransition[i][j];
            if (segmentLen > 0) {
                answer += 1LL * (m - j + 1) * segmentLen;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}