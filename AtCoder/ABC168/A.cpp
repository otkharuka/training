#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;

	int num = N % 10;
	if (num == 3) {
		cout << "bon";
	}
	else if (num == 0 | num == 1 | num == 6 | num == 8) {
		cout << "pon";
	} else {
		cout << "hon";
	}
	return 0;
}