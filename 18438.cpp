// 시간 제한 1초
// 메모리 제한 4MB

#include <bits/stdc++.h>
using namespace std;

string a, b, ans;

vector<int> lcs_dp(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size();
    vector<int> curr(m + 1), prev(m + 1);
    for (int i = 0; i < n; i++) {
        swap(curr, prev);
        for (int j = 0; j < m; j++) {
            if (s1[i] == s2[j]) curr[j + 1] = prev[j] + 1;
            else curr[j + 1] = max(curr[j], prev[j + 1]);
        }
    }
    return curr;
}

void hirschberg(const string& A, const string& B) {
    int n = A.size(), m = B.size();
    if (n == 0 || m == 0) return;
    if (n == 1) {
        for (char c : B) {
            if (c == A[0]) {
                ans += c;
                break;
            }
        }
        return;
    }

    int mid = n / 2;
    auto L = lcs_dp(A.substr(0, mid), B);
    string Ar(A.rbegin(), A.rend()), Br(B.rbegin(), B.rend());
    auto R = lcs_dp(Ar.substr(0, n - mid), Br);
    reverse(R.begin(), R.end());

    int idx = 0, max_sum = 0;
    for (int i = 0; i <= m; i++) {
        if (L[i] + R[i] > max_sum) {
            max_sum = L[i] + R[i];
            idx = i;
        }
    }

    hirschberg(A.substr(0, mid), B.substr(0, idx));
    hirschberg(A.substr(mid), B.substr(idx));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> a >> b;
    hirschberg(a, b);
    cout << ans.size() << '\n' << ans << '\n';
}