#include <cstdio>
#include <queue>
using namespace std;

int n;
int ans[1000001];
priority_queue<int> pq;

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        // 인덱스를 빼줌으로써 보정
        a -= i;

        // 우선순위 큐에 두 번 넣고 한 번 pop 해서 top 유지
        pq.push(a);
        pq.push(a);
        pq.pop();

        // 현재까지의 최댓값을 저장
        ans[i] = pq.top();
    }

    // 뒤에서부터 오름차순 형태로 보정
    for (int i = n - 1; i >= 1; i--) {
        if (ans[i] > ans[i + 1]) {
            ans[i] = ans[i + 1];
        }
    }

    // 보정된 값 + 인덱스를 출력
    for (int i = 1; i <= n; i++) {
        printf("%d\n", ans[i] + i);
    }

    return 0;
}