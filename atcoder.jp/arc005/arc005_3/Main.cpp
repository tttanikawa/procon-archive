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

bool bfs(vector<vector<char>> &c, int R, int C, int sy, int sx, int gy, int gx) {
	queue<tuple<int, int, int>> q;
	q.push(make_tuple(sy, sx, 0));

	bool visited[R][C][3];
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			for (int k = 0; k < 3; k++) {
				visited[i][j][k] = false;
			}
		}
	}

	while (!q.empty()) {
		auto t = q.front();
		q.pop();

		auto i = get<0>(t);
		auto j = get<1>(t);
		auto x = get<2>(t);

		if (i < 0 || i > R - 1 || j < 0 || j > C - 1) {
			continue;
		}

		if (visited[i][j][x]) {
			continue;
		} else {
			visited[i][j][x] = true;
		}

		if (c[i][j] == '#') {
			if (x < 2) {
				q.push(make_tuple(i - 1, j, x + 1));
				q.push(make_tuple(i + 1, j, x + 1));
				q.push(make_tuple(i, j - 1, x + 1));
				q.push(make_tuple(i, j + 1, x + 1));
			} else {
				continue;
			}
		} else {
			q.push(make_tuple(i - 1, j, x));
			q.push(make_tuple(i + 1, j, x));
			q.push(make_tuple(i, j - 1, x));
			q.push(make_tuple(i, j + 1, x));
		}
	}

	return (visited[gy][gx][0] || visited[gy][gx][1] || visited[gy][gx][2]);
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int H, W;
	cin >> H >> W;

	int sy, sx;
	int gy, gx;
	vector<vector<char>> c(H, vector<char>(W));

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> c[i][j];
			if (c[i][j] == 's') {
				sy = i;
				sx = j;
			}
			if (c[i][j] == 'g') {
				gy = i;
				gx = j;
			}
		}
	}

	bool ans = bfs(c, H, W, sy, sx, gy, gx);
	if (ans) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}

	return 0;
}
