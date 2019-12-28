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

	int A, B, C, X;
	cin >> A >> B >> C >> X;

	int count = 0;
	for (size_t i = 0; i <= A; i++)
	{
		for (size_t j = 0; j <= B; j++)
		{
			for (size_t k = 0; k <= C; k++)
			{
				if (500 * i + 100 * j + 50 * k == X)
				{
					count++;
				}
			}
		}
	}
	cout << count << endl;
	return 0;
}
