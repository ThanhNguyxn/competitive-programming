// 791A – Bear and Big Brother.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    int years = 0;
    while (a <= b) {
        a *= 3;
        b *= 2;
        years++;
    }
    cout << years << "\n";
    return 0;
}
