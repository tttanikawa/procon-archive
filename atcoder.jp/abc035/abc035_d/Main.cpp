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
using AdjMatrix = vector<vector<Weight>>;

void shortestPath(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev) {
	int n = g.size();
	dist.assign(n, INF);
	dist[s] = 0;
	prev.assign(n, -1);

	priority_queue<Edge> Q; // "e < f" <=> "e.weight > f.weight"
	Q.push(Edge(-2, s, 0));
	while (!Q.empty()) {
		Edge e = Q.top();
		Q.pop();
		if (prev[e.dst] != -1)
			continue;
		prev[e.dst] = e.src;
		for (auto &&f : g[e.dst]) {
			if (dist[f.dst] > e.weight + f.weight) {
				dist[f.dst] = e.weight + f.weight;
				Q.push(Edge(f.src, f.dst, dist[f.dst]));
			}
		}
	}
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, M, T;
	cin >> N >> M >> T;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	Graph g(N);
	Graph g_rev(N);

	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g[a - 1].push_back(Edge(a - 1, b - 1, c));
		g_rev[b - 1].push_back(Edge(b - 1, a - 1, c));
	}

	vector<Weight> dist;
	vector<Weight> dist_rev;
	vector<int> prev;
	vector<int> prev_rev;
	shortestPath(g, 0, dist, prev);
	shortestPath(g_rev, 0, dist_rev, prev_rev);

	ll money_max = -1;
	for (int i = 0; i < N; i++) {
		int stay = T - (dist[i] + dist_rev[i]);
		ll money = (ll)A[i] * stay;
		if (money_max < money) {
			money_max = money;
		}
	}

	cout << money_max << endl;
	return 0;
}
