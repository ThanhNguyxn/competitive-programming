// 1628B - Peculiar Movie Preferences
#include <bits/stdc++.h>
using namespace std;

static bool is_pal(const string& s) {
    for (int i = 0, j = (int)s.size() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        unordered_set<string> seen;   // all previous strings (len 2 or 3)
        unordered_set<string> pref3;  // prefix(2) of previous len-3 strings
        seen.reserve((size_t)n * 2);
        pref3.reserve((size_t)n * 2);

        bool ok = false;

        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;

            if (ok) continue;

            if (is_pal(s)) {
                ok = true;
                continue;
            }

            string rev = s;
            reverse(rev.begin(), rev.end());

            // len2+len2 or len3+len3
            if (seen.count(rev)) {
                ok = true;
                continue;
            }

            if ((int)s.size() == 2) {
                // previous len3 "abc" + current "ba" => "abcba"
                // need previous prefix2 == reverse(current)
                if (pref3.count(rev)) {
                    ok = true;
                    continue;
                }
            } else { // len == 3
                // previous len2 "cb" + current "abc" => "cbabc" (palindrome)
                // need previous len2 == reverse(last2) = s[2]s[1]
                string need = s.substr(1, 2);
                reverse(need.begin(), need.end());
                if (seen.count(need)) {
                    ok = true;
                    continue;
                }
            }

            seen.insert(s);
            if ((int)s.size() == 3) pref3.insert(s.substr(0, 2));
        }

        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
