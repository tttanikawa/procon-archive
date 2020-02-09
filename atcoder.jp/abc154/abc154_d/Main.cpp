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

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, K;
	cin >> N >> K;

	auto p = table(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> p[i];
	}

	auto e = table(N, 0.0);
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= p[i]; j++) {
			e[i] += (double)j / p[i];
		}
	}

	auto cum = table(N + 1, 0.0);
	for (int i = 0; i < N; i++) {
		cum[i + 1] = cum[i] + e[i];
	}

	double emax = -1;
	for (int i = K; i <= N; i++) {
		chmax(emax, cum[i] - cum[i - K]);
	}

	cout << emax << endl;
	return 0;
}
