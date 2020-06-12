#include <iostream>
using namespace std;

int main() {
	int K, A, B;
	cin >> K >> A >> B;
	bool isAchieved = false;

	for (int i = A; i <= B; i++) {
		if (i % K == 0) {
			isAchieved = true;
			break;
		}
	}
	if (isAchieved) {
		cout << "OK";
	}
	else {
		cout << "NG";
	}
	
	return 0;
}