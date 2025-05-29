def binary_search(start_x, target_y, left, right):
    ret = float('inf')
    # 이분 탐색으로 최적의 기울기(pos)를 찾음
    while abs(right - left) / 2 > 1.1920929e-7:
        mid = (left + right) / 2
        temp_dist, final_y = simulate_path(-10, start_x, mid)
        ret = temp_dist
        if final_y < target_y:
            left = mid
        else:
            right = mid
    return ret


def simulate_path(x, y, slope):
    total_distance = 0
    for _ in range(2000):
        if y < -13 or y > 13:
            return [float('inf'), y]

        # 거리 누적
        total_distance += (y_potential(x, y) + 1) * ((slope ** 2 + 1) ** 0.5) / 100

        # 위치 갱신
        x += 0.01
        y += slope / 100
        slope += euler_lagrange(x, y, slope) / 100

    return [total_distance, y]


def y_potential(x, y):
    total = 0
    for island_y in islands:
        d = x ** 2 + (y - island_y) ** 2
        if d < 1.1920929e-7:
            return float('inf')
        total += d ** -1
    return total


def euler_lagrange(x, y, slope):
    temp = slope ** 2 + 1
    denominator = 1
    p1 = 0
    p2 = 0

    for island_y in islands:
        d = x ** 2 + (y - island_y) ** 2
        denominator += d ** -1
        p1 += (y - island_y) / d ** 2
        p2 += (x + (y - island_y) * slope) / d ** 2

    return 2 * temp * (slope * p2 - temp * p1) / denominator


# 입력 및 결과 출력
T = int(input())
for case_num in range(1, T + 1):
    n, a, b = map(float, input().split())
    islands = list(map(float, input().split()))

    # 탐색할 초기 기울기 후보 리스트 생성
    slopes = sorted([-2, 2] + [(island - a) / 10 for island in islands])
    result = float('inf')

    # 인접한 기울기 구간마다 이분 탐색 수행
    for i in range(len(slopes) - 1):
        temp_result = binary_search(a, b, slopes[i], slopes[i + 1])
        result = min(result, temp_result)

    print(f'Case #{case_num}: {round(result, 2)}')