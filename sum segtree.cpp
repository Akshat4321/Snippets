//https://cses.fi/problemset/task/1648/
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

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());


struct SEGTREE{
    vector<int> seg;
    int n;
    SEGTREE(int n) : n(n), seg(4 * n, 0){} 

    void build(vector<int> &a , int l , int r , int pos){
        if (l==r){
            seg[pos] = a[l];
            return;
        }
        int mid = (l+r)/2;
        build(a , l , mid , 2*pos);
        build(a , mid+1 , r , 2*pos +1);
        seg[pos] = (seg[2*pos] + seg[2*pos+1]); //change
    }
    void build(vector<int> &a){
        build(a , 1 , n , 1);
    }

    void update(int id , int val , int l , int r , int pos){
        if (l==r){
            seg[pos] = val;
            return;
        }
        int mid = (l+r)/2;
        if (id<=mid){
            update(id, val, l, mid, 2 * pos);
        }
        else{
            update(id, val, mid + 1, r, 2 * pos + 1);
        }
        seg[pos] = (seg[pos*2] + seg[2*pos +1]); //change
    }
    void update(int id , int val){
        update(id, val, 1, n, 1);
    }

    int query(int ql , int qr , int l , int r , int pos){
        //ql and qr are given query
        if (qr<l || r < ql) return 0; //change
        if (ql<=l && r<=qr) return seg[pos];
        int mid = (l+r)/2;
        int ans1 = query(ql, qr, l, mid, 2 * pos);
        int ans2 = query(ql, qr, mid + 1, r, 2 * pos + 1);
        return (ans1 + ans2); //change
    }
    int query(int ql , int qr){
        return query(ql, qr, 1, n, 1);
    }

};

void Solve() {
    int n; cin>>n;
    int q; cin>>q;
    vi a(n+1);
    rep(i,1,n+1){
        cin>>a[i];
    }
    SEGTREE segtree(n);
    segtree.build(a , 1 , n , 1);
    while (q--){
        int type; cin>>type;
        if (type==1){
            int id , val ; cin>>id>>val;
            segtree.update(id,val);
        }
        else{
            int l ,r; cin>>l>>r;
            cout<<segtree.query(l,r)<<endl;
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
