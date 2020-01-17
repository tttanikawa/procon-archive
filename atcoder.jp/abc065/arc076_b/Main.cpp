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

struct UnionFind {
	vector<int> data;
	UnionFind(int size) : data(size, -1) {}

	// union
	bool unionSet(int x, int y) {
		x = root(x);
		y = root(y);
		if (x != y) {
			if (data[y] < data[x]) {
				swap(x, y);
			}
			data[x] += data[y];
			data[y] = x;
		}
		return x != y;
	}

	// find
	bool findSet(int x, int y) {
		return root(x) == root(y);
	}

	// root
	int root(int x) {
		return data[x] < 0 ? x : data[x] = root(data[x]);
	}

	// size
	int size(int x) {
		return -data[root(x)];
	}
};

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;

	vector<pint> x(N), y(N);
	for (int i = 0; i < N; i++) {
		cin >> x[i].first >> y[i].first;
		x[i].second = y[i].second = i;
	}

	sort(x.begin(), x.end());
	sort(y.begin(), y.end());

	auto c = [](auto &lhs, auto &rhs) {
		return get<2>(lhs) > get<2>(rhs);
	};
	priority_queue<tuple<int, int, int>,
				   vector<tuple<int, int, int>>,
				   decltype(c)>
		q(c);

	for (int i = 0; i < N - 1; i++) {
		q.push(make_tuple(x[i].second, x[i + 1].second, abs(x[i].first - x[i + 1].first)));
		q.push(make_tuple(y[i].second, y[i + 1].second, abs(y[i].first - y[i + 1].first)));
	}

	UnionFind uf(N);
	ll ans = 0;
	while (uf.size(0) < N) {
		auto e = q.top();
		q.pop();

		if (!uf.findSet(get<0>(e), get<1>(e))) {
			uf.unionSet(get<0>(e), get<1>(e));
			ans += get<2>(e);
		}
	}

	cout << ans << endl;
	return 0;
}
