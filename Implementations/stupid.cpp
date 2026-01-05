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

#define lv(v) v + 1
#define rv(v) v + 2 * (m - l)

ld START_TIME = clock();

std::vector<ll> a, b;

ll w(ll j, ll i){
    return b[j] * a[i];
}

void solve() {
    ll n;
    std::cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    std::vector<ll> dp(n);
    dp[0] = 0;
    std::deque<pll> k = {{1, 0}};
    for (int j = 1; j < n; ++j) {
        dp[j] = dp[k.front().second] + w(k.front().second, j);
        if (j == n - 1) break;
        ++k.front().first;
        if (k.size() > 1 && k[0].first == k[1].first){
            k.pop_front();
        }
        while (!k.empty() && dp[k.back().second] + w(k.back().second, k.back().first) >= dp[j] + w(j, k.back().first)){
            k.pop_back();
        }
        if (k.empty()){
            k.push_back({j + 1, j});
        }
        else if (dp[k.back().second] + w(k.back().second, n - 1) >= dp[j] + w(j, n - 1)){
            ll l = k.back().first, r = n - 1;
            while (r - l > 1){
                ll m = (l + r) / 2;
                if (dp[k.back().second] + w(k.back().second, m) >= dp[j] + w(j, m)){
                    r = m;
                }
                else{
                    l = m;
                }
            }
            k.push_back({r, j});
        }
    }
    std::cout << dp[n - 1];
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