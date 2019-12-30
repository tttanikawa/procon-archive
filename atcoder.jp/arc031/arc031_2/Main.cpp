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

void search(int x, int y, array<array<char, 10>, 10> &A, array<array<bool, 10>, 10> &visited)
{
	if (x < 0 || y < 0 || x > 9 || y > 9)
	{
		return;
	}
	if (visited[x][y])
	{
		return;
	}
	if (A[x][y] == 'x')
	{
		return;
	}

	visited[x][y] = true;

	search(x - 1, y, A, visited);
	search(x, y - 1, A, visited);
	search(x + 1, y, A, visited);
	search(x, y + 1, A, visited);
};

bool ok(array<array<char, 10>, 10> &A, array<array<bool, 10>, 10> &visited)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (A[i][j] == 'o' && !visited[i][j])
			{
				return false;
			}
		}
	}
	return true;
};

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	array<array<char, 10>, 10> A;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			cin >> A[i][j];
		}
	}

	bool ans = false;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			auto A_landfill = A;
			array<array<bool, 10>, 10> visited = {false};

			if (A_landfill[i][j] == 'x')
			{
				A_landfill[i][j] = 'o';
			}

			search(i, j, A_landfill, visited);
			if (ok(A_landfill, visited))
			{
				ans = true;
			}
		}
	}

	if (ans)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}

	return 0;
}
