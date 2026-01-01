// 1352C – K-th Not Divisible by n.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    long long n, k;
    cin >> n >> k;
    // Answer formula:
    // In each block of n numbers, (n-1) are not divisible by n.
    // ans = k + (k-1)/(n-1)
    long long ans = k + (k - 1) / (n - 1);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
