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

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int K, S;
	cin >> K >> S;

	ll ans = 0;
	for (int x = 0; x <= S; x++)
	{
		for (int y = 0; y <= S - x; y++)
		{
			int z = S - x - y;

			if (x <= K && y <= K && z <= K)
			{
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
