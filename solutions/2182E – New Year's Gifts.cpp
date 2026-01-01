// 2182E – New Year's Gifts.cpp
#include <bits/stdc++.h>
using namespace std;

/*
    Greedy idea (editorial-style):

    - Every friend i needs at least y_i coins (mandatory).
      Subtract all y_i from the budget first.

    - If we do NOT use a box for friend i, we may "upgrade" by paying (z_i - y_i)
      to make them happy.

    - A box has a beauty value a. It can be used to make any friend happy whose
      requirement x <= a.

    - We iterate beauty from 1..m:
        * Add all friends that become available at this beauty into a multiset
          of upgrade costs d = z - y.
        * For each box of this beauty, use it on the friend with the largest d
          (saving the most money).
    - After all boxes are used, use remaining budget to pay upgrades for the
      cheapest remaining friends (smallest d first).
*/

static void solve_one() {
    int n, m;
    long long budget;
    cin >> n >> m >> budget;

    vector<int> boxCount(m, 0);
    for (int i = 0; i < m; ++i) {
        int a;                 // box beauty in [1..m]
        cin >> a;
        boxCount[a - 1]++;
    }

    vector<vector<int>> friendsAtBeauty(m); // friendsAtBeauty[x-1] stores (z-y)
    friendsAtBeauty.assign(m, {});
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        budget -= y;                       // mandatory minimum gift
        friendsAtBeauty[x - 1].push_back(z - y); // extra cost to upgrade without a box
    }

    // The statement guarantees feasibility in normal CF settings, but keep it safe.
    if (budget < 0) {
        cout << 0 << "\n";
        return;
    }

    long long happy = 0;
    multiset<int> extraCosts; // store (z - y) for currently available friends

    // Process beauties from low to high.
    for (int beauty = 0; beauty < m; ++beauty) {
        // Add newly available friends (x <= beauty+1).
        for (int d : friendsAtBeauty[beauty]) extraCosts.insert(d);

        // Use all boxes of this beauty on the most expensive upgrades.
        for (int cnt = 0; cnt < boxCount[beauty]; ++cnt) {
            if (extraCosts.empty()) break;
            auto it = prev(extraCosts.end()); // largest d
            extraCosts.erase(it);
            happy++;
        }
    }

    // Pay upgrades with remaining budget for the cheapest remaining friends.
    while (!extraCosts.empty()) {
        auto it = extraCosts.begin(); // smallest d
        if (*it > budget) break;
        budget -= *it;
        extraCosts.erase(it);
        happy++;
    }

    cout << happy << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
