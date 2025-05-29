#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

string inputNumber;
string digitValueStr = "6255456375";
i64 originalNumber = 0, targetSum = 0;
char dp[20][150][2];  // [position][remaining sum][isFree]

char solveDP(int pos, int remainingSum, bool isFree) {
    if (pos == 0) return (remainingSum != 0 || !isFree) ? 10 : 0;
    if (remainingSum <= 0) return 10;

    char& result = dp[pos][remainingSum][isFree];
    if (result != -1) return result;

    for (int digit = isFree ? 0 : inputNumber[pos - 1]; digit < 10; digit++) {
        int nextSum = (pos == inputNumber.size()) ? remainingSum : remainingSum - digitValueStr[digit];
        if (solveDP(pos - 1, nextSum, isFree || digit > inputNumber[pos - 1]) < 10) {
            return result = digit;
        }
    }
    return result = 10;
}

i64 buildAnswer(int pos, int remainingSum, bool isFree) {
    if (pos == 0) return 0;

    int digit = solveDP(pos, remainingSum, isFree);
    i64 power = 1;
    for (int i = 1; i < pos; i++) power *= 10;

    int nextSum = (pos == inputNumber.size()) ? remainingSum : remainingSum - digitValueStr[digit];
    return power * digit + buildAnswer(pos - 1, nextSum, isFree || digit > inputNumber[pos - 1]);
}

int main() {
    fastio;
    memset(dp, -1, sizeof dp);

    cin >> inputNumber;
    for (char& c : digitValueStr) c -= '0';  // digitValueStr을 숫자로 변환
    for (char& c : inputNumber) {
        c -= '0';
        targetSum += digitValueStr[c];
        originalNumber = 10 * originalNumber + c;
    }

    reverse(inputNumber.begin(), inputNumber.end());
    inputNumber.push_back(0);  // 자리수 보정용 dummy

    cout << buildAnswer(inputNumber.size(), targetSum, 0) - originalNumber << '\n';
}