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

#define lv(v) v + 1
#define rv(v) v + 2 * (m - l)

struct node {
    ll mid, x;
};

struct SegmentTree {
    vector<node> t;
    vector<ll> a, sz;

    SegmentTree() = default;

    SegmentTree(vector<ll> s, vector<ll> sz_) {
        if (s.empty()) return;
        a = s;
        sz = sz_;
        t.resize(2 * a.size());
        build(0, 0, a.size());
    }

    void build(ll v, ll l, ll r) {
        if (r - l == 1) {
            t[v] = {l, a[l]};
            return;
        }
        ll sum = 0, m = l, x = 0;
        for (ll i = l; i < r; i++) {
            sum += sz[i];
        }
        for (ll i = l; i < r; i++) {
            x += sz[i];
            if (x >= sum / 2) {
                m = i + 1;
                break;
            }
        }
        if (m == r) m--;
        t[v].mid = m;
        build(lv(v), l, m);
        build(rv(v), m, r);
        t[v].x = max(t[lv(v)].x, t[rv(v)].x);
    }

    ll get(ll v, ll l, ll r, ll ql, ll qr) {
        if (ql >= r || qr <= l) return -INF;
        if (ql <= l && r <= qr) return t[v].x;
        ll m = t[v].mid;
        return max(get(lv(v), l, m, ql, qr), get(rv(v), m, r, ql, qr));
    }

    void update(ll v, ll l, ll r, ll i, ll x) {
        if (r - l == 1) {
            t[v].x = x;
            return;
        }
        ll m = t[v].mid;
        if (i < m) {
            update(lv(v), l, m, i, x);
        } else {
            update(rv(v), m, r, i, x);
        }
        t[v].x = max(t[lv(v)].x, t[rv(v)].x);
    }

    ll get(ll l, ll r) {
        return get(0, 0, t.size() / 2, l, r);
    }

    void update(ll i, ll x) {
        update(0, 0, t.size() / 2, i, x);
    }
};

vector<vector<ll>> g, hv, hvs;
vector<ll> hd, sz, tin, tout, a, eu, hvid, ind, par, s;

void dfs(ll v, ll p) {
    par[v] = p;
    for (auto &u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sz[v] += sz[u];
            if (sz[g[v][0]] < sz[u]) swap(u, g[v][0]);
        }
    }
    sz[v] += 1;
    if (g[v].size()) s[v] = sz[v] - sz[g[v][0]];
    else s[v] = 1;
}

ll jh = 0;

void dfs1(ll v, ll p) {
    ind[v] = hv[hvid[v]].size();
    hv[hvid[v]].push_back(a[v]);
    hvs[hvid[v]].push_back(s[v]);
    tin[v] = eu.size();
    eu.push_back(a[v]);
    for (auto u : g[v]) {
        if (u != p) {
            if (u == g[v][0]) {
                hd[u] = hd[v];
                hvid[u] = hvid[v];
            } else {
                hd[u] = u;
                hvid[u] = ++jh;
            }
            dfs1(u, v);
        }
    }
    tout[v] = eu.size();
}

vector<SegmentTree> b;

bool isanc(ll v, ll u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

ll up(ll &v, ll &u) {
    ll res = 0;
    while (!isanc(hd[v], u)) {
        ll in = hvid[v];
        res = max(res, b[in].get(0, ind[v] + 1));
        v = par[hd[v]];
    }
    return res;
}

void viperr() {
    ll n;
    cin >> n;
    a.resize(n);
    hd.resize(n);
    sz.resize(n);
    tin.resize(n);
    tout.resize(n);
    g.resize(n);
    hvs.resize(n);
    hvid.resize(n);
    par.resize(n);
    ind.resize(n);
    b.resize(n);
    hv.resize(n);
    s.resize(n);
    cin >> a;
    for (ll i = 0; i < n - 1; i++) {
        ll v, u;
        cin >> v >> u;
        v--;
        u--;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    dfs(0, 0);
    dfs1(0, 0);
    for (ll i = 0; i < n; i++) {
        b[i] = {hv[i], hvs[i]};
    }
    ll q;
    cin >> q;
    while (q--) {
        char t;
        cin >> t;
        if (t == '?') {
            ll v, u;
            cin >> v >> u;
            v--;
            u--;
            ll res = up(v, u);
            res = max(res, up(u, v));
            if (ind[v] > ind[u]) swap(v, u);
            res = max(res, b[hvid[v]].get(ind[v], ind[u] + 1));
            cout << res << '\n';
        } else {
            ll v, x;
            cin >> v >> x;
            v--;
            b[hvid[v]].update(ind[v], x);
        }
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
