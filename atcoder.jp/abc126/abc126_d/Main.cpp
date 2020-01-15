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
constexpr ll LINF = 1e18;
#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

struct Edge {
	int to;
	ll cost;
};

vector<vector<Edge>> g;
vector<ll> dist;

void dfs(int x, int p) {
	for (int i = 0; i < g[x].size(); i++) {
		if (g[x][i].to == p) {
			continue;
		}
		dist[g[x][i].to] = dist[x] + g[x][i].cost;
		dfs(g[x][i].to, x);
	}
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;
	g.resize(N);
	dist = vector<ll>(N, 0);

	for (int i = 0; i < N - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		g[u - 1].push_back({v - 1, w});
		g[v - 1].push_back({u - 1, w});
	}

	dfs(0, -1);

	for (int i = 0; i < N; i++) {
		if (dist[i] % 2 == 0) {
			cout << 0 << endl;
		} else {
			cout << 1 << endl;
		}
	}

	return 0;
}
