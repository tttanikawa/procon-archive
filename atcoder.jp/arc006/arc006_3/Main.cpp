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

	vector<int> w(N);
	for (size_t i = 0; i < N; i++)
	{
		cin >> w[i];
	}
	vector<int> v;
	for (size_t i = 0; i < N; i++)
	{
		int matched_idx = -1;
		int w_dif = 1000000;
		for (size_t j = 0; j < v.size(); j++)
		{
			if (w[i] <= v[j])
			{
				if (v[j] - w[i] < w_dif)
				{
					matched_idx = j;
					w_dif = v[j] - w[i];
				}
			}
		}

		if (matched_idx == -1)
		{
			v.push_back(w[i]);
		}
		else
		{
			v[matched_idx] = w[i];
		}
	}
	cout << v.size() << endl;
	return 0;
}
