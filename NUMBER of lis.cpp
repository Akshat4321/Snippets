https://codeforces.com/group/mlc657bZIV/contest/539165/problem/E
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

vector<pii> tree;

int RANKER(vi& arr) {
    int n = arr.size();
    vi temp = arr;
    sort(all(temp));

    unordered_map<int, int> rank;
    int mx = 0;

    rep(i, 0, n) {
        if (rank.find(temp[i]) == rank.end()) {
            rank[temp[i]] = mx++;
        }
    }

    rep(i, 0, n) {
        arr[i] = rank[arr[i]];
    }

    return mx;
}

pii chooseBest(pii& left, pii& right) {
    pii res;
    int mxLen_LFT = left.f;
    int ways_LFT = left.s;
    int mxLen_RHT = right.f;
    int ways_RHT = right.s;

    if (mxLen_LFT > mxLen_RHT) {
        res = {mxLen_LFT, ways_LFT};
    } else if (mxLen_LFT < mxLen_RHT) {
        res = {mxLen_RHT, ways_RHT};
    } else {
        res.f = mxLen_LFT;
        res.s = (ways_LFT + ways_RHT) % mod;
    }
    return res;
}

void update(int start, int end, int parent, int element, int mxLength, int ways) {
    if (start == end) {
        if (tree[parent].f == mxLength) {
            tree[parent].s = (tree[parent].s + ways) % mod;
        } else {
            tree[parent] = {mxLength, ways % mod};
        }
        return;
    }
    int mid = (start + end) / 2;

    if (element <= mid) {
        update(start, mid, 2 * parent + 1, element, mxLength, ways);
    } else {
        update(mid + 1, end, 2 * parent + 2, element, mxLength, ways);
    }

    tree[parent] = chooseBest(tree[2 * parent + 1], tree[2 * parent + 2]);
}

pii maxLen(int start, int end, int qstart, int qend, int parent) {
    if (start > qend || end < qstart) {
        return {0, 0};
    }
    if (start >= qstart && end <= qend) {
        return tree[parent];
    }
    int mid = (start + end) / 2;
    pii left = maxLen(start, mid, qstart, qend, 2 * parent + 1);
    pii right = maxLen(mid + 1, end, qstart, qend, 2 * parent + 2);
    return chooseBest(left, right);
}

pair<int,int> findNumberOfLIS(vi& arr) {
    int n = arr.size();
    int mx = RANKER(arr);

    tree.resize(4 * mx + 5);

    rep(i, 0, n) {
        int mxLen = 1;
        int ways = 1;

        if (arr[i] > 0) {
            pii info = maxLen(0, mx, 0, arr[i] - 1, 0);
            if (info.f + 1 > mxLen) {
                mxLen = info.f + 1;
                ways = info.s;
            }
        }

        update(0, mx, 0, arr[i], mxLen, ways);
    }
    return tree[0];
}

void Solve() {
    int n , m;
    cin>>n>>m;
    vi a(n);
    for (int i = 0; i < n; ++i) {
        cin>>a[i];
    }
    auto ans = findNumberOfLIS(a);
    cout<<ans.first<<endl;//lis
    if(m==1){
        cout<<ans.second<<endl; //numbers
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
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    return 0;
}
