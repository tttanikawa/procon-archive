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

#define EPS (1e-7)
#define INF (1e9)
#define PI (acos(-1))

#define MOD ((ll)1000000007)

int N, W;
ll v[201];
ll w[201];
pair<ll, ll> ps[1 << 16];
long long dp[201][201 * 1000];

long long search_w(int idx, int w_limit)
{
	if (idx < 0)
	{
		return 0;
	}

	if (dp[idx][w_limit] != -1)
	{
		return dp[idx][w_limit];
	}

	if (w_limit >= w[idx])
	{
		dp[idx][w_limit] = max(
			search_w(idx - 1, w_limit - w[idx]) + v[idx],
			search_w(idx - 1, w_limit));
	}
	else
	{
		dp[idx][w_limit] = search_w(idx - 1, w_limit);
	}

	return dp[idx][w_limit];
}

long long search_v(int idx, int v_sum)
{
	if (idx > N)
	{
		return 0;
	}

	if (dp[idx][v_sum] != (1LL << 60))
	{
		return dp[idx][v_sum];
	}

	if (v_sum > v[idx])
	{
		dp[idx][v_sum] = min(
			search_v(idx + 1, v_sum - v[idx]) + w[idx],
			search_v(idx + 1, v_sum));
	}
	else
	{
		dp[idx][v_sum] = search_v(idx + 1, v_sum);
	}

	return dp[idx][v_sum];
}

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> N >> W;

	for (int i = 0; i < N; i++)
	{
		cin >> v[i];
		cin >> w[i];
	}

	if (N <= 30)
	{
		int n = N / 2;
		for (int i = 0; i < (1 << n); i++)
		{
			ll sw = 0, sv = 0;
			for (int j = 0; j < n; j++)
			{
				if ((i >> j) & 1)
				{
					sw += w[j];
					sv += v[j];
				}
			}
			ps[i] = make_pair(sw, sv);
		}

		sort(ps, ps + (1 << n));

		int m = 1;
		for (int i = 1; i < (1 << n); i++)
		{
			if (ps[m - 1].second < ps[i].second)
			{
				ps[m] = ps[i];
				m++;
			}
		}
		ll res = 0;
		for (int i = 0; i < 1 << (N - n); i++)
		{
			ll sw = 0, sv = 0;
			for (int j = 0; j < N - n; j++)
			{
				if ((i >> j) & 1)
				{
					sw += w[n + j];
					sv += v[n + j];
				}
			}
			if (sw <= W)
			{
				ll tv = (lower_bound(ps, ps + m, make_pair(W - sw, 1ll << 55)) - 1)->second;
				res = max(res, sv + tv);
			}
		}
		cout << res << endl;
		return 0;
	}

	bool w_flag = true;
	for (int i = 0; i < N; i++)
	{
		w_flag &= (w[i] <= 1000);
	}

	if (w_flag)
	{
		memset(dp, -1, sizeof(dp));
		dp[0][0] = 0;

		cout << search_w(N, W) << endl;
		return 0;
	}
	else
	{
		// memset(dp, 1LL << 60, sizeof(dp));
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < 201 * 1000; j++)
			{
				dp[i][j] = (1LL << 60);
			}
		}
		dp[0][0] = 0;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < 201 * 1000; j++)
			{
				if (j - v[i] >= 0)
				{
					dp[i + 1][j] = min(dp[i][j - v[i]] + w[i], dp[i][j]);
				}
				else
				{
					dp[i + 1][j] = dp[i][j];
				}
			}
		}

		int ans = 0;
		for (int i = 0; i < 201 * 1000; i++)
		{
			if (dp[N][i] <= W)
			{
				ans = i;
			}
		}
		cout << ans << endl;
		return 0;
	}

	return 0;
}
