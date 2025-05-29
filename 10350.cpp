#include <iostream>
#include <cmath>
#define MAX 20001
using namespace std;
typedef long long ll;

int dp[MAX];
int N;

void init() {
    for (int i = 1; i <= (N << 1); i++) {
        dp[i] += dp[i - 1];
    }
}

void func() {
    init();
    ll ret = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = i; j < N + i; j++) {
            int sum = dp[j] - dp[i - 1];
            int total = dp[N + i - 1] - dp[i - 1];
            if (sum >= 0) continue;
            ret += (ll)ceil((double)(-sum) / (double)total);
        }
    }

    cout << ret << '\n';
}

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> dp[i];
        dp[i + N] = dp[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    input();
    func();

    return 0;
}
