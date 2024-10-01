//https://cses.fi/problemset/task/1651/


#include <bits/stdc++.h>
 
using namespace std;
#define int long long
#define INF (int)1e18
#define endl '\n'
const int mod = 1000 * 1000 * 1000 + 7;
const int N = 200005;
#define f first
#define s second
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define rrep(i, a, b) for(int i = (a); i > (b); i--)
#define vi vector<int>
#define pii pair<int, int>
 
mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
 
struct SEGTREE {
    vector<int> seg, lazyseg;
    int n;
 
    SEGTREE(int n) : n(n), seg(4 * n, 0), lazyseg(8 * n, 0) {}
 
    void build(vector<int>& a, int l, int r, int pos) {
        if (l == r) {
            seg[pos] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, l, mid, 2 * pos);
        build(a, mid + 1, r, 2 * pos + 1);
        seg[pos] = seg[2 * pos] + seg[2 * pos + 1];
    }
 
    void build(vector<int>& a) {
        build(a, 1, n, 1);
    }
 
    void propagate(int l, int r, int pos) {
        if (lazyseg[pos] != 0) {
            seg[pos] += lazyseg[pos] * (r - l + 1);
            if (l != r) {
                lazyseg[2 * pos] += lazyseg[pos];
                lazyseg[2 * pos + 1] += lazyseg[pos];
            }
            lazyseg[pos] = 0;
        }
    }
 
    void update(int ql, int qr, int l, int r, int val, int pos) {
        propagate(l, r, pos);
        if (r < ql || qr < l) {
            return;
        }
        if (ql <= l && r <= qr) {
            seg[pos] += val * (r - l + 1);
            if (l != r) {
                lazyseg[2 * pos] += val;
                lazyseg[2 * pos + 1] += val;
            }
            return;
        }
        int mid = (l + r) / 2;
        update(ql, qr, l, mid, val, 2 * pos);
        update(ql, qr, mid + 1, r, val, 2 * pos + 1);
        seg[pos] = seg[2 * pos] + seg[2 * pos + 1];
    }
 
    void update(int ql, int qr, int val) {
        update(ql, qr, 1, n, val, 1);
    }
 
    int query(int id, int l, int r, int pos) {
        propagate(l, r, pos);
        if (l == r) {
            return seg[pos];
        }
        int mid = (l + r) / 2;
        if (id <= mid) {
            return query(id, l, mid, 2 * pos);
        } else {
            return query(id, mid + 1, r, 2 * pos + 1);
        }
    }
 
    int query(int id) {
        return query(id, 1, n, 1);
    }
};
 
 
void Solve() {
    int n, m; cin>>n>>m;
    vi a(n+1);
    rep(i , 1 , n+1){
        cin>>a[i];
    }
    SEGTREE segtree(n);
    segtree.build(a);
    while (m--){
        int k; cin>>k;
        if (k==1){
            int l , r; cin>>l>>r;
            int val; cin>>val;
            segtree.update(l,r,val);
        }
        else{
            int id; cin>>id;
            cout<<segtree.query(id)<<endl;
        }
    }
}
 
int32_t main() {
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
 
    int t = 1;
    //   cin >> t;
    for (int i = 1; i <= t; i++) {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    return 0;
}
