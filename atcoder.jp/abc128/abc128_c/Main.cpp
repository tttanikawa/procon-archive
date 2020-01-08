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

vector<int> k;
vector<vector<int>> s;
vector<int> p;

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, M;
	cin >> N >> M;
	k.resize(M);
	s.resize(M);
	p.resize(M);

	for (int i = 0; i < M; i++) {
		int ki;
		cin >> ki;
		vector<int> si(ki);
		for (int j = 0; j < ki; j++) {
			cin >> si[j];
			si[j]--;
		}
		s[i] = si;
	}
	for (int i = 0; i < M; i++) {
		cin >> p[i];
	}

	ll ans = 0;
	for (int bit = 0; bit < (1 << N); bit++) {
		bool ok = true;
		for (int i = 0; i < M; i++) {
			int count = 0;
			for (auto &&sij : s[i]) {
				if (bit & (1 << sij)) {
					count++;
				}
			}
			if (count % 2 != p[i]) {
				ok = false;
				break;
			}
		}

		if (ok) {
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
