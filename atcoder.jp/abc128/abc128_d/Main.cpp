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

int N, K;
vector<ll> V;

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> N >> K;
	V.resize(N);
	for (int i = 0; i < N; ++i)
		cin >> V[i];

	long long res = 0;
	for (int p = 0; p <= min(K, N); ++p) {
		for (int q = 0; p + q <= min(K, N); ++q) {
			vector<long long> v;
			long long cur = 0;
			for (int i = 0; i < p; ++i)
				v.push_back(V[i]), cur += V[i];
			for (int i = 0; i < q; ++i)
				v.push_back(V[N - 1 - i]), cur += V[N - 1 - i];

			sort(v.begin(), v.end());
			for (int i = 0; i < min(K - p - q, (int)v.size()); ++i) {
				if (v[i] < 0)
					cur -= v[i];
			}
			res = max(res, cur);
		}
	}
	cout << res << endl;
	return 0;
}
