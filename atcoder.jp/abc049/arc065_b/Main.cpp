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

	bool findSet(int x, int y) {
		return root(x) == root(y);
	}

	int root(int x) {
		return data[x] < 0 ? x : data[x] = root(data[x]);
	}

	int size(int x) {
		return -data[root(x)];
	}
};

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, K, L;
	cin >> N >> K >> L;

	UnionFind road(N);
	UnionFind rail(N);

	for (int i = 0; i < K; i++) {
		int p, q;
		cin >> p >> q;
		road.unionSet(p - 1, q - 1);
	}

	for (int i = 0; i < L; i++) {
		int r, s;
		cin >> r >> s;
		rail.unionSet(r - 1, s - 1);
	}

	vector<pint> p(N);
	for (int i = 0; i < N; i++) {
		p[i] = make_pair(road.root(i), rail.root(i));
	}

	map<pint, int> m;
	for (auto &&i : p) {
		if (m.count(i)) {
			m[i]++;
		} else {
			m[i] = 1;
		}
	}

	for (int i = 0; i < N - 1; i++) {
		cout << m[p[i]] << " ";
	}
	cout << m[p[N - 1]] << endl;

	return 0;
}
