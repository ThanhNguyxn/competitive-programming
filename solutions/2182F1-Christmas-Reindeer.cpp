#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
static const int LOG = 61;

static inline int addmod(int a, int b){
    a += b;
    if(a >= MOD) a -= MOD;
    if(a < 0) a += MOD;
    return a;
}
static inline int submod(int a, int b){ return addmod(a, -b); }
static inline int mulmod(long long a, long long b){ return int((a*b)%MOD); }

static int modpow(int a, int e){
    long long r=1, x=a;
    while(e){
        if(e&1) r = r*x%MOD;
        x = x*x%MOD;
        e >>= 1;
    }
    return (int)r;
}

// build req like editorial
static vector<int> get_required(long long x){
    vector<int> req(LOG, 0);
    int cnt = 0;
    for(int i = LOG-1; i >= 0; --i){
        if((x >> i) & 1LL){
            req[i + cnt]++; // i+cnt < 61 for x<=1e18
            cnt++;
        }
    }
    return req;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> freq(LOG, 0);
    for(int i = 0; i < n; i++){
        int c; cin >> c;
        freq[c]++;
    }

    int maxN = n + m + 5; // F1: <= 1005
    vector<int> fact(maxN,1), invfact(maxN,1), pow2(maxN,1);
    for(int i=1;i<maxN;i++){
        fact[i] = mulmod(fact[i-1], i);
        pow2[i] = addmod(pow2[i-1], pow2[i-1]);
    }
    invfact[maxN-1] = modpow(fact[maxN-1], MOD-2);
    for(int i=maxN-2;i>=0;i--) invfact[i] = mulmod(invfact[i+1], i+1);

    auto C = [&](int N, int K)->int{
        if(K<0 || K>N) return 0;
        return mulmod(fact[N], mulmod(invfact[K], invfact[N-K]));
    };

    auto sum_greater = [&](int x, int y)->int{ // sum_{i=y+1..x} C(x,i)
        if(y >= x) return 0;
        int ans = pow2[x];
        for(int i=0;i<=y;i++) ans = submod(ans, C(x,i));
        return ans;
    };

    while(m--){
        int t; long long x;
        cin >> t >> x;
        if(t == 1){
            freq[(int)x]++;
        }else if(t == 2){
            freq[(int)x]--;
        }else{
            auto req = get_required(x);

            int cnt_less = 0;
            for(int i=0;i<LOG;i++) cnt_less += freq[i];

            int ans = 0;
            int cur = 1;
            for(int i=LOG-1;i>=0;i--){
                cnt_less -= freq[i];
                ans = addmod(ans, mulmod(cur, mulmod(sum_greater(freq[i], req[i]), pow2[cnt_less])));
                cur = mulmod(cur, C(freq[i], req[i]));
            }
            ans = addmod(ans, cur);
            cout << ans << "\n";
        }
    }
    return 0;
}
