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

using Weight = int;
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
AdjMatrix d;
void warshallFloyd(AdjMatrix &m) {			   // nは頂点数
	for (int i = 0; i < m.size(); i++)		   // 経由する頂点
		for (int j = 0; j < m.size(); j++)	 // 開始頂点
			for (int k = 0; k < m.size(); k++) // 終端
				m[j][k] = min(m[j][k], m[j][i] + m[i][k]);
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, M;
	cin >> N >> M;

	d.assign(N, vector<Weight>(N, INF));
	for (int i = 0; i < M; i++) {
		int a, b, t;
		cin >> a >> b >> t;
		d[a - 1][b - 1] = t;
		d[b - 1][a - 1] = t;
	}

	warshallFloyd(d);
	int ans = INF;

	for (int i = 0; i < N; i++) {
		d[i][i] = -1;
		int max_d = *max_element(d[i].begin(), d[i].end());
		if (max_d < ans) {
			ans = max_d;
		}
	}
	cout << ans << endl;
	return 0;
}
