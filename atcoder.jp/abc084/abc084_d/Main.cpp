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
#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

vector<int> sieveOfEratosthenes(int n) {
	vector<int> primes(n + 1);
	for (int i = 2; i <= n; ++i)
		primes[i] = i;
	for (int i = 2; i * i <= n; ++i)
		if (primes[i])
			for (int j = i * i; j <= n; j += i)
				primes[j] = 0;
	return primes;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int Q;
	cin >> Q;
	vector<int> l(Q);
	vector<int> r(Q);
	int r_max = -1;
	for (int i = 0; i < Q; i++) {
		cin >> l[i] >> r[i];
		if (r[i] > r_max) {
			r_max = r[i];
		}
	}

	auto primes = sieveOfEratosthenes(r_max);

	vector<int> cum(r_max + 1, 0);
	for (int i = 1; i <= r_max; i++) {
		cum[i] = cum[i - 1];
		if (i % 2 == 0) {
			continue;
		}

		if (primes[i] > 0 && primes[(i + 1) / 2] > 0) {
			cum[i]++;
		}
	}
	for (int i = 0; i < Q; i++) {
		if (primes[l[i]] > 0 && primes[(l[i] + 1) / 2] > 0) {
			cout << (cum[r[i]] - cum[l[i]] + 1) << endl;
		} else {
			cout << (cum[r[i]] - cum[l[i]]) << endl;
		}
	}

	return 0;
}
