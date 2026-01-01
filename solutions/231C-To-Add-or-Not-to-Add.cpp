// 231C – To Add or Not to Add.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    sort(a.begin(), a.end());
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

    int bestLen = 1;
    long long bestVal = a[0];

    int l = 0;
    for (int r = 0; r < n; r++) {
        while (l <= r) {
            long long len = r - l + 1;
            long long need = a[r] * len - (pref[r + 1] - pref[l]);
            if (need <= k) break;
            l++;
        }
        int len = r - l + 1;
        if (len > bestLen) {
            bestLen = len;
            bestVal = a[r];
        }
    }

    cout << bestLen << " " << bestVal << "\n";
    return 0;
}
