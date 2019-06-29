#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <array>
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
    int t;
    vector<int> d;
    cin >> N;
    for (size_t i = 0; i < N; i++)
    {
        cin >> t;
        d.push_back(t);
    }

    sort(d.begin(), d.end());
    int N2 = N / 2;
    int median = d[N2];

    int K = 0;
    int count = 1;
    int i = 1;
    int j = 1;
    int tmp = 0;
    int larger = median;
    int smaller = median;

    if (median == d[N2 - 1])
    {
        cout << 0 << "\n";
    } else {
        while (true)
        {
            if (median - i > d[N2 - 1])
            {
                count++;
                i++;
            } else {
                break;
            }
        }
        cout << count << "\n";
    }


	return 0;
}
