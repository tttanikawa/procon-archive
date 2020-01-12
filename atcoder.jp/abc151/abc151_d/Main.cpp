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

int H, W;
vector<vector<char>> S;
vector<vector<int>> d;

void warshall_floyd(int n) {			// nは頂点数
	for (int i = 0; i < n; i++)			// 経由する頂点
		for (int j = 0; j < n; j++)		// 開始頂点
			for (int k = 0; k < n; k++) // 終端
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> H >> W;
	S.resize(H);
	for (auto &&s : S) {
		s.resize(W);
	}

	for (size_t i = 0; i < H; i++) {
		for (size_t j = 0; j < W; j++) {
			cin >> S[i][j];
		}
	}
	int n = H * W;
	d = vector<vector<int>>(n, vector<int>(n, INF));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				d[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		int y = i / W;
		int x = i % W;
		if (S[y][x] == '.') {
			if (y > 0) {
				if (S[y - 1][x] == '.') {
					d[i][i - W] = 1;
				}
			}
			if (x > 0) {
				if (S[y][x - 1] == '.') {
					d[i][i - 1] = 1;
				}
			}
			if (y < H - 1) {
				if (S[y + 1][x] == '.') {
					d[i][i + W] = 1;
				}
			}
			if (x < W - 1) {
				if (S[y][x + 1] == '.') {
					d[i][i + 1] = 1;
				}
			}
		}
	}

	warshall_floyd(n);
	int max_d = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && d[i][j] != INF) {
				max_d = max(max_d, d[i][j]);
			}
		}
	}
	cout << max_d << endl;

	return 0;
}