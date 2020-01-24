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
#include <numeric>
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

int N, K;
vector<double> w;
vector<double> p;
vector<double> wp;

double ok(double x) {
	for (int i = 0; i < N; i++) {
		wp[i] = w[i] * ((double)p[i] - x);
	}
	sort(wp.begin(), wp.end(), greater<double>());
	double sum = accumulate(wp.begin(), next(wp.begin(), K), 0.0);
	return sum;
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> N >> K;
	w.assign(N, 0);
	p.assign(N, 0);
	wp.assign(N, 0);

	for (int i = 0; i < N; i++) {
		cin >> w[i] >> p[i];
	}

	double l = 0;
	double r = 100;
	double m;

	for (int i = 0; i < 1000; i++) {
		m = (l + r) / 2;
		double s = ok(m);
		if (s >= 0) {
			l = m;
		} else {
			r = m;
		}
		//cout << l << " " << r << " " << (s + m) << endl;
	}

	cout << m << endl;
	return 0;
}
