//range update query

#include <bits/stdc++.h>

using namespace std;
#define int long long
#define INF (int)1e18
#define endl '\n'
const int mod = 1000 * 1000 * 1000 + 7;
const int N = 100005;
#define f first
#define s second
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define rrep(i, a, b) for(int i = (a); i > (b); i--)
#define vi vector<int>
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()

#ifndef ONLINE_JUDGE

#include "template.cpp"

#else
#define debug(...)
#define debugArr(...)
#endif

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

/*

*/



struct SEGTREE {
    vector<int> seg, lazyseg;
    int n;

    SEGTREE(int n) : n(n), seg(4 * n, 0), lazyseg(4 * n, 0) {} // Lazy array should be 4*N, not 8*N

    void build(vector<int>& a, int l, int r, int pos) {
        if (l == r) {
            seg[pos] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, l, mid, 2 * pos);
        build(a, mid + 1, r, 2 * pos + 1);
        seg[pos] = max(seg[2 * pos], seg[2 * pos + 1]); // Correctly updating max
    }

    void build(vector<int>& a) {
        build(a, 1, n, 1);
    }

    void propagate(int l, int r, int pos) {
        if (lazyseg[pos] != 0) {
            seg[pos] += lazyseg[pos];  // Add lazy value directly (no range multiplication)
            if (l != r) {  // If not a leaf node
                lazyseg[2 * pos] += lazyseg[pos];       // Propagate to left child
                lazyseg[2 * pos + 1] += lazyseg[pos];   // Propagate to right child
            }
            lazyseg[pos] = 0; // Clear the lazy value
        }
    }

    void update(int ql, int qr, int l, int r, int val, int pos) {
        propagate(l, r, pos); // Apply any pending lazy updates
        if (r < ql || qr < l) {
            return; // No overlap
        }
        if (ql <= l && r <= qr) { // Complete overlap
            seg[pos] += val;  // Apply the value directly (not multiplying by range)
            if (l != r) {  // If not a leaf node, propagate lazily to children
                lazyseg[2 * pos] += val;
                lazyseg[2 * pos + 1] += val;
            }
            return;
        }
        // Partial overlap, recursively update both sides
        int mid = (l + r) / 2;
        update(ql, qr, l, mid, val, 2 * pos);
        update(ql, qr, mid + 1, r, val, 2 * pos + 1);
        seg[pos] = max(seg[2 * pos], seg[2 * pos + 1]); // Recalculate the maximum after update
    }

    void update(int ql, int qr, int val) {
        update(ql, qr, 1, n, val, 1);
    }

    int query(int ql, int qr, int l, int r, int pos) {
        propagate(l, r, pos); // Apply any pending lazy updates
        if (qr < l || r < ql) return -INF; // No overlap, return a negative infinity for max query
        if (ql <= l && r <= qr) return seg[pos]; // Complete overlap
        // Partial overlap, query both sides
        int mid = (l + r) / 2;
        int ans1 = query(ql, qr, l, mid, 2 * pos);
        int ans2 = query(ql, qr, mid + 1, r, 2 * pos + 1);
        return max(ans1, ans2); // Return maximum of the two halves
    }

    int query(int ql, int qr) {
        return query(ql, qr, 1, n, 1);
    }
};

void Solve() {
    int n ;
    cin>>n;
    vi a(n+1);
    for(int i = 1 ; i<= n ; i++){
        cin>>a[i];
    }

    SEGTREE segtree(n);
    segtree.build(a);

    int m;
    cin>>m;

    while(m--){
        char c;
        cin>>c;
        if (c=='m'){
            int ql , qr;
            cin>>ql>>qr;
            cout<<segtree.query(ql,qr)<<endl;
        }
        else{
            int ql , qr , val;
            cin>>ql>>qr>>val;
            segtree.update(ql,qr,val);
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
