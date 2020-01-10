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

void foreach_permutation(int n, std::function<void(int *)> f) {
	int indexes[n];
	for (int i = 0; i < n; i++)
		indexes[i] = i;
	do {
		f(indexes);
	} while (std::next_permutation(indexes, indexes + n));
}

string P;
string Q;

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;
	P.resize(N);
	Q.resize(N);

	for (size_t i = 0; i < N; i++) {
		cin >> P[i];
	}
	for (size_t i = 0; i < N; i++) {
		cin >> Q[i];
	}

	string s;
	s.resize(N);

	int loop_count = 0;
	int a = -1;
	int b = -1;
	foreach_permutation(N, [&](int *indexes) {
		for (size_t i = 0; i < N; i++) {
			s[i] = '1' + indexes[i];
		}

		//cout << s << endl;

		if (P == s) {
			a = loop_count;
		}
		if (Q == s) {
			b = loop_count;
		}

		loop_count++;
	});

	cout << abs(a - b) << endl;

	return 0;
}
