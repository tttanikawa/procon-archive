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

	string s;
	cin >> s;

	/*
	int A = (int)(s[0] - '0');
	int B = (int)(s[1] - '0');
	int C = (int)(s[2] - '0');
	int D = (int)(s[3] - '0');
	*/

	vector<int> v(4);
	for (size_t i = 0; i < 4; i++)
	{
		v[i] = (int)(s[i] - '0');
	}

	/*
	for (size_t op1 = 0; op1 < 2; op1++)
	{
		for (size_t op2 = 0; op2 < 2; op2++)
		{
			for (size_t op3 = 0; op3 < 2; op3++)
			{
				int res = A;
				res = (op1 == 0) ? (res + B) : (res - B);
				res = (op2 == 0) ? (res + C) : (res - C);
				res = (op3 == 0) ? (res + D) : (res - D);

				if (res == 7)
				{
					cout << A << ((op1 == 0) ? "+" : "-") << B << ((op2 == 0) ? "+" : "-") << C << ((op3 == 0) ? "+" : "-") << D << "=7" << endl;
					return 0;
				}
			}
		}
	}
	*/

	for (int i = 0; i < (1 << 3); i++)
	{
		int res = v[0];
		for (int j = 0; j < 3; j++)
		{
			if (i & (1 << j))
			{
				res += v[j + 1];
			}
			else
			{
				res -= v[j + 1];
			}
		}

		if (res == 7)
		{
			cout << v[0];
			for (int j = 0; j < 3; j++)
			{
				if (i & (1 << j))
				{
					cout << "+";
				}
				else
				{
					cout << "-";
				}
				cout << v[j + 1];
			}
			cout << "=7" << endl;
			return 0;
		}
	}

	return 0;
}
