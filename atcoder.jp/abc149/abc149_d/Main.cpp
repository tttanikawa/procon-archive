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

	int N, K, R, S, P;
	string T;
	cin >> N >> K >> R >> S >> P >> T;

	ll score = 0;
	vector<char> history(N);
	vector<bool> fix(N, false);

	unordered_map<char, int> points = {{'r', R}, {'s', S}, {'p', P}};
	unordered_map<char, char> kachi = {{'r', 'p'}, {'s', 'r'}, {'p', 's'}};
	char te;
	for (size_t i = 0; i < N; i++)
	{
		if (i < K)
		{
			te = kachi[T[i]];
			fix[i] = true;
			score += points[te];
		}
		else
		{
			if (fix[i - K] == true && history[i - K] == kachi[T[i]])
			{
				te = T[i];
			}
			else
			{
				te = kachi[T[i]];
				fix[i] = true;
				score += points[te];
			}
		}

		history[i] = te;
	}
	cout << score << endl;
	return 0;
}
