// 1791G2 - Teleporters (Hard Version)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long c;
        cin >> n >> c;

        vector<long long> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<long long> leftCost(n + 1), bestCost(n + 1);
        vector<pair<long long, int>> ord;
        ord.reserve(n);

        for (int i = 1; i <= n; i++) {
            leftCost[i] = a[i] + i;
            long long rightCost = a[i] + (n + 1LL - i);
            bestCost[i] = min(leftCost[i], rightCost);
            ord.push_back({bestCost[i], i});
        }

        sort(ord.begin(), ord.end());

        vector<long long> pref(n + 1, 0);
        vector<int> pos(n + 1, -1);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + ord[i].first;
            pos[ord[i].second] = i;
        }

        auto can_take = [&](int firstIdx, int take, long long budget) -> bool {
            if (take <= 0) return true;
            int p = pos[firstIdx];
            if (p >= take) {
                return pref[take] <= budget;
            } else {
                if (take + 1 > n) return false;
                long long sum = pref[take + 1] - bestCost[firstIdx];
                return sum <= budget;
            }
        };

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (leftCost[i] > c) continue;
            long long budget = c - leftCost[i];

            int lo = 0, hi = n - 1;
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                if (can_take(i, mid, budget)) lo = mid;
                else hi = mid - 1;
            }
            ans = max(ans, 1 + lo);
        }

        cout << ans << "\n";
    }
    return 0;
}
