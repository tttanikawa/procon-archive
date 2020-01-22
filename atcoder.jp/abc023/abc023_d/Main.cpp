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

int N;
vector<ll> H;
vector<ll> S;

bool ok(ll x) {
	vector<ll> T(N);
	for (int i = 0; i < N; i++) {
		if (x < H[i]) {
			return false;
		}
		T[i] = (x - H[i]) / S[i];
	}
	sort(T.begin(), T.end());
	for (int i = 0; i < N; i++) {
		if (T[i] < i) {
			return false;
		}
	}
	return true;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> N;
	H.resize(N);
	S.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> H[i];
		cin >> S[i];
	}
	ll l = 0;
	ll r = 1e16;
	while (r - l > 1) {
		ll m = (l + r) / 2;
		if (ok(m)) {
			r = m;
		} else {
			l = m;
		}
	}
	if (!ok(r)) {
		r = l;
	}
	cout << r << endl;
	return 0;
}
