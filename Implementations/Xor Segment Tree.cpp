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

struct SegmentTree {
    vector<ll> t;
    vector<ll> a, add;

    SegmentTree(vector<ll> b) {
        a = b;
        t.resize(2 * a.size());
        add.assign(2 * a.size(), -1);
        build(0, 0, a.size());
    }

    void push(ll v, ll l, ll r) {
        if (add[v] == -1) return;
        ll m = (r + l) / 2;
        t[lv(v)] = add[v] * (ll) (m - l);
        t[rv(v)] = add[v] * (ll) (r - m);
        add[lv(v)] = add[v];
        add[rv(v)] = add[v];
        add[v] = -1;
    }

    void build(ll v, ll l, ll r) {
        if (r - l == 1) {
            t[v] = a[l];
            return;
        }
        ll m = (r + l) / 2;
        build(lv(v), l, m);
        build(rv(v), m, r);
        t[v] = t[lv(v)] + t[rv(v)];
    }

    ll get(ll v, ll l, ll r, ll ql, ll qr, ll k, ll h) {
        if (ql >= r || qr <= l) return 0;
        if (ql <= l && r <= qr) return t[v];
        ll m = (r + l) / 2;
        push(v, l, r);
        if ((k >> h) & 1) {
            return get(rv(v), l, m, ql, qr, k, h - 1) + get(lv(v), m, r, ql, qr, k, h - 1);
        } else {
            return get(lv(v), l, m, ql, qr, k, h - 1) + get(rv(v), m, r, ql, qr, k, h - 1);
        }
    }

    void update(ll v, ll l, ll r, ll ql, ll qr, ll x, ll k, ll h) {
        if (ql >= r || qr <= l) return;
        if (ql <= l && r <= qr) {
            t[v] = x * (r - l);
            add[v] = x;
            return;
        }
        ll m = (r + l) / 2;
        push(v, l, r);
        if ((k >> h) & 1) {
            update(rv(v), l, m, ql, qr, x, k, h - 1);
            update(lv(v), m, r, ql, qr, x, k, h - 1);
        } else {
            update(lv(v), l, m, ql, qr, x, k, h - 1);
            update(rv(v), m, r, ql, qr, x, k, h - 1);
        }
        t[v] = t[lv(v)] + t[rv(v)];
    }
};

void viperr() {
    ll n;
    cin >> n;
    ll h = n;
    n = 1 << n;
    vector<ll> a(n);
    cin >> a;
    ll q;
    cin >> q;
    SegmentTree tree(a);
    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r, k, x;
            cin >> l >> r >> k >> x;
            tree.update(0, 0, n, l, r + 1, x, k, h - 1);
        } else {
            ll l, r, k;
            cin >> l >> r >> k;
            cout << tree.get(0, 0, n, l, r + 1, k, h - 1) << '\n';
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
