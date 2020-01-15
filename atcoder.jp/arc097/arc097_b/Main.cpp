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

	int N, M;
	cin >> N >> M;

	vector<int> p(N);
	UnionFind d(N);
	map<int, int> m;
	for (int i = 0; i < N; i++) {
		cin >> p[i];
		p[i]--;
		m[p[i]] = i;
	}
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;
		d.unionSet(x - 1, y - 1);
	}

	int ret = 0;
	for (int i = 0; i < N; i++) {
		if (d.findSet(i, p[i])) {
			ret++;
		}
	}

	cout << ret << endl;
	return 0;
}
