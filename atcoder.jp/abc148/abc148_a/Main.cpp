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
constexpr ll LINF = 1e18;
#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int A, B;
	cin >> A >> B;

	if (min(A, B) == 1 && max(A, B) == 2) {
		cout << 3 << endl;
	}
	if (min(A, B) == 2 && max(A, B) == 3) {
		cout << 1 << endl;
	}
	if (min(A, B) == 1 && max(A, B) == 3) {
		cout << 2 << endl;
	}
	return 0;
}
