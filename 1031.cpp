from collections import deque

# BFS로 증가 경로 탐색
def bfs():
    queue = deque([0])
    parent = [-1] * total_nodes
    while queue:
        current = queue.popleft()
        for neighbor in adj[current]:
            if parent[neighbor] < 0 and capacity[current][neighbor] - flow[current][neighbor] > 0:
                parent[neighbor] = current
                queue.append(neighbor)
                if neighbor == sink:
                    return parent
    return None

# 특정 간선(i, j)을 제외한 증가 경로 탐색
def update_path(i, j):
    queue = deque([i])
    parent = [-1] * total_nodes
    while queue:
        current = queue.popleft()
        for neighbor in adj[current]:
            if (0 < neighbor < i) or (current == i and neighbor <= j) or parent[neighbor] != -1:
                continue
            if capacity[current][neighbor] - flow[current][neighbor] > 0:
                parent[neighbor] = current
                queue.append(neighbor)
                if neighbor == j:
                    return parent
    return None

# 입력 처리
[N, M], row_sums, col_sums = [[*map(int, input().split())] for _ in range(3)]
total_nodes = N + M + 2
source, sink = 0, total_nodes - 1

# 유량 그래프 초기화
capacity = [[0] * total_nodes for _ in range(total_nodes)]
flow = [[0] * total_nodes for _ in range(total_nodes)]
adj = [[] for _ in range(total_nodes)]

# Source → Row
for i in range(1, N + 1):
    capacity[source][i] = row_sums[i - 1]
    adj[source].append(i)
    adj[i].append(source)

    # Row → Column (초기 용량: 1)
    for j in range(1, M + 1):
        col_node = j + N
        capacity[i][col_node] = 1
        adj[i].append(col_node)
        adj[col_node].append(i)

# Column → Sink
for j in range(1, M + 1):
    col_node = j + N
    capacity[col_node][sink] = col_sums[j - 1]
    adj[col_node].append(sink)
    adj[sink].append(col_node)

# Edmonds-Karp 알고리즘 (BFS 기반 최대 유량)
while (parent := bfs()):
    current = sink
    while current != source:
        prev = parent[current]
        flow[prev][current] += 1
        flow[current][prev] -= 1
        current = prev

# 유량이 정확히 필요한 값만큼 흘렀는지 확인
if sum(flow[source]) == sum(row_sums) == sum(col_sums):
    # 출력 전 flow[i][j] == 1 인 것들만 재확인
    for i in range(1, N + 1):
        for j in range(N + 1, N + M + 1):
            if flow[i][j] == 1:
                if (parent := update_path(i, j)):
                    # 경로가 존재하면 flow 업데이트
                    flow[i][j] -= 1
                    cur = j
                    while cur != i:
                        prev = parent[cur]
                        flow[prev][cur] += 1
                        flow[cur][prev] -= 1
                        cur = prev

    # 결과 출력 (0/1 매트릭스)
    for i in range(1, N + 1):
        print(*flow[i][N + 1:sink], sep="")
else:
    print(-1)
