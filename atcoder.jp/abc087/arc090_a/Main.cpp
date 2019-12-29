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

	vector<int> A1(N, 0);
	vector<int> A2(N, 0);
	for (size_t i = 0; i < N; i++)
	{
		cin >> A1[i];
	}
	for (size_t i = 0; i < N; i++)
	{
		cin >> A2[i];
	}

	vector<int> d1(N, 0);
	vector<int> d2(N, 0);
	d1[0] = A1[0];
	d2[0] = A1[0] + A2[0];
	for (size_t i = 1; i < N; i++)
	{
		d1[i] = d1[i - 1] + A1[i];
		d2[i] = max(d1[i], d2[i - 1]) + A2[i];
	}
	cout << d2[N - 1] << endl;
	return 0;
}
