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

constexpr ll MOD = 1e9 + 7;

std::vector<std::vector<long long>> comb(int n, int r)
{
	std::vector<std::vector<long long>> v(n + 1, std::vector<long long>(n + 1, 0));
	for (int i = 0; i < v.size(); i++)
	{
		v[i][0] = 1;
		v[i][i] = 1;
	}
	for (int j = 1; j < v.size(); j++)
	{
		for (int k = 1; k < j; k++)
		{
			v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
		}
	}
	return v;
}

constexpr int n_max = 100000 + 100000 - 1;
ll factrial[n_max + 1];
ll inverse[n_max + 1];
ll comb_fermat(int n, int k)
{
	// 階乗とその逆元を計算
	auto pow_mod = [](ll x, ll n) {
		ll ans = 1;
		while (n > 0)
		{
			if ((n & 1) == 1)
			{
				ans = ans * x % MOD;
			}
			x = x * x % MOD;
			n = (n >> 1);
		}
		return ans;
	};
	factrial[0] = 1;
	inverse[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		factrial[i] = factrial[i - 1] * i % MOD;
		inverse[i] = inverse[i - 1] * pow_mod(i, MOD - 2) % MOD;
	}
	return factrial[n] * inverse[k] % MOD * inverse[n - k] % MOD;
}

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int n, k;
	cin >> n >> k;

	auto v = comb_fermat(n + k - 1, k);
	cout << v << endl;

	return 0;
}
