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

	char s[3];
	cin >> s[0] >> s[1] >> s[2];

	int result = 0;
	for (size_t i = 0; i < 3; i++)
	{
		if (s[i] == '1')
		{
			result++;
		}
	}
	cout << result << endl;
	return 0;
}
