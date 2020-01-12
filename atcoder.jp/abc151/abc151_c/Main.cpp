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

	int N, M;
	cin >> N >> M;
	vector<int> p(M);
	vector<string> S(M);
	for (int i = 0; i < M; i++) {
		cin >> p[i];
		p[i]--;
		cin >> S[i];
	}

	vector<int> first_ac(N, -1);
	vector<vector<int>> memo_wa(N);
	for (int i = 0; i < M; i++) {
		if (S[i] == "AC" && first_ac[p[i]] == -1) {
			first_ac[p[i]] = i;
		} else {
			memo_wa[p[i]].push_back(i);
		}
	}

	int total_ac = 0;
	int total_pena = 0;
	for (int i = 0; i < N; i++) {
		if (first_ac[i] != -1) {
			total_ac++;

			for (int j = 0; j < memo_wa[i].size(); j++) {
				if (memo_wa[i][j] < first_ac[i]) {
					total_pena++;
				} else {
					break;
				}
			}
		}
	}
	cout << total_ac << " " << total_pena << endl;
	return 0;
}
