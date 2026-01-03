#include <bits/stdc++.h>
using namespace std;

// Codeforces 1579C - Ticks

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<string> g(n);
        for (int i = 0; i < n; i++) cin >> g[i];

        vector<vector<int>> dl(n, vector<int>(m, 0));
        vector<vector<int>> dr(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] != '*') continue;
                dl[i][j] = 1;
                dr[i][j] = 1;
                if (i > 0 && j > 0) dl[i][j] += dl[i - 1][j - 1];
                if (i > 0 && j + 1 < m) dr[i][j] += dr[i - 1][j + 1];
            }
        }

        // Diagonal diff arrays keyed by diagonal id and indexed by row i.
        int d1 = n + m - 1; // i - j + (m-1)
        int d2 = n + m - 1; // i + j
        vector<vector<int>> diff1(d1, vector<int>(n + 1, 0));
        vector<vector<int>> diff2(d2, vector<int>(n + 1, 0));

        auto id1 = [&](int i, int j) { return i - j + (m - 1); };
        auto id2 = [&](int i, int j) { return i + j; };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] != '*') continue;
                int s = min(dl[i][j], dr[i][j]) - 1; // arm length
                if (s < k) continue;

                int top = i - s;
                // left arm: (top, j-s) .. (i, j)
                {
                    int diag = id1(i, j);
                    diff1[diag][top] += 1;
                    diff1[diag][i + 1] -= 1;
                }
                // right arm: (top, j+s) .. (i, j)
                {
                    int diag = id2(i, j);
                    diff2[diag][top] += 1;
                    diff2[diag][i + 1] -= 1;
                }
            }
        }

        vector<vector<char>> covered(n, vector<char>(m, 0));

        // Apply diff1 along i for each diag, then mark cells on that diag.
        for (int diag = 0; diag < d1; diag++) {
            int cur = 0;
            for (int i = 0; i < n; i++) {
                cur += diff1[diag][i];
                if (cur <= 0) continue;
                // diag = i - j + (m-1) => j = i + (m-1) - diag
                int j = i + (m - 1) - diag;
                if (0 <= j && j < m) covered[i][j] = 1;
            }
        }
        // Apply diff2 along i for each diag, then mark cells on that diag.
        for (int diag = 0; diag < d2; diag++) {
            int cur = 0;
            for (int i = 0; i < n; i++) {
                cur += diff2[diag][i];
                if (cur <= 0) continue;
                // diag = i + j => j = diag - i
                int j = diag - i;
                if (0 <= j && j < m) covered[i][j] = 1;
            }
        }

        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == '*' && !covered[i][j]) {
                    ok = false;
                    break;
                }
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}
