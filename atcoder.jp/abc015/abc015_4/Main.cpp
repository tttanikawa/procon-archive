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

int A[50];
int B[50];
int dp[51][10001][51];
int W, N, K;

int search(int n, int a, int k)
{
	if (dp[n][a][k] != -1)
	{
		return dp[n][a][k];
	}

	if (n == N)
	{
		return 0;
	}
	if (k == 0)
	{
		return 0;
	}

	if (a >= A[n])
	{
		dp[n][a][k] = max(search(n + 1, a - A[n], k - 1) + B[n], search(n + 1, a, k));
	}
	else
	{
		dp[n][a][k] = search(n + 1, a, k);
	}

	return dp[n][a][k];
}

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	cin >> W >> N >> K;

	for (size_t i = 0; i < N; i++)
	{
		cin >> A[i] >> B[i];
	}

	for (size_t i = 0; i < 51; i++)
	{
		for (size_t j = 0; j < 10001; j++)
		{
			for (size_t k = 0; k < 51; k++)
			{
				dp[i][j][k] = -1;
			}
		}
	}

	cout << search(0, W, K) << endl;

	return 0;
}
