#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
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

vector<vector<ll>> g;
vector<ll> jump, pr;
vector<ll> tin, tout;
vector<ll> h;
ll t = 0;

void dfs(ll v, ll p) {
    pr[v] = p;
    h[v] = h[p] + 1;
    tin[v] = t++;
    if (h[jump[p]] - h[jump[jump[p]]] == h[p] - h[jump[p]]) {
        jump[v] = jump[jump[p]];
    } else {
        jump[v] = p;
    }
    for (auto u : g[v]) {
        dfs(u, v);
    }
    tout[v] = t;
}

bool isanc(ll v, ll u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

ll lca(ll v, ll u) {
    while (true) {
        if (!isanc(jump[v], u)) {
            v = jump[v];
        } else if (!isanc(pr[v], u)) {
            v = pr[v];
        } else {
            break;
        }
    }
    if (!isanc(v, u)) v = pr[v];
    return v;
}

void viperr() {
    ll n, m;
    cin >> n >> m;
    g.resize(n);
    jump.resize(n);
    pr.resize(n);
    tin.resize(n);
    tout.resize(n);
    h.resize(n);
    for (ll i = 0; i < n - 1; i++) {
        ll x;
        cin >> x;
        g[x].push_back(i + 1);
    }
    dfs(0, 0);
    for (ll i = 0; i < m; i++) {
        ll v, u;
        cin >> v >> u;
        cout << lca(v, u) << '\n';
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
