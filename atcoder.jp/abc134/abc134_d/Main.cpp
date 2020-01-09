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

vector<int> a;
vector<bool> ball;

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N;
	cin >> N;
	a.resize(N);
	ball = vector<bool>(N, false);

	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	int num_ball = 0;
	for (int i = N; i > 0; i--) {
		int count = 0;

		for (int j = 2; i * j <= N; j++) {
			if (ball[i * j - 1]) {
				count++;
			}
		}
		if (count % 2 != a[i - 1]) {
			ball[i - 1] = true;
			num_ball++;
		}
	}
	cout << num_ball << endl;
	for (int i = 0; i < N; i++) {
		if (ball[i]) {
			cout << (i + 1);
			num_ball--;
			if (num_ball == 0) {
				cout << endl;
				break;
			} else {
				cout << " ";
			}
		}
	}

	return 0;
}
