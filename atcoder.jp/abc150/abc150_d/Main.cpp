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

vector<int> a;
vector<int> ah;

int gcd(int a, int b) {
	if (a < b) {
		return gcd(b, a);
	}

	int r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

ll lcm(ll x, ll y) {
	return (x * y) / gcd(x, y);
}

ll nlcm(vector<int> &nums) {
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

	ll N, M;
	cin >> N >> M;
	a.resize(N);
	ah.resize(N);

	for (int i = 0; i < N; i++) {
		cin >> a[i];
		ah[i] = a[i] / 2;
	}

	ll l = nlcm(ah);
	for (int i = 0; i < N; i++) {
		if (l % a[i] == 0) {
			cout << 0 << endl;
			return 0;
		}
	}

	cout << (M / l + 1) / 2 << endl;

	return 0;
}
