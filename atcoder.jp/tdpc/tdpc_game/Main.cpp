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
constexpr int INF = 1e9;
constexpr ll LINF = 1e18;

#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

int A, B;
vector<int> a;
vector<int> b;
vector<vector<vector<ll>>> memo;

ll dp(ll i, ll j, bool k) {
	if (i == A && j == B) {
		return 0;
	}
	if (memo[i][j][k] != -1) {
		return memo[i][j][k];
	}

	ll res = 0;
	if (k) {
		if (i == A) {
			res = dp(i, j + 1, !k) + b[j];
		} else if (j == B) {
			res = dp(i + 1, j, !k) + a[i];
		} else {
			res = max(dp(i + 1, j, !k) + a[i], dp(i, j + 1, !k) + b[j]);
		}
	} else {
		if (i == A) {
			res = dp(i, j + 1, !k);
		} else if (j == B) {
			res = dp(i + 1, j, !k);
		} else {
			res = min(dp(i + 1, j, !k), dp(i, j + 1, !k));
		}
	}
	memo[i][j][k] = res;
	return res;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> A >> B;
	a.resize(A);
	b.resize(B);
	memo.assign(A + 1, vector<vector<ll>>(B + 1, vector<ll>(3, -1)));
	for (int i = 0; i < A; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < B; i++) {
		cin >> b[i];
	}

	cout << dp(0, 0, true) << endl;
	return 0;
}
