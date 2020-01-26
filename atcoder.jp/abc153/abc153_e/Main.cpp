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
constexpr ll LINF = 1e18;

#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

template <class T>
inline bool chmax(T &a, T b) {
	if (a < b) {
		a = b;
		return 1;
	}
	return 0;
}

template <class T>
inline bool chmin(T &a, T b) {
	if (a > b) {
		a = b;
		return 1;
	}
	return 0;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int H, N;
	cin >> H >> N;

	vector<int> A(N);
	vector<int> B(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i] >> B[i];
	}

	vector<ll> dp(H + 1, LINF);
	dp[0] = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= H; j++) {
			if (dp[j] == LINF) {
				continue;
			}

			int cur = min(j + A[i], H);
			dp[cur] = min(dp[cur], dp[j] + B[i]);
		}
	}
	cout << dp[H] << endl;
	return 0;
}
