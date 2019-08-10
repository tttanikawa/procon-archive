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
#include <unordered_map>
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
    vector<string> s(N);
	cin >> N;
    string ts;
    for (int i = 0; i < N; i++)
    {
        cin >> ts;
        sort(ts.begin(), ts.end());
        s.push_back(ts);
    }
    ll total=0;
    unordered_map<string, int> m;
    sort(s.begin(), s.end());
    int i;
    for (i = 0; i < N; i++)
    {
       if (m.count(s[i]) == 0) {
           m[s[i]] = 1;
       } else {

           total += m[s[i]];
           m[s[i]]++;
       }
    }
    cout << total << endl;
	return 0;
}
