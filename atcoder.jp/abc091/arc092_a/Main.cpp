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

	int N;
	cin >> N;

	vector<pair<int, int>> ab(N);
	vector<pair<int, int>> cd(N);
	for (size_t i = 0; i < N; i++)
	{
		int a, b;
		cin >> a >> b;
		ab[i] = make_pair(a, b);
	}
	for (size_t i = 0; i < N; i++)
	{
		int c, d;
		cin >> c >> d;
		cd[i] = make_pair(c, d);
	}

	sort(ab.begin(), ab.end(), [](auto &l, auto &r) {
		return l.first < r.first;
	});

	sort(cd.begin(), cd.end(), [](auto &l, auto &r) {
		return l.first < r.first;
	});

	int ans = 0;
	vector<bool> matched(N, false);
	for (int i = 0; i < N; i++)
	{
		int match_idx = -1;
		int match_y = -1;
		for (int j = 0; j < N; j++)
		{
			if (cd[i].first < ab[j].first || cd[i].second < ab[j].second)
			{
				continue;
			}
			if (matched[j])
			{
				continue;
			}

			if (match_y < ab[j].second)
			{
				match_y = ab[j].second;
				match_idx = j;
			}
		}

		if (match_idx != -1)
		{
			matched[match_idx] = true;
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
