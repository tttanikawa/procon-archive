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

	int R, C;
	cin >> R >> C;

	int sy, sx, gy, gx;
	cin >> sy >> sx >> gy >> gx;
	sy--;
	sx--;
	gy--;
	gx--;

	vector<vector<char>> c(R, vector<char>(C));
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> c[i][j];
		}
	}

	constexpr char blank = '.';
	constexpr char wall = '#';

	vector<vector<int>> g(R, vector<int>(C, 100000));
	queue<tuple<int, int, int>> q;
	q.push(make_tuple(sy, sx, 0));

	while (!q.empty())
	{
		auto t = q.front();
		q.pop();

		auto i = get<0>(t);
		auto j = get<1>(t);
		auto d = get<2>(t);
		if (i < 0 || i > R - 1 || j < 0 || j > C - 1)
		{
			continue;
		}

		if (c[i][j] == wall)
		{
			continue;
		}

		if (g[i][j] != 100000)
		{
			continue;
		}
		g[i][j] = d;

		q.push(make_tuple(i - 1, j, d + 1));
		q.push(make_tuple(i + 1, j, d + 1));
		q.push(make_tuple(i, j - 1, d + 1));
		q.push(make_tuple(i, j + 1, d + 1));
	}

	cout << g[gy][gx] << endl;

	return 0;
}
