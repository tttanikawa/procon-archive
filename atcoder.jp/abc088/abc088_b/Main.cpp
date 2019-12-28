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

	vector<int> a(N, 0);
	for (size_t i = 0; i < N; i++)
	{
		cin >> a[i];
	}

	sort(a.begin(), a.end());

	int p_alice = 0;
	int p_bob = 0;

	for (int i = N - 1; i >= 0; i -= 2)
	{
		p_alice += a[i];
	}

	for (int i = N - 2; i >= 0; i -= 2)
	{
		p_bob += a[i];
	}

	cout << (p_alice - p_bob) << endl;
	return 0;
}
