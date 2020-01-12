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

constexpr ll MOD = (ll)1e9 + 7;

int N;
vector<vector<int>> adj;
vector<ll> dp;
vector<ll> dp_white;

ll dfs_white(int x, int p);

ll dfs(int x, int p) {
	// cout << "dfs(" << x << "," << p << ")" << endl;
	if (dp[x] > 0) {
		return dp[x];
	}

	// xを白で塗るパターン
	ll ret = dfs_white(x, p) % MOD;

	// xを黒で塗るパターン
	ll black = 1;
	for (auto &&v : adj[x]) {
		if (v == p) {
			continue;
		}
		black *= (dfs_white(v, x) % MOD);
		black %= MOD;
	}
	ret += black;
	ret %= MOD;

	dp[x] = ret;
	// cout << ret << endl;
	return ret;
}

ll dfs_white(int x, int p) {
	// cout << "dfs_white(" << x << "," << p << ")" << endl;
	if (dp_white[x] > 0) {
		return dp_white[x];
	}

	ll ret = 1;
	for (auto &&v : adj[x]) {
		if (v == p) {
			continue;
		}
		ret *= (dfs(v, x) % MOD);
		ret %= MOD;
	}
	dp_white[x] = ret;
	// cout << "---- " << ret << endl;
	return ret;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> N;
	adj.resize(N);
	dp.resize(N);
	fill(dp.begin(), dp.end(), -1);
	dp_white.resize(N);
	fill(dp_white.begin(), dp_white.end(), -1);

	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}

	cout << dfs(0, -1) << endl;

	return 0;
}
