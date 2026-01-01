// 136A – Presents.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> inv(n + 1);
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        inv[p] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << inv[i];
    }
    cout << "\n";
    return 0;
}
