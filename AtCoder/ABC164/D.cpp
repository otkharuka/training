#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;
	int count = 1;
	int ans = 0;
	string str = "";

	while (str.size() <= s.size()) {	
		str = to_string(2019 * count);
		for (int i = 0; i < s.size() - str.size() + 1; i++) {
			if (s.substr(i, str.size()) == str) {
				ans++;
			}
		}
		count++;
	}

	cout << ans;
	return 0;
}