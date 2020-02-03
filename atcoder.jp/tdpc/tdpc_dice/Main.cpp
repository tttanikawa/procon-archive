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

vector<pair<ll, ll>> primeFactor(ll n) {
	vector<pair<ll, ll>> res;
	for (ll p = 2; p * p <= n; p++) {
		ll tmp = 0;
		while (n % p == 0) {
			n /= p;
			tmp++;
		}
		if (tmp != 0)
			res.push_back(make_pair(p, tmp));
	}
	if (n != 1)
		res.push_back(make_pair(n, 1));
	return res;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	ll D;
	cin >> N >> D;

	auto pf = primeFactor(D);
	int count[7] = {0};
	for (auto &&i : pf) {
		auto f = i.first;
		auto n = i.second;
		if (f > 5) {
			cout << 0.0 << endl;
			return 0;
		} else {
			count[f] = n;
		}
	}
	constexpr int dx[6] = {0, 1, 0, 2, 0, 1};
	constexpr int dy[6] = {0, 0, 1, 0, 0, 1};
	constexpr int dz[6] = {0, 0, 0, 0, 1, 0};

	auto dp = table(count[2] + 1, count[3] + 1, count[5] + 1, 0.0);
	dp[0][0][0] = 1.0;
	for (int i = 0; i < N; i++) {
		auto nxt = table(count[2] + 1, count[3] + 1, count[5] + 1, 0.0);
		for (int j = 0; j <= count[2]; j++) {
			for (int k = 0; k <= count[3]; k++) {
				for (int l = 0; l <= count[5]; l++) {
					for (int m = 0; m < 6; m++) {
						const int nx = min(count[2], j + dx[m]);
						const int ny = min(count[3], k + dy[m]);
						const int nz = min(count[5], l + dz[m]);
						nxt[nx][ny][nz] += dp[j][k][l] / 6;
					}
				}
			}
		}
		dp = move(nxt);
	}
	cout << dp[count[2]][count[3]][count[5]] << endl;
	return 0;
}
