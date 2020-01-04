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

#define EPS (1e-7)
#define INF (923456789)
#define PI (acos(-1))

ll a[2000];
ll a_cum[2000 + 1];
int dp[2000 + 1][2000 + 1];

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, K;
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> a[i];
	}

	a_cum[0] = 0;
	for (int i = 0; i < N; i++)
	{
		a_cum[i + 1] = a_cum[i] + a[i];
	}

	if (a_cum[N] == K)
	{
		cout << 1 << endl;
		return 0;
	}

	memset(dp, INF, sizeof(dp));
	dp[0][0] = 0;

	for (int i = 0; i < N; i++)
	{
		dp[i + 1][0] = 0;

		// j-1, j日までの試合数の合計
		const ll past_matchs = a_cum[i];
		const ll todays_matchs = a_cum[i + 1];
		for (int j = 1; j <= i + 1; j++)
		{
			// 今日機嫌が良くなるために必要な勝利回数
			int win;
			if (past_matchs == 0)
			{
				win = 1;
			}
			else
			{
				win = floor((double)todays_matchs * dp[i][j - 1] / past_matchs) + 1;
			}

			if (win > todays_matchs)
			{
				win = INF;
			}
			dp[i + 1][j] = min(win, dp[i][j]);
		}
	}

	int max_comfort_days = 0;
	for (int i = 0; i <= N; i++)
	{
		if (dp[N][i] <= K)
		{
			max_comfort_days = max(i, max_comfort_days);
		}
	}

	cout << max_comfort_days << endl;

	return 0;
}
