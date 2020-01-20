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

ll gcd(ll a, ll b) {
	if (a < b) {
		return gcd(b, a);
	}
	ll r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

// 最小公倍数（2変数）
ll lcm(ll x, ll y) {
	return x / gcd(x, y) * y;
}

ll nlcm(vector<ll> &nums) {
	ll l = nums[0];
	for (int i = 1; i < nums.size(); i++) {
		l = lcm(l, nums[i]);
	}
	return l;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;

	vector<ll> T(N);
	for (int i = 0; i < N; i++) {
		cin >> T[i];
	}

	ll l = nlcm(T);
	cout << l << endl;
	return 0;
}
