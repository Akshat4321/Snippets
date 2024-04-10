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
