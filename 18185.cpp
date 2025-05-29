// 시간 제한 0.5초 (추가 시간 X)
// 메모리 제한 32MB

#include <iostream>
#include <algorithm>
using namespace std;

int factorys[10003];
int n;
int answer = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> factorys[i];

    for (int i = 1; i <= n; i++) {
        if (factorys[i + 1] > factorys[i + 2]) {
            int count = min(factorys[i], factorys[i + 1] - factorys[i + 2]);
            answer += 5 * count;
            factorys[i]     -= count;
            factorys[i + 1] -= count;

            int count2 = min({ factorys[i], factorys[i + 1], factorys[i + 2] });
            answer += 7 * count2;
            factorys[i]     -= count2;
            factorys[i + 1] -= count2;
            factorys[i + 2] -= count2;
        }
        else {
            int count = min({ factorys[i], factorys[i + 1], factorys[i + 2] });
            answer += 7 * count;
            factorys[i]     -= count;
            factorys[i + 1] -= count;
            factorys[i + 2] -= count;

            int count2 = min(factorys[i], factorys[i + 1]);
            answer += 5 * count2;
            factorys[i]     -= count2;
            factorys[i + 1] -= count2;
        }

        answer += 3 * factorys[i];
        factorys[i] = 0;
    }

    cout << answer << '\n';
}