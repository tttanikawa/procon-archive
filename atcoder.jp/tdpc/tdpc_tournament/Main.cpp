#include <algorithm>
#include <array>
#include <cassert>
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
constexpr ll LINF = 1e18;

#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

double calc_prob(double RP, double RQ) {
	return 1.0 / (1.0 + pow(10.0, (RQ - RP) / 400.0));
}

int main(int argc, char const *argv[]) {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int K;
	cin >> K;

	int num_people = (int)pow(2, K);
	vector<double> R(num_people);
	for (int i = 0; i < num_people; i++) {
		cin >> R[i];
	}

	vector<vector<double>> dp(K + 1, vector<double>(num_people, 0));
	for (int i = 0; i < num_people; i++) {
		dp[0][i] = 1;
	}

	for (int i = 0; i < K; i++) {
		int num_member = pow(2, i + 1);
		for (int j = 0; j < num_people / num_member; j++) {
			for (int k = j * num_member; k < j * num_member + num_member / 2; k++) {
				for (int l = j * num_member + num_member / 2; l < (j + 1) * num_member; l++) {
					dp[i + 1][k] += dp[i][k] * dp[i][l] * calc_prob(R[k], R[l]);
					dp[i + 1][l] += dp[i][l] * dp[i][k] * calc_prob(R[l], R[k]);
				}
			}
		}
	}

	for (int i = 0; i < num_people; i++) {
		cout << dp[K][i] << endl;
	}

	return 0;
}
