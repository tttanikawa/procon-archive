#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
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

int H, W;
vector<vector<int>> a;
vector<vector<ll>> dp;

ll dfs(int i, int j) {
	if (dp[i][j] > 0) {
		return dp[i][j];
	}

	ll ret = 1;

	bool ok = false;
	if (i > 0) {
		if (a[i][j] < a[i - 1][j]) {
			ret += dfs(i - 1, j);
			ret %= MOD;
			ok = true;
		}
	}
	if (j > 0) {
		if (a[i][j] < a[i][j - 1]) {
			ret += dfs(i, j - 1);
			ret %= MOD;
			ok = true;
		}
	}
	if (i < H - 1) {
		if (a[i][j] < a[i + 1][j]) {
			ret += dfs(i + 1, j);
			ret %= MOD;
			ok = true;
		}
	}
	if (j < W - 1) {
		if (a[i][j] < a[i][j + 1]) {
			ret += dfs(i, j + 1);
			ret %= MOD;
			ok = true;
		}
	}

	dp[i][j] = ret;
	return ret;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> H >> W;
	a.resize(H);
	dp.resize(H);
	for (int i = 0; i < H; i++) {
		a[i].resize(W);
		dp[i].resize(W);
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> a[i][j];
			a[i][j]--;
			dp[i][j] = -1;
		}
	}

	ll ret = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			ret += dfs(i, j);
			ret %= MOD;
		}
	}
	cout << ret << endl;
	return 0;
}
