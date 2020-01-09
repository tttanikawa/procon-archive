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

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int n;
	cin >> n;
	vector<ll> a(n);
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
	}

	multiset<ll> s;

	for (ll i = 0; i < n; ++i) {
		ll now = a[i];
		auto itr = s.lower_bound(now);
		if (itr != s.begin()) {
			--itr;
			s.erase(itr);
		}
		s.insert(now);
	}
	cout << s.size() << endl;
	return 0;
}
