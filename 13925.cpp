#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

const ll MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

struct Seg {
    ll val, lazy_mul = 1, lazy_add = 0;
};

int n, q;
ll init[MAXN];
Seg tree[4 * MAXN];

void push(int node, int s, int e) {
    if (tree[node].lazy_mul != 1) {
        tree[node].val = tree[node].val * tree[node].lazy_mul % MOD;
        if (s != e) {
            for (int i = 0; i < 2; ++i) {
                int child = node * 2 + i;
                tree[child].lazy_mul = tree[child].lazy_mul * tree[node].lazy_mul % MOD;
                tree[child].lazy_add = tree[child].lazy_add * tree[node].lazy_mul % MOD;
            }
        }
        tree[node].lazy_mul = 1;
    }
    if (tree[node].lazy_add != 0) {
        tree[node].val = (tree[node].val + (e - s + 1) * tree[node].lazy_add) % MOD;
        if (s != e) {
            for (int i = 0; i < 2; ++i) {
                int child = node * 2 + i;
                tree[child].lazy_add = (tree[child].lazy_add + tree[node].lazy_add) % MOD;
            }
        }
        tree[node].lazy_add = 0;
    }
}

void update_add(int l, int r, ll v, int s, int e, int node) {
    push(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        tree[node].lazy_add = v;
        push(node, s, e);
        return;
    }
    int m = (s + e) / 2;
    update_add(l, r, v, s, m, node * 2);
    update_add(l, r, v, m + 1, e, node * 2 + 1);
    tree[node].val = (tree[node * 2].val + tree[node * 2 + 1].val) % MOD;
}

void update_mul(int l, int r, ll v, int s, int e, int node) {
    push(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        tree[node].lazy_mul = v;
        push(node, s, e);
        return;
    }
    int m = (s + e) / 2;
    update_mul(l, r, v, s, m, node * 2);
    update_mul(l, r, v, m + 1, e, node * 2 + 1);
    tree[node].val = (tree[node * 2].val + tree[node * 2 + 1].val) % MOD;
}

void update_set(int l, int r, ll v, int s, int e, int node) {
    push(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        tree[node].lazy_mul = 0;
        tree[node].lazy_add = v;
        push(node, s, e);
        return;
    }
    int m = (s + e) / 2;
    update_set(l, r, v, s, m, node * 2);
    update_set(l, r, v, m + 1, e, node * 2 + 1);
    tree[node].val = (tree[node * 2].val + tree[node * 2 + 1].val) % MOD;
}

ll query(int l, int r, int s, int e, int node) {
    push(node, s, e);
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node].val;
    int m = (s + e) / 2;
    return (query(l, r, s, m, node * 2) + query(l, r, m + 1, e, node * 2 + 1)) % MOD;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        ll x;
        scanf("%lld", &x);
        update_set(i, i, x, 1, n, 1);
    }

    scanf("%d", &q);
    while (q--) {
        int type;
        ll l, r, v;
        scanf("%d %lld %lld", &type, &l, &r);
        if (type == 1) {
            scanf("%lld", &v);
            update_add(l, r, v, 1, n, 1);
        } else if (type == 2) {
            scanf("%lld", &v);
            update_mul(l, r, v, 1, n, 1);
        } else if (type == 3) {
            scanf("%lld", &v);
            update_set(l, r, v, 1, n, 1);
        } else if (type == 4) {
            printf("%lld\n", query(l, r, 1, n, 1));
        }
    }
    return 0;
}
