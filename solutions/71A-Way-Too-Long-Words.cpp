// 71A – Way Too Long Words.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        if ((int)s.size() <= 10) {
            cout << s << "\n";
        } else {
            cout << s.front() << (int)s.size() - 2 << s.back() << "\n";
        }
    }
    return 0;
}
