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

	int T, N;
	cin >> T >> N;
	vector<int> A(N, 0);
	for (size_t i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	int M;
	cin >> M;
	vector<int> B(M, 0);
	for (size_t i = 0; i < M; i++)
	{
		cin >> B[i];
	}

	if (N < M)
	{
		cout << "no" << endl;
	}
	else
	{
		bool ans = true;
		for (int i = 0; i < M; i++)
		{
			bool success = false;
			for (int j = 0; j < N; j++)
			{
				if (B[i] - A[j] <= T && B[i] - A[j] >= 0)
				{
					success = true;
					A[j] = -1000;
					break;
				}
			}
			if (!success)
			{
				ans = false;
				break;
			}
		}

		if (ans)
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}

	return 0;
}
