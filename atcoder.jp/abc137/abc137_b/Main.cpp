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

	int K, X;
	cin >> K >> X;
    int start;

    for (int i = max(-1000000, X - K + 1); i < min(X + K - 1, 1000000); i++)
    {
        cout << i << " ";
    }
    cout << X + K - 1 << endl;
	return 0;
}
