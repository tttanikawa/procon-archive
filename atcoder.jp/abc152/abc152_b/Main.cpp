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

	int a, b;
	cin >> a >> b;

	if (a < b) {
		for (int i = 0; i < b; i++) {
			cout << a;
		}
		cout << endl;
	} else {
		for (int i = 0; i < a; i++) {
			cout << b;
		}
		cout << endl;
	}

	return 0;
}
