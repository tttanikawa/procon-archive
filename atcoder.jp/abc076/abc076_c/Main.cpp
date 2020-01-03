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

	string S, T;
	cin >> S >> T;

	bool ans = false;
	int matched_idx = -1;
	for (size_t i = 0; i < S.size() - T.size() + 1; i++)
	{
		bool matched = true;
		for (size_t j = 0; j < T.size(); j++)
		{
			if (S[i + j] != '?' && S[i + j] != T[j])
			{
				matched = false;
				break;
			}
		}

		if (matched)
		{
			ans = true;
			matched_idx = i; // search max idx
		}
	}

	if (ans)
	{
		for (size_t i = 0; i < T.size(); i++)
		{
			S[matched_idx + i] = T[i];
		}

		for (size_t i = 0; i < S.size(); i++)
		{
			if (S[i] == '?')
			{
				cout << 'a';
			}
			else
			{
				cout << S[i];
			}
		}
		cout << endl;
	}
	else
	{
		cout << "UNRESTORABLE" << endl;
	}

	return 0;
}
