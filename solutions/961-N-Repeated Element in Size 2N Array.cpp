#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int repeatedNTimes(vector<int>& a) {
        int n = (int)a.size();
        for (int i = 0; i + 1 < n; ++i)
            if (a[i] == a[i + 1]) return a[i];

        for (int i = 0; i + 2 < n; ++i)
            if (a[i] == a[i + 2]) return a[i];

        for (int i = 0; i + 3 < n; ++i)
            if (a[i] == a[i + 3]) return a[i];

        return a[0];
    }
};
