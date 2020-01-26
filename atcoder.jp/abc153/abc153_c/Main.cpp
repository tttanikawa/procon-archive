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
constexpr int INF = 1e9;
#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

template <typename T>
ll slice_sum(const std::vector<T> &v, size_t from, size_t to) {
	return std::accumulate(std::next(v.cbegin(), from), std::next(v.cbegin(), to), T{});
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, K;
	cin >> N >> K;
	vector<ll> H(N);
	for (int i = 0; i < N; i++) {
		cin >> H[i];
	}
	if (N <= K) {
		cout << 0 << endl;
		return 0;
	}
	sort(H.begin(), H.end());

	ll ans = slice_sum(H, 0, N - K);
	cout << ans << endl;
	return 0;
}
