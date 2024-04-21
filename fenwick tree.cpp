struct BIT {
	int size;
	vector<int> bit;
	BIT(int n) : size(n), bit(n + 1) {}
	void update(int x, int v) {
		for (; x <= size; x += x & (-x)) { bit[x] += v; }
	}
	/** @return sum of the values in [0,b] */
	int query(int b) {
		int result = 0;
		for (; b > 0; b -= b & (-b)) { result += bit[b]; }
		return result;
	}
};

void Solve() {
    cin>>n>>q;
    vi a(n+1);
    BIT fen(n);
    rep(i,1,n+1){
        cin>>a[i];
        update(i,a[i]);
    }
    while (q--){
        int op , a1 , a2; cin>>op>>a1>>a2;
        if (op==1){
            update(a1 , a2-a[a1]);
            a[a1] = a2;
        }
        else{
             cout<<query(a2) - query(a1-1)<<endl;
        }
    }
}

