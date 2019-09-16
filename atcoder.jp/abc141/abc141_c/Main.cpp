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
	
	int N, Q;
	ll K;
	std::vector<int> A;
	std::vector<ll> P;
	cin >> N;
	cin >> K;
	cin >> Q;
	A.reserve(Q);
	P.reserve(N);

	int a;

	for (size_t i = 0; i < Q; i++)
	{
		cin >> a;
		A.push_back(a - 1);
	}

	for (size_t i = 0; i < N; i++)
	{
		P.push_back(0);
	}
	
	int winner;
	for (size_t i = 0; i < Q; i++)
	{
		P[A[i]]++;
	}
	
	for (size_t i = 0; i < N; i++)
	{
		if (K - (Q - P[i]) > 0)
		{
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}

	return 0;
}
