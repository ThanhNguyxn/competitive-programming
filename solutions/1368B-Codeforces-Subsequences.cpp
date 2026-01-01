// 1368B – Codeforces Subsequences.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k;
    cin >> k;

    const string base = "codeforces";
    vector<long long> cnt(10, 1);

    __int128 prod = 1;
    auto enough = [&]() -> bool { return prod >= (__int128)k; };

    int i = 0;
    while (!enough()) {
        prod /= cnt[i];
        cnt[i]++;
        prod *= cnt[i];
        i = (i + 1) % 10;
    }

    string out;
    out.reserve(1000);
    for (int j = 0; j < 10; j++) {
        out.append((size_t)cnt[j], base[j]);
    }

    cout << out << "\n";
    return 0;
}
