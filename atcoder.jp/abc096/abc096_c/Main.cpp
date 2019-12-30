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

	int H, W;
	cin >> H >> W;

	vector<vector<char>> s(H, vector<char>(W));

	for (size_t i = 0; i < H; i++)
	{
		for (size_t j = 0; j < W; j++)
		{
			cin >> s[i][j];
		}
	}

	bool ans = true;
	for (size_t i = 0; i < H; i++)
	{
		for (size_t j = 0; j < W; j++)
		{
			if (s[i][j] == '#')
			{
				bool ok = false;
				if (i > 0)
				{
					if (s[i - 1][j] == '#')
					{
						ok = true;
					}
				}
				if (j > 0)
				{
					if (s[i][j - 1] == '#')
					{
						ok = true;
					}
				}
				if (i < H - 1)
				{
					if (s[i + 1][j] == '#')
					{
						ok = true;
					}
				}
				if (j < W - 1)
				{
					if (s[i][j + 1] == '#')
					{
						ok = true;
					}
				}

				if(!ok) {
					ans = false;
				}
			}
		}
	}

	if(ans) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
	return 0;
}
