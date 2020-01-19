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

inline int keta(int x) {
	return floor(log10(x)) + 1;
}

inline int pre(int x) {
	return x / pow(10, keta(x) - 1);
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;

	vector<vector<int>> c(10, vector<int>(10, 0));
	for (int i = 0; i <= N; i++) {
		if (i % 10 == 0) {
			continue;
		}

		c[pre(i)][i % 10]++;
	}
	int ans = 0;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			ans += c[i][j] * c[j][i];
		}
	}
	cout << ans << endl;
	return 0;
}
