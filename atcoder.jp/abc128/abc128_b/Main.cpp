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

vector<tuple<int, string, int>> SP;

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;
	SP.resize(N);

	for (int i = 0; i < N; i++) {
		string S;
		int P;
		cin >> S >> P;
		SP[i] = {i + 1, S, P};
	}

	sort(SP.begin(), SP.end(), [](auto &lhs, auto &rhs) {
		if (get<1>(lhs) != get<1>(rhs)) {
			return get<1>(lhs) < get<1>(rhs);
		} else {
			return get<2>(lhs) > get<2>(rhs);
		}
	});

	for (int i = 0; i < N; i++) {
		cout << get<0>(SP[i]) << endl;
	}

	return 0;
}
