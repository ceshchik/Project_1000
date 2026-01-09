#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = int;
using ull = unsigned long long;
using ld = long double;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T>
using pq = priority_queue<T, vector<T>>;
const ll INF = 1e9;
ll MOD = 1e9 + 7;
ll MAXn = 2e6;
ll lg = 22;
const ld ap = 1e-6;
const double pi = acos(-1);

template<class T>
istream &operator>>(istream &in, vector<T> &x) {
    for (auto &i : x) {
        in >> i;
    }
    return in;
}

template<class T>
ostream &operator<<(ostream &out, vector<T> &x) {
    for (auto &i : x) {
        out << i << ' ';
    }
    return out;
}

vector<vector<pair<ll, ll>>> g;
vector<ll> jump, mn, pr, a;
vector<ll> tin, tout;
vector<ll> h;
ll t = 0;

void dfs(ll v, ll w, ll p) {
    a[v] = w;
    pr[v] = p;
    h[v] = h[p] + 1;
    tin[v] = t++;
    if (h[jump[p]] - h[jump[jump[p]]] == h[p] - h[jump[p]]) {
        jump[v] = jump[jump[p]];
        mn[v] = min({w, mn[p], mn[jump[p]]});
    } else {
        jump[v] = p;
        mn[v] = min(w, a[p]);
    }
    for (auto [u, ww] : g[v]) {
        dfs(u, ww, v);
    }
    tout[v] = t;
}

bool isanc(ll v, ll u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

ll get(ll v, ll u) {
    ll ans = INF;
    if (!isanc(v, u)) ans = a[v];
    while (!isanc(v, u)) {
        if (!isanc(jump[v], u)) {
            ans = min(ans, mn[v]);
            v = jump[v];
        } else if (!isanc(pr[v], u)) {
            ans = min({ans, a[v], a[pr[v]]});
            v = pr[v];
        } else break;
    }
    return ans;
}

void viperr() {
    ll n;
    cin >> n;
    g.resize(n);
    tin.resize(n);
    tout.resize(n);
    jump.resize(n);
    mn.resize(n, INF);
    a.resize(n);
    pr.resize(n);
    h.resize(n);
    for (ll i = 1; i < n; i++) {
        ll v, w;
        cin >> v >> w;
        g[v - 1].emplace_back(i, w);
    }
    dfs(0, INF, 0);
    ll q;
    cin >> q;
    while (q--) {
        ll v, u;
        cin >> v >> u;
        cout << min(get(v - 1, u - 1), get(u - 1, v - 1)) << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t11 = 1;
//    cin >> t11;
    while (t11--) {
        viperr();
        cout << '\n';
    }
    return 0;
}
