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

	int N;
	cin >> N;
	vector<int> A(N);
	vector<int> B(N);
	vector<int> C(N);

	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> B[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> C[i];
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	sort(C.begin(), C.end());

	vector<vector<int>::iterator> ab_bounds(N);
	vector<vector<int>::iterator> bc_bounds(N);
	for (int i = 0; i < N; i++) {
		auto a_bound = upper_bound(A.begin(), A.end(), B[i] - 1);
		ab_bounds[i] = a_bound;
	}

	for (int i = 0; i < N; i++) {
		auto c_bound = lower_bound(C.begin(), C.end(), B[i] + 1);
		bc_bounds[i] = c_bound;
	}

	ll ans = 0;
	for (int i = 0; i < N; i++) {
		auto a_bound = upper_bound(A.begin(), A.end(), B[i] - 1);
		auto c_bound = lower_bound(C.begin(), C.end(), B[i] + 1);

		ans += (a_bound - A.begin()) * (C.end() - c_bound);
	}
	cout << ans << endl;
	return 0;
}
