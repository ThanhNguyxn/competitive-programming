// 1472C – Strange Game On A Strip.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n;
    cin >> n;
    vector<long long> a(n + 1), dp(n + 2, 0);

    for (int i = 1; i <= n; i++) cin >> a[i];

    long long best = 0;
    for (int i = n; i >= 1; i--) {
        int nxt = i + (int)a[i];
        dp[i] = a[i] + (nxt <= n ? dp[nxt] : 0LL);
        best = max(best, dp[i]);
    }
    cout << best << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
