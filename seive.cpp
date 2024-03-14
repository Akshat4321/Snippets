const int M = 1e9 + 7;
const int N = 2e5;

vector<int> spf(N, -1);
for (int i = 2; i < N; i++) {
    if (spf[i] == -1) {
        for (int j = i; j < N; j += i) if (spf[j] == -1) spf[j] = i;
    }
}

int n = 20;
while (n > 1) {
    cout << spf[n] << ' ';
    n /= spf[n];
}
