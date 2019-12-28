#include <algorithm>
#include <array>
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
#include <vector>

using namespace std;
using ll = long long;

#define EPS (1e-7)
#define INF (1e9)
#define PI (acos(-1))

#define MOD ((ll)1000000007)


int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	ll N, Y;
	cin >> N >> Y;
	bool ok = false;
	for (ll i = 0; i <= N; i++)
	{
		for (ll j = 0; j <= N - i; j++)
		{
			if (i * 10000 + j * 5000 + (N - i - j) * 1000 == Y)
			{
				ok = true;
				cout << i << " " << j << " " << (N - i - j) << endl;
				break;
			}
		}

		if (ok)
		{
			break;
		}
	}

	if (!ok)
	{
		cout << "-1 -1 -1" << endl;
	}

	return 0;
}
