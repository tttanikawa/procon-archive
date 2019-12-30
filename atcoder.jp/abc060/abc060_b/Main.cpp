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

int gcd(int a, int b)
{
	if (a < b)
	{
		return gcd(b, a);
	}

	int r = a % b;
	while (r != 0)
	{
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

int ngcd(vector<int> nums)
{
	int d = nums[0];
	for (size_t i = 1; i < nums.size(); i++)
	{
		d = gcd(d, nums[i]);
	}
	return d;
}

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	int A, B, C;
	cin >> A >> B >> C;

	vector<int> v = {A, B, C};
	int d = ngcd(v);

	A /= d;
	B /= d;

	if (gcd(A, B) == 1)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}

	return 0;
}
