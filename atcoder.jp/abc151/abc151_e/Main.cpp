#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using pint = pair<int, int>;
using pll = pair<ll, ll>;

constexpr double EPS = 1e-7;
constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

ll pow_mod(ll x, ll n) {
	ll ans = 1;
	while (n > 0) {
		if ((n & 1) == 1) {
			ans = ans * x % MOD;
		}
		x = x * x % MOD;
		n = (n >> 1);
	}
	return ans;
}

vector<ll> factrial;
vector<ll> inverse;
ll comb_fermat(int n, int k) {
	// 階乗とその逆元を計算
	factrial[0] = 1;
	inverse[0] = 1;
	for (int i = 1; i <= n; i++) {
		factrial[i] = factrial[i - 1] * i % MOD;
		inverse[i] = inverse[i - 1] * pow_mod(i, MOD - 2) % MOD;
	}
	return factrial[n] % MOD * inverse[k] % MOD * inverse[n - k] % MOD;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, K;
	cin >> N >> K;

	vector<int> A(N);
	for (auto &&i : A) {
		cin >> i;
	}

	sort(A.begin(), A.end());

	factrial.resize(N + 1);
	inverse.resize(N + 1);
	comb_fermat(N, K);

	ll sum_max = 0;
	for (int i = K - 1; i < N; i++) {
		sum_max += (ll)A[i] % MOD * factrial[i] % MOD * inverse[K - 1] % MOD * inverse[i - K + 1] % MOD;
		sum_max %= MOD;
	}
	// cout << sum_max << endl;
	ll sum_min = 0;
	for (int i = 0; i < N - K + 1; i++) {
		sum_min += (ll)A[i] % MOD * factrial[N - 1 - i] % MOD * inverse[K - 1] % MOD * inverse[N - K - i] % MOD;
		sum_min %= MOD;
	}
	// cout << sum_min << endl;
	ll ans = sum_max - sum_min;
	if(ans < 0) {
		ans += MOD;
	}
	cout << ans % MOD << endl;

	return 0;
}
