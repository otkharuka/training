#include <iostream>
#include <string>

using namespace std;

int main() {
	string S;
	cin >> S;

	int N = S.size();
	while (0 < N) {
		if ((S.substr(N - 5, 5) == "dream") | (S.substr(N - 5, 5) == "erase")) {
			N = N - 5;
		}
		else if (S.substr(N - 6, 6) == "eraser") {
			N = N - 6;
		}
		else if (S.substr(N - 7, 7) == "dreamer") {
			N = N - 7;
		}
		else {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
	
}
