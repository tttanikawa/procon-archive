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

int b[2][3];
int c[3][2];
array<array<int, 3>, 3> board;

pint calc_score() {
	int chokudai = 0, naoko = 0;
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (board[i][j] == board[i + 1][j]) {
				chokudai += b[i][j];
			} else {
				naoko += b[i][j];
			}
		}
	}
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 2; j++) {
			if (board[i][j] == board[i][j + 1]) {
				chokudai += c[i][j];
			} else {
				naoko += c[i][j];
			}
		}
	}
	return make_pair(chokudai, naoko);
}

pint dfs(int step) {
	if (step == 9) {
		return calc_score();
	}

	bool is_chokudai = (step % 2 == 0);
	pint ret = make_pair(-1, -1); // (max_score_chokudai, max_score_naoko)
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (board[i][j] == -1) {
				board[i][j] = static_cast<int>(is_chokudai);
				auto ret_tmp = dfs(step + 1);

				// first loop
				if (ret.first < 0) {
					ret = ret_tmp;
				} else {
					if (is_chokudai) {
						if ((ret.first < ret_tmp.first) ||
							(ret.first == ret_tmp.first && ret.second > ret_tmp.second)) {
							ret = ret_tmp;
						}
					} else {
						if ((ret.second < ret_tmp.second) ||
							(ret.second == ret_tmp.second && ret.first > ret_tmp.first)) {
							ret = ret_tmp;
						}
					}
				}
				board[i][j] = -1;
			}
		}
	}
	return ret;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 3; j++) {
			cin >> b[i][j];
		}
	}

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 2; j++) {
			cin >> c[i][j];
		}
	}

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			board[i][j] = -1;
		}
	}
	auto ret = dfs(0);
	cout << ret.first << endl;
	cout << ret.second << endl;
	return 0;
}
