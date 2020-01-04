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
#include <string>
#include <stack>
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

int N;
int c[30000];
int dp[30001];

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> N;
	for (size_t i = 0; i < N; i++)
	{
		cin >> c[i];
	}

	for (int i = 0; i < N; i++)
	{
		dp[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (c[j] < c[i])
			{
				dp[i] = max(dp[j] + 1, dp[i]);
			}
		}
	}
	int a = PI;
	int ans = 0;
	for (int i = 0; i < N; i++)
	{
		ans = max(ans, dp[i]);
	}
	cout << N - ans << endl;
	return 0;
}
