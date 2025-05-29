#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long count_digit[10];

// 각 자릿수에 따라 숫자 세는 함수
void count_page(long long start, long long end, long long place) {
    while (start % 10 != 0 && start <= end) {
        long long temp = start;
        while (temp > 0) {
            count_digit[temp % 10] += place;
            temp /= 10;
        }
        start++;
    }

    if (start > end) return;

    while (end % 10 != 9 && start <= end) {
        long long temp = end;
        while (temp > 0) {
            count_digit[temp % 10] += place;
            temp /= 10;
        }
        end--;
    }

    long long cnt = (end / 10 - start / 10 + 1);
    for (int i = 0; i < 10; ++i)
        count_digit[i] += cnt * place;

    count_page(start / 10, end / 10, place * 10);
}

int main() {
    long long N;
    cin >> N;

    count_page(1, N, 1);

    for (int i = 0; i < 10; ++i)
        cout << count_digit[i] << " ";
    cout << "\n";

    return 0;
}
