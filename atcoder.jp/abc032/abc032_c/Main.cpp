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

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, K;
	cin >> N >> K;

	vector<ll> s(N);
	for (int i = 0; i < N; i++) {
		cin >> s[i];
		if (s[i] == 0) {
			cout << N << endl;
			return 0;
		}
	}

	ll l = 0;
	ll r = 0;
	ll res = 0;
	ll prod = 1;
	while (l < N) {
		while (r < N && prod * s[r] <= K) {
			prod *= s[r];
			r++;
		}
		res = max(res, r - l);
		if (l == r) {
			prod *= s[r];
			r++;
		}

		prod /= s[l];
		l++;
	}
	cout << res << endl;
	return 0;
}
