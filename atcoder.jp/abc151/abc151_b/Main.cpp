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

	int N, K, M;
	cin >> N >> K >> M;

	vector<int> A(N - 1);
	for (size_t i = 0; i < N - 1; i++) {
		cin >> A[i];
	}

	int sum = 0;
	for (size_t i = 0; i < N - 1; i++) {
		sum += A[i];
	}

	int res = M * N - sum;
	if (res > K) {
		cout << -1 << endl;
	} else {
		cout << max(res, 0) << endl;
	}

	return 0;
}
