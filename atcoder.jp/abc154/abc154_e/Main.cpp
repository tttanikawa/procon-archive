#include <algorithm>
#include <array>
#include <cassert>
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
#include <numeric>
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

template <typename T>
constexpr T INF = numeric_limits<T>::max();

template <class T>
constexpr T PI = static_cast<T>(3.14159265358979323846);

constexpr int MOD = 1e9 + 7;

template <class T>
bool chmin(T &a, T b) {
	if (a > b) {
		a = b;
		return true;
	}
	return false;
}

template <class T>
bool chmax(T &a, T b) {
	if (a < b) {
		a = b;
		return true;
	}
	return false;
}

template <typename T>
std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }

template <class... Args>
auto table(int n, Args... args) {
	auto val = table(args...);
	return std::vector<decltype(val)>(n, std::move(val));
}

// 組み合わせを列挙
void recursive_comb(int *indexes, int s, int rest, std::function<void(int *)> f) {
	if (rest == 0) {
		f(indexes);
	} else {
		if (s < 0)
			return;
		recursive_comb(indexes, s - 1, rest, f);
		indexes[rest - 1] = s;
		recursive_comb(indexes, s - 1, rest - 1, f);
	}
}
// nCkの組み合わせに対して処理を実行する
void foreach_comb(int n, int k, std::function<void(int *)> f) {
	int indexes[k];
	recursive_comb(indexes, n - 1, k, f);
}

long long comb(long long N, long long R) {
	if (R < 0 || R > N)
		return 0;
	if (R == 1)
		return N;
	else if (R == 2)
		return N * (N - 1) / 2;
	else
		return N * (N - 1) * (N - 2) / 6;
}

ll pow(ll x, ll n) {
	ll ans = 1;
	while (n > 0) {
		if ((n & 1) == 1) {
			ans = ans * x;
		}
		x = x * x;
		n = (n >> 1);
	}
	return ans;
}

/*
ll rec(string &N, int K, int indexes[], int i, bool b) {
	if (i >= K) {
		return 1;
	}

	int d = N[indexes[i]] - '0';
	ll ret = 0;
	if (b) {
		if (d != 0) {
			ret += (d - 1) * rec(N, K, indexes, i + 1, false);
			ret += rec(N, K, indexes, i + 1, true);
		} else {
			return 0;
		}
	} else {
		ret += 9 * rec(N, K, indexes, i + 1, false);
	}
	return ret;
}
*/

ll rec(string &N, int i, int k, bool smaller) {
	if (k == 0) {
		return 1;
	}
	if (i >= N.size()) {
		return 0;
	}

	if (smaller) {
		return comb(N.size() - i, k) * pow(9, k);
	}

	if (N[i] == '0') {
		return rec(N, i + 1, k, false);
	}

	ll a = rec(N, i + 1, k, true);
	ll b = (N[i] - '0' - 1) * rec(N, i + 1, k - 1, true);
	ll c = rec(N, i + 1, k - 1, false);
	return a + b + c;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	string N;
	int K;
	cin >> N >> K;

	ll ans = 0;
	/*
	foreach_comb(N.size(), K, [&](int indexes[]) {
		if (indexes[0] == 0) {
			ans += rec(N, K, indexes, 0, true);
		} else {
			ans += rec(N, K, indexes, 0, false);
		}
	});
	*/

	cout << rec(N, 0, K, false) << endl;
	return 0;
}
