#include <algorithm>
#include <array>
#include <cassert>
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
#include <numeric>
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

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;

	vector<int> p(N);
	for (int i = 0; i < N; i++) {
		cin >> p[i];
	}

	vector<bool> dp(10001);
	dp[0] = true;
	for (int i = 0; i < N; i++) {
		for (int j = 10000 - p[i]; j >= 0; j--) {
			dp[j + p[i]] = dp[j + p[i]] | dp[j];
		}
	}

	cout << count(dp.begin(), dp.end(), true) << endl;
	return 0;
}
