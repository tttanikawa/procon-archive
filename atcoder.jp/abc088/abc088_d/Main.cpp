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
	int total_white = 0;
	for (size_t i = 0; i < H; i++)
	{
		for (size_t j = 0; j < W; j++)
		{
			cin >> s[i][j];
			if (s[i][j] == '.')
			{
				total_white++;
			}
		}
	}

	vector<vector<int>> d_min(H, vector<int>(W, -1));
	queue<tuple<int, int, int>> q;
	q.push(make_tuple(0, 0, 0));

	while (!q.empty())
	{
		auto t = q.front();
		q.pop();

		auto i = get<0>(t);
		auto j = get<1>(t);
		auto d = get<2>(t);
		if (i < 0 || i > H - 1 || j < 0 || j > W - 1)
		{
			continue;
		}
		if (s[i][j] == '#')
		{
			continue;
		}
		if (d_min[i][j] != -1)
		{
			continue;
		}

		d_min[i][j] = d;
		q.push(make_tuple(i - 1, j, d + 1));
		q.push(make_tuple(i + 1, j, d + 1));
		q.push(make_tuple(i, j - 1, d + 1));
		q.push(make_tuple(i, j + 1, d + 1));
	}

	if (d_min[H - 1][W - 1] == -1)
	{
		cout << -1 << endl;
	}
	else
	{
		int min_white = d_min[H - 1][W - 1] + 1;
		int ans = total_white - min_white;
		cout << ans << endl;
	}

	return 0;
}
