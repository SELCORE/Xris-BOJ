#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define IDX(v, x) (lower_bound(all(v), x) - v.begin())
using namespace std;

using ld = long double;
using Point = pair<ld, ld>;
constexpr ld EPS = 1e-10;

// ===== Point 연산자 오버로딩 =====
Point operator+(const Point &a, const Point &b) { return {a.x + b.x, a.y + b.y}; }
Point operator-(const Point &a, const Point &b) { return {a.x - b.x, a.y - b.y}; }
ld operator*(const Point &a, const Point &b) { return a.x * a.x + a.y * a.y; }             // 크기 제곱
ld operator/(const Point &a, const Point &b) { return a.x * b.y - b.x * a.y; }             // 외적
Point operator*(const Point &a, ld b) { return {a.x * b, a.y * b}; }
Point operator/(const Point &a, ld b) { return {a.x / b, a.y / b}; }
istream &operator>>(istream &in, Point &t) { in >> t.x >> t.y; return in; }

// ===== 유틸리티 함수 =====
ld ccw(const Point &p1, const Point &p2, const Point &p3) {
    ld res = (p2 - p1) / (p3 - p2);
    return (res > 0) - (res < 0);
}

ld distance_squared(const Point &p1, const Point &p2) {
    return (p1 - p2) * (p1 - p2);
}

bool segments_intersect(Point s1, Point e1, Point s2, Point e2) {
    ld cw1 = ccw(s1, e1, s2) * ccw(s1, e1, e2);
    ld cw2 = ccw(s2, e2, s1) * ccw(s2, e2, e1);
    if (cw1 == 0 && cw2 == 0) {
        if (s1 > e1) swap(s1, e1);
        if (s2 > e2) swap(s2, e2);
        return !(e1 < s2 || e2 < s1);
    }
    return cw1 <= 0 && cw2 <= 0;
}

bool segments_intersect(Point s1, Point e1, Point s2, Point e2, Point &res) {
    if (!segments_intersect(s1, e1, s2, e2)) return false;
    ld det = (e1 - s1) / (e2 - s2);
    if (abs(det) < EPS) return false;
    res = s1 + (e1 - s1) * ((s2 - s1) / (e2 - s2) / det);
    return true;
}

// ===== 볼록 다각형 클래스 =====
struct ConvexHull {
    vector<Point> pts;

    void build(vector<Point> points) {
        swap(points[0], *min_element(all(points)));
        sort(points.begin() + 1, points.end(), [&](const Point &a, const Point &b) {
            ld angle = ccw(points[0], a, b);
            return angle ? (angle > 0) : distance_squared(points[0], a) < distance_squared(points[0], b);
        });

        pts.clear();
        for (const Point &p : points) {
            while (pts.size() >= 2 && ccw(pts[pts.size() - 2], pts.back(), p) <= 0)
                pts.pop_back();
            pts.push_back(p);
        }
        assert(pts.size() >= 3);
    }

    bool contains(const Point &p) const {
        int i = lower_bound(pts.begin() + 1, pts.end(), p, [&](const Point &a, const Point &b) {
            ld angle = ccw(pts[0], a, b);
            return angle ? (angle > 0) : distance_squared(pts[0], a) < distance_squared(pts[0], b);
        }) - pts.begin();

        if (i == pts.size()) return false;
        if (i == 1) return ccw(pts[0], p, pts[1]) == 0 && pts[0] <= p && p <= pts[1];

        bool in_triangle = ccw(pts[0], p, pts[i]) * ccw(pts[0], p, pts[i - 1]) <= 0 &&
                           ccw(pts[i], pts[i - 1], pts[0]) * ccw(pts[i], pts[i - 1], p) <= 0;
        return in_triangle || ccw(pts[0], p, pts[i - 1]) != 0;
    }

    bool contains(const ConvexHull &hull) const {
        for (const Point &p : hull.pts)
            if (!contains(p)) return false;
        return true;
    }

    ld area() const {
        ld result = 0;
        for (int i = 0; i < pts.size(); ++i) {
            int j = (i + 1) % pts.size();
            result += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
        }
        return abs(result) / 2.0;
    }

    vector<pair<Point, Point>> edges() const {
        vector<pair<Point, Point>> result;
        for (int i = 0; i + 1 < pts.size(); ++i)
            result.emplace_back(pts[i], pts[i + 1]);
        if (!pts.empty())
            result.emplace_back(pts.back(), pts[0]);
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Point> poly1(n), poly2(m);
    for (Point &p : poly1) cin >> p;
    for (Point &p : poly2) cin >> p;

    ConvexHull hull1, hull2, intersection;
    hull1.build(poly1);
    hull2.build(poly2);

    if (hull1.contains(hull2)) {
        cout << fixed << setprecision(20) << hull2.area();
        return 0;
    }
    if (hull2.contains(hull1)) {
        cout << fixed << setprecision(20) << hull1.area();
        return 0;
    }

    vector<Point> inter_points;
    for (const auto &e1 : hull1.edges()) {
        for (const auto &e2 : hull2.edges()) {
            Point p;
            if (segments_intersect(e1.first, e1.second, e2.first, e2.second, p))
                inter_points.push_back(p);
        }
    }

    for (const Point &p : hull1.pts)
        if (hull2.contains(p))
            inter_points.push_back(p);

    for (const Point &p : hull2.pts)
        if (hull1.contains(p))
            inter_points.push_back(p);

    if (inter_points.empty()) {
        cout << 0;
        return 0;
    }

    intersection.build(inter_points);
    cout << fixed << setprecision(20) << intersection.area();
}
