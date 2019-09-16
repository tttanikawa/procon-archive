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
	
	int N;
	string S;
	cin >> N >> S;

	char c;
	int len = 0;
	size_t mx = 0;
	for (size_t i = 1; i < N; i++)
	{
		size_t k = 0;
		for (size_t j = 0; j + i < N; j++)
		{
			if (S[j] == S[j + i])
			{
				k++;
				mx = max(mx, min(i, k));
			} else {
				k = 0;
			}
			
		}
		
	}

	cout << mx << endl;

	return 0;
}
