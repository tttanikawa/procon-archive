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

using Weight = ll;
struct Edge {
	int src, dst;
	Weight weight;
	Edge(int src, int dst, Weight weight) : src(src), dst(dst), weight(weight) {}
};
bool operator<(const Edge &e, const Edge &f) {
	return e.weight != f.weight ? e.weight > f.weight : // !!INVERSE!!
			   e.src != f.src ? e.src < f.src : e.dst < f.dst;
}
using Edges = vector<Edge>;
using Graph = vector<Edges>;

bool shortestPathBellmanFord(const Graph g, int s,
							 vector<Weight> &dist, vector<int> &prev) {
	int n = g.size();
	dist.assign(n, LINF + LINF);
	dist[s] = 0;
	prev.assign(n, -2);
	bool negative_cycle = false;
	for (int k = 0; k <= 2 * n; k++) {
		for (int i = 0; i < n; i++) {
			for (auto &&e : g[i]) {
				if (dist[e.dst] > dist[e.src] + e.weight) {
					dist[e.dst] = dist[e.src] + e.weight;
					prev[e.dst] = e.src;
					if (e.dst == n - 1 && k == 2 * n) {
						dist[e.dst] = -LINF;
						negative_cycle = true;
					}
				}
			}
		}
	}
	return !negative_cycle;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, M;
	cin >> N >> M;

	Graph g(N);
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g[a - 1].push_back(Edge(a - 1, b - 1, -c));
	}

	vector<Weight> dist;
	vector<int> prev;
	bool ans = shortestPathBellmanFord(g, 0, dist, prev);
	if (ans == false) {
		cout << "inf" << endl;
	} else {
		cout << -dist[N - 1] << endl;
	}

	return 0;
}
