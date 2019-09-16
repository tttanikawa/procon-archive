#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <bitset>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <numeric>
#include <complex>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;
typedef long long ll;
const double EPS = 1e-9;
typedef vector<int> vint;
typedef pair<int, int> pint;
#define rep(i, n) REP(i, 0, n)
#define ALL(v) v.begin(), v.end()
#define MSG(a) cout << #a << " " << a << endl;
#define REP(i, x, n) for(int i = x; i < n; i++)
template<class T, class C> void chmax(T& a, C b){ a>b?:a=b; }
template<class T, class C> void chmin(T& a, C b){ a<b?:a=b; }


int main(int argc, char const *argv[])
{
	cin.tie(0);
	ios::sync_with_stdio(false);
	
	string S;
	cin >> S;

	char c;
	bool result = true;
	for (size_t i = 0; i < S.size(); i++)
	{
		c = S[i];
		if (i % 2 == 0)
		{
			if (c == 'R' || c == 'U' || c == 'D')
			{
				
			} else {
				result = false;
			}
		} else {
			if (c == 'L' || c == 'U' || c == 'D')
			{
				
			} else {
				result = false;
			}
		}
	}
	
	if (result)
	{
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
	

	return 0;
}
