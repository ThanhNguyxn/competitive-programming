#include <bits/stdc++.h>
using namespace std;

static inline uint64_t rng_u64() {
    static uint64_t x = chrono::high_resolution_clock::now().time_since_epoch().count();
    x += 0x9e3779b97f4a7c15ULL;
    uint64_t z = x;
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}
static inline double rng_double() { // [0,1)
    return (rng_u64() >> 11) * (1.0 / 9007199254740992.0); // 2^53
}
static inline int rng_int(int n) { // [0, n)
    return (int)(rng_u64() % (uint64_t)n);
}

static inline int contrib(uint8_t mask) {
    if (!mask) return 0;
    unsigned x = mask;
    int lo = __builtin_ctz(x);
    int hi = 31 - __builtin_clz(x);
    int span = hi - lo + 1;
    int t = span + 2;
    return t * t;
}

struct State {
    int n, m, a;
    int E;
    vector<pair<int,int>> edge;     // (g,p)
    vector<int> slotOf;            // size E, in [0..41]
    vector<vector<int>> slotEdges; // 42 lists of edge indices
    vector<int> posInSlot;         // size E
    vector<uint64_t> gBusy, pBusy; // 42-bit masks
    vector<array<uint8_t,6>> gDay; // 7-bit masks per day
    vector<array<uint8_t,6>> pDay;
    int f = 0;

    void init(int _n, int _m, int _a, const vector<pair<int,int>>& edges) {
        n=_n; m=_m; a=_a;
        edge = edges;
        E = (int)edge.size();
        slotOf.assign(E, -1);
        slotEdges.assign(42, {});
        posInSlot.assign(E, -1);
        gBusy.assign(n, 0);
        pBusy.assign(m, 0);
        gDay.assign(n, {});
        pDay.assign(m, {});
        for (int i=0;i<n;i++) for (int d=0;d<6;d++) gDay[i][d]=0;
        for (int j=0;j<m;j++) for (int d=0;d<6;d++) pDay[j][d]=0;
        f = 0;
    }

    inline int delta_add(int g, int p, int slot) const {
        int d = slot / 7;
        int l = slot % 7;
        uint8_t bit = (uint8_t)(1u << l);

        uint8_t g0 = gDay[g][d];
        uint8_t g1 = (uint8_t)(g0 | bit);
        int dg = contrib(g1) - contrib(g0);

        uint8_t p0 = pDay[p][d];
        uint8_t p1 = (uint8_t)(p0 | bit);
        int dp = contrib(p1) - contrib(p0);

        return dg + dp;
    }

    inline int delta_move(int g, int p, int s1, int s2) const {
        int d1 = s1 / 7, l1 = s1 % 7;
        int d2 = s2 / 7, l2 = s2 % 7;
        uint8_t b1 = (uint8_t)(1u << l1);
        uint8_t b2 = (uint8_t)(1u << l2);

        int delta = 0;

        // group
        if (d1 == d2) {
            uint8_t oldm = gDay[g][d1];
            uint8_t newm = (uint8_t)((oldm & ~b1) | b2);
            delta += contrib(newm) - contrib(oldm);
        } else {
            uint8_t o1 = gDay[g][d1], n1 = (uint8_t)(o1 & ~b1);
            uint8_t o2 = gDay[g][d2], n2 = (uint8_t)(o2 | b2);
            delta += (contrib(n1) + contrib(n2) - contrib(o1) - contrib(o2));
        }

        // professor
        if (d1 == d2) {
            uint8_t oldm = pDay[p][d1];
            uint8_t newm = (uint8_t)((oldm & ~b1) | b2);
            delta += contrib(newm) - contrib(oldm);
        } else {
            uint8_t o1 = pDay[p][d1], n1 = (uint8_t)(o1 & ~b1);
            uint8_t o2 = pDay[p][d2], n2 = (uint8_t)(o2 | b2);
            delta += (contrib(n1) + contrib(n2) - contrib(o1) - contrib(o2));
        }

        return delta;
    }

    inline bool can_place(int g, int p, int slot, int forbidEdge = -1) const {
        if ((int)slotEdges[slot].size() >= a) return false;
        if ((gBusy[g] >> slot) & 1ULL) return false;
        if ((pBusy[p] >> slot) & 1ULL) return false;
        (void)forbidEdge;
        return true;
    }

    inline void remove_from_slot(int ei, int slot) {
        auto &v = slotEdges[slot];
        int pos = posInSlot[ei];
        int last = v.back();
        v[pos] = last;
        posInSlot[last] = pos;
        v.pop_back();
        posInSlot[ei] = -1;
    }

    inline void add_to_slot(int ei, int slot) {
        auto &v = slotEdges[slot];
        posInSlot[ei] = (int)v.size();
        v.push_back(ei);
    }

    inline void apply_move(int ei, int s2, int delta) {
        int s1 = slotOf[ei];
        auto [g,p] = edge[ei];

        int d1 = s1/7, l1 = s1%7;
        int d2 = s2/7, l2 = s2%7;
        uint8_t b1 = (uint8_t)(1u<<l1);
        uint8_t b2 = (uint8_t)(1u<<l2);

        remove_from_slot(ei, s1);
        gBusy[g] &= ~(1ULL<<s1);
        pBusy[p] &= ~(1ULL<<s1);
        gDay[g][d1] = (uint8_t)(gDay[g][d1] & ~b1);
        pDay[p][d1] = (uint8_t)(pDay[p][d1] & ~b1);

        slotOf[ei] = s2;
        add_to_slot(ei, s2);
        gBusy[g] |= (1ULL<<s2);
        pBusy[p] |= (1ULL<<s2);
        gDay[g][d2] = (uint8_t)(gDay[g][d2] | b2);
        pDay[p][d2] = (uint8_t)(pDay[p][d2] | b2);

        f += delta;
    }

    inline int delta_swap(int e1, int e2) const {
        int s1 = slotOf[e1], s2 = slotOf[e2];
        auto [g1,p1] = edge[e1];
        auto [g2,p2] = edge[e2];
        int d1 = s1/7, l1 = s1%7;
        int d2 = s2/7, l2 = s2%7;
        uint8_t b1 = (uint8_t)(1u<<l1);
        uint8_t b2 = (uint8_t)(1u<<l2);

        int delta = 0;

        auto calc_one_group = [&](int g) {
            int dd = 0;
            for (int d=0; d<6; d++) {
                uint8_t oldm = gDay[g][d];
                uint8_t newm = oldm;
                if (g == g1) {
                    if (d == d1) newm = (uint8_t)(newm & ~b1);
                    if (d == d2) newm = (uint8_t)(newm | b2);
                }
                if (g == g2) {
                    if (d == d2) newm = (uint8_t)(newm & ~b2);
                    if (d == d1) newm = (uint8_t)(newm | b1);
                }
                if (newm != oldm) dd += contrib(newm) - contrib(oldm);
            }
            return dd;
        };
        auto calc_one_prof = [&](int p) {
            int dd = 0;
            for (int d=0; d<6; d++) {
                uint8_t oldm = pDay[p][d];
                uint8_t newm = oldm;
                if (p == p1) {
                    if (d == d1) newm = (uint8_t)(newm & ~b1);
                    if (d == d2) newm = (uint8_t)(newm | b2);
                }
                if (p == p2) {
                    if (d == d2) newm = (uint8_t)(newm & ~b2);
                    if (d == d1) newm = (uint8_t)(newm | b1);
                }
                if (newm != oldm) dd += contrib(newm) - contrib(oldm);
            }
            return dd;
        };

        if (g1 == g2) {
            // group masks unchanged
        } else {
            delta += calc_one_group(g1);
            delta += calc_one_group(g2);
        }

        if (p1 == p2) {
            // prof masks unchanged
        } else {
            delta += calc_one_prof(p1);
            delta += calc_one_prof(p2);
        }

        return delta;
    }

    inline bool can_swap(int e1, int e2) const {
        if (e1 == e2) return false;
        int s1 = slotOf[e1], s2 = slotOf[e2];
        if (s1 == s2) return false;
        auto [g1,p1] = edge[e1];
        auto [g2,p2] = edge[e2];

        // Place e2 into s1 (after removing e1)
        if (g2 != g1 && ((gBusy[g2] >> s1) & 1ULL)) return false;
        if (p2 != p1 && ((pBusy[p2] >> s1) & 1ULL)) return false;

        // Place e1 into s2 (after removing e2)
        if (g1 != g2 && ((gBusy[g1] >> s2) & 1ULL)) return false;
        if (p1 != p2 && ((pBusy[p1] >> s2) & 1ULL)) return false;

        return true;
    }

    inline void apply_swap(int e1, int e2, int delta) {
        int s1 = slotOf[e1], s2 = slotOf[e2];
        auto [g1,p1] = edge[e1];
        auto [g2,p2] = edge[e2];

        int d1 = s1/7, l1 = s1%7;
        int d2 = s2/7, l2 = s2%7;
        uint8_t b1 = (uint8_t)(1u<<l1);
        uint8_t b2 = (uint8_t)(1u<<l2);

        // swap in slotEdges vectors
        int pos1 = posInSlot[e1];
        int pos2 = posInSlot[e2];
        slotEdges[s1][pos1] = e2; posInSlot[e2] = pos1;
        slotEdges[s2][pos2] = e1; posInSlot[e1] = pos2;
        slotOf[e1] = s2;
        slotOf[e2] = s1;

        // busy masks
        if (g1 != g2) {
            gBusy[g1] &= ~(1ULL<<s1); gBusy[g1] |= (1ULL<<s2);
            gBusy[g2] &= ~(1ULL<<s2); gBusy[g2] |= (1ULL<<s1);
        }
        if (p1 != p2) {
            pBusy[p1] &= ~(1ULL<<s1); pBusy[p1] |= (1ULL<<s2);
            pBusy[p2] &= ~(1ULL<<s2); pBusy[p2] |= (1ULL<<s1);
        }

        // day masks
        if (g1 != g2) {
            // g1: (d1,l1) -> (d2,l2)
            gDay[g1][d1] = (uint8_t)(gDay[g1][d1] & ~b1);
            gDay[g1][d2] = (uint8_t)(gDay[g1][d2] | b2);
            // g2: (d2,l2) -> (d1,l1)
            gDay[g2][d2] = (uint8_t)(gDay[g2][d2] & ~b2);
            gDay[g2][d1] = (uint8_t)(gDay[g2][d1] | b1);
        }

        if (p1 != p2) {
            pDay[p1][d1] = (uint8_t)(pDay[p1][d1] & ~b1);
            pDay[p1][d2] = (uint8_t)(pDay[p1][d2] | b2);

            pDay[p2][d2] = (uint8_t)(pDay[p2][d2] & ~b2);
            pDay[p2][d1] = (uint8_t)(pDay[p2][d1] | b1);
        }

        f += delta;
    }

    bool build_greedy(const vector<int>& gTot, const vector<int>& pTot) {
        // order edges by (gTot+ pTot) desc, shuffle inside buckets
        vector<vector<int>> bucket(200);
        int maxS = 0;
        for (int i=0;i<E;i++) {
            auto [g,p] = edge[i];
            int s = gTot[g] + pTot[p];
            bucket[s].push_back(i);
            maxS = max(maxS, s);
        }
        vector<int> order;
        order.reserve(E);
        for (int s=maxS;s>=0;s--) {
            auto &b = bucket[s];
            for (int i=(int)b.size()-1;i>0;i--) swap(b[i], b[rng_int(i+1)]);
            for (int x: b) order.push_back(x);
        }

        for (int ei: order) {
            auto [g,p] = edge[ei];
            int bestSlot = -1;
            int bestDelta = INT_MAX;

            // scan all 42 slots
            for (int s=0;s<42;s++) {
                if ((int)slotEdges[s].size() >= a) continue;
                if ((gBusy[g] >> s) & 1ULL) continue;
                if ((pBusy[p] >> s) & 1ULL) continue;

                int dlt = delta_add(g,p,s);
                if (dlt < bestDelta) {
                    bestDelta = dlt;
                    bestSlot = s;
                } else if (dlt == bestDelta && bestSlot != -1) {
                    if (s < bestSlot) bestSlot = s;
                }
            }
            if (bestSlot == -1) return false;

            int d = bestSlot/7, l = bestSlot%7;
            uint8_t bit = (uint8_t)(1u<<l);

            slotOf[ei] = bestSlot;
            add_to_slot(ei, bestSlot);
            gBusy[g] |= (1ULL<<bestSlot);
            pBusy[p] |= (1ULL<<bestSlot);
            gDay[g][d] = (uint8_t)(gDay[g][d] | bit);
            pDay[p][d] = (uint8_t)(pDay[p][d] | bit);
            f += bestDelta;
        }
        return true;
    }

    void anneal_until(chrono::steady_clock::time_point deadline) {
        auto start = chrono::steady_clock::now();
        double T0 = 50.0, T1 = 0.2;

        uint64_t it = 0;
        while (true) {
            if ((it & 4095ULL) == 0) {
                auto now = chrono::steady_clock::now();
                if (now >= deadline) break;
            }
            it++;

            double progress = 0.0;
            if ((it & 8191ULL) == 0) {
                auto now = chrono::steady_clock::now();
                double total = chrono::duration<double>(deadline - start).count();
                double used  = chrono::duration<double>(now - start).count();
                if (total > 1e-9) progress = min(1.0, max(0.0, used / total));
            }
            double T = T0 * (1.0 - progress) + T1 * progress;

            if (E == 0) continue;

            // choose op
            double r = rng_double();
            if (r < 0.72) {
                // move
                int ei = rng_int(E);
                int s1 = slotOf[ei];
                auto [g,p] = edge[ei];

                int bestS = -1;
                int bestD = INT_MAX;

                // sample K candidates
                const int K = 14;
                for (int k=0;k<K;k++) {
                    int s2 = rng_int(42);
                    if (s2 == s1) continue;
                    if ((int)slotEdges[s2].size() >= a) continue;
                    if ((gBusy[g] >> s2) & 1ULL) continue;
                    if ((pBusy[p] >> s2) & 1ULL) continue;

                    int dlt = delta_move(g,p,s1,s2);
                    if (dlt < bestD) {
                        bestD = dlt;
                        bestS = s2;
                    }
                }
                if (bestS == -1) continue;

                if (bestD <= 0 || rng_double() < exp(-bestD / max(1e-9, T))) {
                    apply_move(ei, bestS, bestD);
                }
            } else {
                // swap
                int e1 = rng_int(E);
                int e2 = rng_int(E);
                if (e1 == e2) continue;
                if (!can_swap(e1,e2)) continue;

                int dlt = delta_swap(e1,e2);
                if (dlt <= 0 || rng_double() < exp(-dlt / max(1e-9, T))) {
                    apply_swap(e1,e2,dlt);
                }
            }
        }
    }
};

static State build_from_slots(int n, int m, int a, const vector<pair<int,int>>& edges, const vector<int>& slots) {
    State st;
    st.init(n,m,a,edges);
    st.slotOf = slots;
    st.slotEdges.assign(42, {});
    st.posInSlot.assign((int)edges.size(), -1);
    st.gBusy.assign(n,0);
    st.pBusy.assign(m,0);
    st.gDay.assign(n, {});
    st.pDay.assign(m, {});
    for (int i=0;i<n;i++) for (int d=0;d<6;d++) st.gDay[i][d]=0;
    for (int j=0;j<m;j++) for (int d=0;d<6;d++) st.pDay[j][d]=0;

    for (int ei=0; ei<(int)edges.size(); ei++) {
        int s = slots[ei];
        auto [g,p] = edges[ei];
        int d = s/7, l = s%7;
        uint8_t bit = (uint8_t)(1u<<l);

        st.add_to_slot(ei, s);
        st.gBusy[g] |= (1ULL<<s);
        st.pBusy[p] |= (1ULL<<s);
        st.gDay[g][d] = (uint8_t)(st.gDay[g][d] | bit);
        st.pDay[p][d] = (uint8_t)(st.pDay[p][d] | bit);
    }

    int f = 0;
    for (int g=0; g<n; g++) for (int d=0; d<6; d++) f += contrib(st.gDay[g][d]);
    for (int p=0; p<m; p++) for (int d=0; d<6; d++) f += contrib(st.pDay[p][d]);
    st.f = f;
    return st;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a;
    cin >> n >> m >> a;

    vector<vector<int>> c(n, vector<int>(m));
    vector<int> gTot(n,0), pTot(m,0);
    long long E = 0;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            cin >> c[i][j];
            gTot[i] += c[i][j];
            pTot[j] += c[i][j];
            E += c[i][j];
        }
    }

    vector<pair<int,int>> edges;
    edges.reserve((size_t)E);
    for (int i=0;i<n;i++) for (int j=0;j<m;j++) {
        for (int k=0;k<c[i][j];k++) edges.push_back({i,j});
    }

    auto globalStart = chrono::steady_clock::now();
    auto deadline = globalStart + chrono::milliseconds(9500);

    vector<int> bestSlots;
    int bestF = INT_MAX;

    // few random starts
    for (int attempt=0; attempt<5; attempt++) {
        State st;
        st.init(n,m,a,edges);

        // shuffle edges order by shuffling underlying edge list for this attempt
        // (keep degrees same, just permute instances)
        for (int i=st.E-1;i>0;i--) swap(st.edge[i], st.edge[rng_int(i+1)]);

        if (!st.build_greedy(gTot, pTot)) continue;

        auto now = chrono::steady_clock::now();
        auto sub = min(deadline, now + chrono::milliseconds(700));
        st.anneal_until(sub);

        if (st.f < bestF) {
            bestF = st.f;
            bestSlots = st.slotOf;
        }

        if (chrono::steady_clock::now() >= deadline) break;
    }

    if (bestSlots.empty()) {
        // fallback: deterministic simple build (should be rare)
        State st;
        st.init(n,m,a,edges);
        st.build_greedy(gTot, pTot);
        bestF = st.f;
        bestSlots = st.slotOf;
    }

    // final long anneal from best
    State best = build_from_slots(n,m,a,edges,bestSlots);
    best.anneal_until(deadline);
    bestF = best.f;
    bestSlots = best.slotOf;

    // build output schedule matrix: for each group, day(0..5), lesson(0..6) -> professor+1
    vector<vector<array<int,7>>> out(n, vector<array<int,7>>(6));
    for (int g=0; g<n; g++) for (int d=0; d<6; d++) for (int l=0; l<7; l++) out[g][d][l] = 0;

    for (int ei=0; ei<(int)edges.size(); ei++) {
        auto [g,p] = edges[ei];
        int s = bestSlots[ei];
        int d = s/7, l = s%7;
        out[g][d][l] = p + 1;
    }

    cout << bestF << "\n\n";
    for (int g=0; g<n; g++) {
        for (int l=0; l<7; l++) {
            for (int d=0; d<6; d++) {
                if (d) cout << ' ';
                cout << out[g][d][l];
            }
            cout << "\n";
        }
        if (g+1 < n) cout << "\n";
    }
    return 0;
}
