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
using pint = pair<int, int>;
using pll = pair<ll, ll>;

constexpr double EPS = 1e-7;
constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
#define PI (acos(-1))

constexpr int MOD = 1e9 + 7;

#define MAX_N 100000

// Binary Indexed Tree
// 区間和じゃなくて区間の最大を求められる版
class BIT
{
private:
	int n;
	int bit[MAX_N];

public:
	void init(int num);
	void add(int a, int w);
	int maximum(int a);
};

//初期化 M_i <= 10^5
void BIT::init(int num)
{
	n = MAX_N;
	for (int i = 0; i < MAX_N; i++)
		bit[i] = 0;
}

// a-1 の位置にwを更新
void BIT::add(int a, int w)
{
	for (int x = a; x < n; x |= x + 1)
	{
		if (bit[x] < w)
			bit[x] = w;
	}
}

// 0 から a-1 までの最大値を求める
int BIT::maximum(int a)
{
	int ret = -INF;
	for (int x = a - 1; x >= 0; x = (x & (x + 1)) - 1)
		ret = max(ret, bit[x]);
	return ret;
}

// ソート用の関数
bool comp(pair<int, int> lhs, pair<int, int> rhs)
{
	// hについて昇順で
	if (lhs.first != rhs.first)
	{
		return lhs.first < rhs.first;
	}
	else
	{
		// hが等しければwについて降順で
		return lhs.second > rhs.second;
	}
}

int main(int argc, char const *argv[])
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);

	// 入力
	int n;
	cin >> n;
	vector<pair<int, int>> v; // (height, width)
	for (int i = 0; i < n; i++)
	{
		int w, h;
		cin >> w >> h;
		v.push_back(make_pair(h, w));
	}
	// 定義した関数を用いてソート
	sort(v.begin(), v.end(), comp);

	BIT bit;
	bit.init(n);
	int dp[MAX_N];
	// 漸化式に従ってdp
	for (int i = 0; i < n; i++)
	{
		dp[i] = bit.maximum(v[i].second) + 1;
		bit.add(v[i].second, dp[i]);
	}

	// dp[i] の最大値を求める
	int retmax = 0;
	for (int i = 0; i < n; i++)
	{
		retmax = max(retmax, dp[i]);
	}

	cout << retmax << endl;

	return 0;
}
