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

int N, Q, K;
vector<vector<pint>> adj;
vector<pint> xy;
vector<ll> dp;
vector<bool> visited;

void dfs(int v, int parent, ll distance) {
	for (auto &&to : adj[v]) {
		if (visited[to.first]) {
			continue;
		}
		visited[to.first] = true;

		if (to.first == parent) {
			continue;
		}

		dp[to.first] = distance + to.second;
		dfs(to.first, v, dp[to.first]);
	}

	return;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> N;
	adj.resize(N);

	for (int i = 0; i < N - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a - 1].push_back({b - 1, c});
		adj[b - 1].push_back({a - 1, c});
	}

	cin >> Q >> K;
	xy.resize(Q);
	for (int i = 0; i < Q; i++) {
		int x, y;
		cin >> x >> y;
		xy[i] = {x - 1, y - 1};
	}

	dp.resize(N);
	visited.resize(N);
	fill(visited.begin(), visited.end(), false);

	dfs(K - 1, -1, 0);
	for (int i = 0; i < Q; i++) {
		cout << dp[xy[i].first] + dp[xy[i].second] << endl;
	}

	return 0;
}
