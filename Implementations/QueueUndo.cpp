#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <immintrin.h>

#ifndef DEBUG
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#endif

using namespace __gnu_pbds;
using namespace __gnu_cxx;
using namespace std;

using ld = long double;
using ll = long long;
using i128 = __int128;
using ull = unsigned long long;
using pll = std::pair<ll, ll>;
using cmpl = std::complex<ld>;
template<typename T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr ll MOD = 998244353;
constexpr ll MOD1 = 1000000007;
constexpr ll INV2 = 499122177;
constexpr ld PI = 3.141592653589793;
const ld eps = 1e-7;
const ll K = 500;
const ll C = 200;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

ld START_TIME = clock();

struct DSU {
    std::vector<ll> pr, rnk;
    std::vector<std::pair<pll, pll>> otk;
    std::vector<ll> otk1;
    ll cmps = 0;

    void resize(ll n) {
        cmps = n;
        pr.resize(n, -1);
        rnk.resize(n, 1);
    }

    ll get(ll v) {
        if (pr[v] == -1) {
            return v;
        }
        return get(pr[v]);
    }

    void unite(ll v, ll u) {
        v = get(v), u = get(u);
        otk1.push_back(cmps);
        if (v == u) {
            otk.push_back({{-1, -1},
                           {-1, -1}});
            return;
        }
        if (rnk[v] > rnk[u]) {
            std::swap(v, u);
        }
        otk.push_back({{v, pr[v]},
                       {u, rnk[u]}});
        --cmps;
        pr[v] = u;
        rnk[u] += rnk[v];
    }

    void otkat() {
        if (otk.back().first.first == -1) {
            cmps = otk1.back();
            otk.pop_back();
            otk1.pop_back();
            return;
        }
        pr[otk.back().first.first] = otk.back().first.second;
        rnk[otk.back().second.first] = otk.back().second.second;
        cmps = otk1.back();
        otk.pop_back();
        otk1.pop_back();
    }

    void otkat(ll k) {
        for (int op = 0; op < k; ++op) {
            otkat();
        }
    }
};

struct EuphoriaTrick {
    DSU c;
    std::vector<std::pair<char, pll>> ops;
    ll cnta = 0, cntb = 0;

    void add(ll v, ll u) {
        ops.push_back({'A', {v, u}});
        ++cnta;
        c.unite(v, u);
    }

    void pop() {
        if (ops.back().first == 'B') {
            c.otkat();
            ops.pop_back();
            --cntb;
        } else {
            if (cntb == 0) {
                std::vector<std::pair<char, pll>> ops1;
                c.otkat(ops.size());
                for (int i = ops.size() - 1; i >= 0; --i) {
                    ops1.push_back({'B', ops[i].second});
                    c.unite(ops[i].second.first, ops[i].second.second);
                    --cnta;
                    ++cntb;
                }
                ops = ops1;
            } else {
                ll cnttb = 0, cntta = 0;
                ll j = ops.size() - 1;
                for (; j > 0; --j) {
                    cnttb += ops[j].first == 'B';
                    cntta += ops[j].first == 'A';
                    if (cnttb > cntta) {
                        break;
                    }
                }
                std::vector<std::pair<char, pll>> dxx;
                for (int i = j; i < ops.size(); ++i) {
                    if (ops[i].first == 'A') {
                        dxx.push_back(ops[i]);
                    }
                }
                for (int i = j; i < ops.size(); ++i) {
                    if (ops[i].first == 'B') {
                        dxx.push_back(ops[i]);
                    }
                }
                c.otkat(ll(ops.size()) - j);
                while (ops.size() > j) {
                    ops.pop_back();
                }
                for (int i = 0; i < dxx.size(); ++i) {
                    ops.push_back(dxx[i]);
                    c.unite(dxx[i].second.first, dxx[i].second.second);
                }
            }
            pop();
        }
    }
};

void solve() {
    ll n, m;
    std::cin >> n >> m;
    std::vector<pll> edgs(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edgs[i].first >> edgs[i].second;
        --edgs[i].first, --edgs[i].second;
    }
    ll ans = 0;
    EuphoriaTrick dd;
    dd.c.resize(n);
    ll r = 0;
    for (int i = 0; i < m; ++i) {
        while (r < m && dd.c.cmps > 1) {
            dd.add(edgs[r].first, edgs[r].second);
            ++r;
        }
        if (dd.c.cmps > 1) {
            break;
        }
        ans += m - r + 1;
        dd.pop();
    }
    std::cout << ans;
}

signed main() {
#ifdef DEBUG
    std::freopen("/home/anton/CLionProjects/untitled/input.txt", "r", stdin);
#else
    //    std::freopen("tri.in", "r", stdin); std::freopen("tri.out", "w", stdout);
#endif
    std::cin.tie(nullptr)->std::ios_base::sync_with_stdio(false);
    int tt = 1;
    //    ll g; std::cin >> g;
//    std::cin >> tt;
    while (tt--) {
        solve();
    }
#ifdef DEBUG
    std::cerr << '\n';
    ld TIME = (clock() - START_TIME) / CLOCKS_PER_SEC;
    std::cerr << "Time: " << TIME << '\n';
#endif
}
