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

	string S;
	cin >> S;
	map<char, vector<int>> m;
	for (size_t i = 0; i < 4; i++)
	{
		m[S[i]].push_back(i);
	}

	if (m[S[0]].size() == 2 && m[S[1]].size() == 2 && m[S[2]].size() == 2 && m[S[3]].size() == 2)
	{
		cout << "Yes" << "\n";
	} else {
		cout << "No" << "\n";
	}



	return 0;
}
