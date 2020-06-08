#include <iostream>
#include <string>
using namespace std;

int main() {
	string S, T;
	cin >> S >> T;

	int sLen = S.size();
	if (T.size() != sLen + 1) {
		cout << "No";
		return 0;
	}

	if (T.substr(0, sLen) == S) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}
	return 0;
}