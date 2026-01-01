// 158A – Next Round.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int threshold = a[k - 1];
    int ans = 0;
    for (int x : a) if (x >= threshold && x > 0) ans++;
    cout << ans << "\n";
    return 0;
}
