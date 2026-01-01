// 4A – Watermelon.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w;
    cin >> w;
    cout << ((w > 2 && w % 2 == 0) ? "YES" : "NO") << "\n";
    return 0;
}
