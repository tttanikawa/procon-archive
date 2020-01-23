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

bool ok(ll num, ll R, ll B, ll x, ll y) {
	R -= num;
	B -= num;
	if (R < 0 || B < 0) {
		return false;
	}

	if (R / (x - 1) + B / (y - 1) >= num) {
		return true;
	} else {
		return false;
	}
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	ll R, B;
	ll x, y;
	cin >> R >> B;
	cin >> x >> y;

	ll right = min(R, B);
	ll left = 0;
	while (right - left > 1) {
		ll m = (left + right) / 2;
		if (ok(m, R, B, x, y)) {
			left = m;
		} else {
			right = m;
		}
	}
	if (!ok(right, R, B, x, y)) {
		right = left;
	}

	cout << right << endl;
	return 0;
}
