#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <sstream>
#include <complex>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>

using namespace std;
typedef long long unsigned int ll;

#define EPS (1e-7)
#define INF (1e9)
#define PI (acos(-1))


int main(int argc, char const *argv[])
{
	cin.tie(0);
	ios::sync_with_stdio(false);

    int N;
    int p[20];
    cin >> N;
    for (size_t i = 0; i < N; i++)
    {
        cin >> p[i];
    }

    int count = 0;
    for (size_t i = 1; i < N-1; i++)
    {
        if ((p[i] > p[i-1] && p[i+1] > p[i]) || (p[i] > p[i+1] && p[i-1] > p[i])
        || (p[i+1] > p[i] && p[i] == p[i-1]) || (p[i-1] > p[i] && p[i+1] == p[i]))
        {
            count++;
        }

    }
    cout << count << "\n";
	return 0;
}
