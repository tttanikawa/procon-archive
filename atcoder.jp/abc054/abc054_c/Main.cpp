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

int dfs(int v, vector<vector<bool>> &graph, vector<bool> &visited)
{
	bool all_visited = true;
	for (size_t i = 0; i < graph.size(); i++)
	{
		if (visited[i] == false)
		{
			all_visited = false;
			break;
		}
	}

	if (all_visited)
	{
		return 1;
	}

	int ret = 0;
	for (size_t i = 0; i < graph.size(); i++)
	{
		if (graph[v][i] == true)
		{
			if (visited[i] == false)
			{
				visited[i] = true;
				ret += dfs(i, graph, visited);
				visited[i] = false;
			}
		}
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int N, M;
	cin >> N >> M;

	vector<vector<bool>> graph(N, vector<bool>(N, false));

	for (size_t i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a - 1][b - 1] = true;
		graph[b - 1][a - 1] = true;
	}

	vector<bool> visited(N, false);
	visited[0] = true;
	int ans = dfs(0, graph, visited);
	cout << ans << endl;
	return 0;
}
