//problem https://cses.fi/problemset/task/1648
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
int n , q;
int tree[N];
 
void add(int k , int x){
    while (k<=n){
        tree[k] +=x;
        k += (k&-k);
    }
}
 
int query(int k){
    int s = 0;
    while (k>=1){
        s +=  tree[k];
        k -= k & -k;
    }
    return s;
}
 
void Solve() {
    cin>>n>>q;
    vi a(n+1);
    rep(i,1,n+1){
        cin>>a[i];
        add(i,a[i]);
    }
    while (q--){
        int op , a1 , a2; cin>>op>>a1>>a2;
        if (op==1){
            add(a1 , a2-a[a1]);
            a[a1] = a2;
        }
        else{
             cout<<query(a2) - query(a1-1)<<endl;
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
