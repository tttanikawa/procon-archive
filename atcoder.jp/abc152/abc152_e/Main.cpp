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

constexpr ll MOD = 1e9 + 7;

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

ll lcm(ll x, ll y) {
	return x / gcd(x, y) * y;
}

ll nlcm(vector<int> &nums) {
	ll l = nums[0];
	for (int i = 1; i < nums.size(); i++) {
		l = lcm(l, nums[i]) % MOD;
	}
	return l;
}

vector<pair<ll, ll>> primeFactor(ll n) {
	vector<pair<ll, ll>> res;
	for (ll p = 2; p * p <= n; p++) {
		ll tmp = 0;
		while (n % p == 0) {
			n /= p;
			tmp++;
		}
		if (tmp != 0)
			res.push_back(make_pair(p, tmp));
	}
	if (n != 1)
		res.push_back(make_pair(n, 1));
	return move(res);
}

ll pow_mod(ll x, ll n) {
	ll ans = 1;
	while (n > 0) {
		if ((n & 1) == 1) {
			ans = ans * x % MOD;
		}
		x = x * x % MOD;
		n = (n >> 1);
	}
	return ans;
}

ll modinv(ll a) {
	ll b = MOD, x = 1, y = 0;
	while (b) {
		ll t = a / b;
		a -= t * b;
		swap(a, b);
		x -= t * y;
		swap(x, y);
	}
	x %= MOD;
	if (x < 0)
		x += MOD;
	return x;
}

ll modpow(ll a, ll n) {
	ll res = 1;
	while (n > 0) {
		if (n & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		n >>= 1;
	}
	return res;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;

	vector<int> A(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	map<int, int> m;
	for (auto &&a : A) {
		auto pf = primeFactor(a);
		for (auto &&p : pf) {
			if (m.count(p.first) == 0) {
				m[p.first] = p.second;
			} else {
				m[p.first] = max((ll)m[p.first], p.second);
			}
		}
	}

	ll l = 1;
	for (auto &&e : m) {
		l *= (ll)pow_mod(e.first, e.second) % MOD;
		l %= MOD;
	}

	ll ans = 0;
	for (int i = 0; i < N; i++) {
		ans += l * modinv(A[i]) % MOD;
		ans %= MOD;
	}
	cout << ans << endl;

	return 0;
}
