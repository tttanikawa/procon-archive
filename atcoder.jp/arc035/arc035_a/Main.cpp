#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	string s;
	cin >> s;

	bool result = true;

	int size = s.size();
	for(int i=0; i < size/2; i++){
		if(s[i] == '*' || s[size-1-i] == '*' || s[i] == s[size-1-i]) continue;
		else result = false;
	}

	if(result) cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}