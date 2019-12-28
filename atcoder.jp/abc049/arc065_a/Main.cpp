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

	string S;
	cin >> S;
	string s[4] = {"dream", "dreamer", "erase", "eraser"};

	string sub1, sub2, sub3;
	int i = S.size() - 1;
	while (i > 3)
	{
		if (i - 4 >= 0)
		{
			sub1 = S.substr(i - 4, 5);
			if (sub1 == s[0] || sub1 == s[2]) {
				i -= 5;
				continue;
			}
		}

		if (i - 6 >= 0)
		{
			sub2 = S.substr(i - 6, 7);
			if (sub2 == s[1]) {
				i -= 7;
				continue;
			}
		}

		if (i - 5 >= 0)
		{
			sub3 = S.substr(i - 5, 6);
			if (sub3 == s[3]) {
				i -= 6;
				continue;
			}
		}

		break;
	}

	if (i == -1)
	{
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
