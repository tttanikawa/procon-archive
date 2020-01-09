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

vector<pint> A;

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;
	A.resize(N);

	for (size_t i = 0; i < N; i++) {
		cin >> A[i].first;
		A[i].second = i;
	}

	auto A_sorted = A;
	sort(A_sorted.begin(), A_sorted.end(), greater<pint>());

	int max_v = A_sorted[0].first;
	int max_i = A_sorted[0].second;
	int max_v2 = A_sorted[1].first;
	int max_i2 = A_sorted[1].second;

	for (int i = 0; i < N; i++) {
		if (i == max_i) {
			cout << max_v2 << endl;
		} else {
			cout << max_v << endl;
		}
	}

	return 0;
}
