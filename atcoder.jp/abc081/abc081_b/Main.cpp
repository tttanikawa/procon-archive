#include <algorithm>
#include <array>
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

	vector<int> A(N, 0);
	for (size_t i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	vector<int> counts(N, 0);
	for (size_t i = 0; i < N; i++)
	{
		int div = A[i];
		while (div % 2 == 0)
		{
			counts[i]++;
			div = div / 2;
		}
	}

	cout << *min_element(counts.begin(), counts.end()) << endl;

	return 0;
}
