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

double func(double t, double A, double B, double C) {
	return A * t + B * sin(PI * C * t) - 100;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	double A, B, C;
	cin >> A >> B >> C;

	double l = 0;
	double r = 210;
	for (int i = 0; i < 100; i++) {
		double m = (l + r) / 2;
		if (func(m, A, B, C) > 0) {
			r = m;
		} else {
			l = m;
		}
	}
	if (func(r, A, B, C) > 0) {
		r = l;
	}

	cout << r << endl;
	return 0;
}
