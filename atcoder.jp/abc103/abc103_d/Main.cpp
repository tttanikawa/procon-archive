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

	int N, M;
	cin >> N >> M;

	vector<pair<int, int>> p(M);
	for (size_t i = 0; i < M; i++)
	{
		int a, b;
		cin >> a;
		cin >> b;
		p[i].first = a;
		p[i].second = b;
	}

	sort(p.begin(), p.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
		return lhs.second < rhs.second;
	});

	int ans = 0;
	int end = 0;
	for (size_t i = 0; i < M; i++)
	{
		if (p[i].first >= end)
		{
			end = p[i].second;
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
