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

// ワーシャルフロイド法による全点間の最小コスト算出
void warshallFloyd(AdjMatrix &m) {			   // nは頂点数
	for (int i = 0; i < m.size(); i++)		   // 経由する頂点
		for (int j = 0; j < m.size(); j++)	 // 開始頂点
			for (int k = 0; k < m.size(); k++) // 終端
				m[j][k] = min(m[j][k], m[j][i] + m[i][k]);
}

void foreach_permutation(int n, std::function<void(int *)> f) {
	int indexes[n];
	for (int i = 0; i < n; i++)
		indexes[i] = i;
	do {
		f(indexes);
	} while (std::next_permutation(indexes, indexes + n));
}

AdjMatrix m;
int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, M, R;
	cin >> N >> M >> R;

	vector<int> r(R);
	for (int i = 0; i < R; i++) {
		cin >> r[i];
		r[i]--;
	}

	m.assign(N, vector<Weight>(N, INF));
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		m[a - 1][b - 1] = c;
		m[b - 1][a - 1] = c;
	}

	warshallFloyd(m);

	ll ans = 1e18;
	foreach_permutation(R, [&](int *indexes) {
		ll cost = 0;
		for (int i = 0; i < R - 1; i++) {
			cost += m[r[indexes[i]]][r[indexes[i + 1]]];
		}
		if (cost < ans) {
			ans = cost;
		}
	});
	cout << ans << endl;
	return 0;
}
