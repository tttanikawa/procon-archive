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

	int N;
	ll M;
	cin >> N >> M;

	vector<int> A(N, 0);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}

	// 昇順でソート
	sort(A.begin(), A.end());

	// min_happiness以上の幸福度を獲得可能な握手パターンがM以上あるか
	auto isOK = [&](int min_happiness) {
		ll count_shake = 0;
		// i番目との握手を固定
		for (int i = 0; i < N; i++)
		{
			// 合計の幸福度がmin_happiness以上となる最小のj
			int bound = min_happiness - A[i];
			int j = lower_bound(A.begin(), A.end(), bound) - A.begin();
			// min_happiness以上を達成可能な握手パターン数を加算
			count_shake += N - j;
		}
		return count_shake >= M;
	};

	// isOKがtrueとなる最大のmin_happinessを二分探索
	int left = 0;
	int right = A.back() * 2 + 1; // 1度の握手で獲得可能な幸福度の最大値
	while (right - left > 1)
	{
		int pivot = left + (right - left) / 2;
		if (isOK(pivot))
		{
			// OKの場合、min_happinessをもっと大きくできる
			left = pivot;
		}
		else
		{
			// NGの場合、min_happinessを緩和
			right = pivot;
		}
	}

	// 累積和を計算
	vector<ll> cumsum(N + 1, 0);
	for (int i = 0; i < N; i++)
	{
		cumsum[i + 1] = cumsum[i] + A[i];
	}

	// 合計幸福度を計算
	ll total_happiness = 0;
	ll count = 0;
	for (int i = 0; i < N; i++)
	{
		// 合計の幸福度がleft - A[i]以上となる最小のj
		int j = lower_bound(A.begin(), A.end(), left - A[i]) - A.begin();
		count += N - j;
		total_happiness += cumsum[N] - cumsum[j]; // 各jの幸福度の合計
		total_happiness += (ll)A[i] * (N - j);	// iの幸福度の合計
	}

	total_happiness -= (ll)left * (count - M);
	cout << total_happiness << endl;

	return 0;
}
