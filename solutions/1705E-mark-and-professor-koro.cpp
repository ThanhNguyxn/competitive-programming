// 1705E - Mark and Professor Koro

#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> sum;   // number of ones
    vector<int> lazy;  // -1 none, 0 set 0, 1 set 1

    SegTree(int n_) : n(n_), sum(4 * n_, 0), lazy(4 * n_, -1) {}

    void apply(int v, int l, int r, int val) {
        sum[v] = val ? (r - l + 1) : 0;
        lazy[v] = val;
    }
    void push(int v, int l, int r) {
        if (l == r || lazy[v] == -1) return;
        int m = (l + r) / 2;
        apply(v * 2, l, m, lazy[v]);
        apply(v * 2 + 1, m + 1, r, lazy[v]);
        lazy[v] = -1;
    }

    void range_assign(int v, int l, int r, int ql, int qr, int val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(v, l, r, val);
            return;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        range_assign(v * 2, l, m, ql, qr, val);
        range_assign(v * 2 + 1, m + 1, r, ql, qr, val);
        sum[v] = sum[v * 2] + sum[v * 2 + 1];
    }
    void range_assign(int l, int r, int val) {
        if (l > r) return;
        range_assign(1, 0, n - 1, l, r, val);
    }

    int point_get(int v, int l, int r, int idx) {
        if (l == r) return sum[v];
        push(v, l, r);
        int m = (l + r) / 2;
        if (idx <= m) return point_get(v * 2, l, m, idx);
        return point_get(v * 2 + 1, m + 1, r, idx);
    }
    int point_get(int idx) { return point_get(1, 0, n - 1, idx); }

    int first_zero(int v, int l, int r, int ql) {
        if (r < ql) return -1;
        if (sum[v] == (r - l + 1)) return -1; // all ones
        if (l == r) return l;
        push(v, l, r);
        int m = (l + r) / 2;
        int res = first_zero(v * 2, l, m, ql);
        if (res != -1) return res;
        return first_zero(v * 2 + 1, m + 1, r, ql);
    }

    int first_one(int v, int l, int r, int ql) {
        if (r < ql) return -1;
        if (sum[v] == 0) return -1;
        if (l == r) return l;
        push(v, l, r);
        int m = (l + r) / 2;
        int res = first_one(v * 2, l, m, ql);
        if (res != -1) return res;
        return first_one(v * 2 + 1, m + 1, r, ql);
    }

    int first_zero(int ql) { return first_zero(1, 0, n - 1, ql); }
    int first_one(int ql) { return first_one(1, 0, n - 1, ql); }

    int last_one(int v, int l, int r) {
        if (sum[v] == 0) return -1;
        if (l == r) return l;
        push(v, l, r);
        int m = (l + r) / 2;
        int res = last_one(v * 2 + 1, m + 1, r);
        if (res != -1) return res;
        return last_one(v * 2, l, m);
    }
    int last_one() { return last_one(1, 0, n - 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // a[i] up to 2e5, carries add ~log2(n) more.
    int MAXA = 200000 + 35;
    SegTree st(MAXA);

    vector<int> a(n + 1);

    auto add_pow = [&](int p) {
        if (st.point_get(p) == 0) {
            st.range_assign(p, p, 1);
            return;
        }
        int z = st.first_zero(p);
        st.range_assign(p, z - 1, 0);
        st.range_assign(z, z, 1);
    };

    auto sub_pow = [&](int p) {
        if (st.point_get(p) == 1) {
            st.range_assign(p, p, 0);
            return;
        }
        int o = st.first_one(p);
        st.range_assign(p, o - 1, 1);
        st.range_assign(o, o, 0);
    };

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add_pow(a[i]);
    }

    while (q--) {
        int k, l;
        cin >> k >> l;
        sub_pow(a[k]);
        a[k] = l;
        add_pow(a[k]);
        cout << st.last_one() << "\n";
    }

    return 0;
}
