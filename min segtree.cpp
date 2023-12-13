
struct segtree{
    vector<int> seg;
    int n;
    segtree(int siz) : seg(4*siz,1e18){
        n = siz;
    }
    void build(vector<int> &a , int l , int r , int pos){
        if (l==r){
            seg[pos] = a[l];
            return;
        }
        int mid = (l+r)/2;
        build(a , l , mid , 2*pos);
        build(a , mid+1 , r , 2*pos +1);
        seg[pos] = min(seg[2*pos] , seg[2*pos+1]);
    }
    void build(vector<int> &a){
        build(a , 1 , n , 1);
    }

    void set(int id ,int val , int l , int r , int pos){
        if (l==r){
            seg[pos] = val;
            return;
        }
        int mid = (l+r)/2;
        if (id<=mid){
            set(id, val , l , mid , 2*pos);
        }
        else{
            set(id , val , mid+1 , r , 2*pos +1);
        }
        seg[pos] = min(seg[pos*2] , seg[2*pos +1]);
    }
    void set(int id , int val){
        set(id , val  , 1 ,n , 1);
    }

    int calc(int ql , int qr , int l , int r , int pos){
        //ql and qr are given query
        if (qr<l || r < ql) return LONG_LONG_MAX;
        if (ql<=l && r<=qr) return seg[pos];
        int mid = (l+r)/2;
        int ans1 = calc(ql , qr ,l , mid , 2*pos);
        int ans2 = calc(ql , qr , mid+1 , r , 2*pos +1);
        return min(ans1,ans2);
    }
    int calc(int ql , int qr){
        return calc(ql , qr , 1 , n , 1);
    }

};
