#include <iostream>
#include <string>
using namespace std;

int main() {
	int A, B, C, K;
	int sum = 0;
	cin >> A >> B >> C >> K;
	/*
	for (int i = 0; i < K; i++) {
		if (A > 0) {
			sum += 1;
			A--;
			continue;
		}
		if (B > 0) {
			sum += 0;
			B--;
			continue;
		}
		if (C > 0) {
			sum -= 1;
			C--;
			continue;
		}
	}*/
	if (K < A) {
		cout << K;
		return 0;
	} 
	else if (A <= K && K <= A + B) {
		cout << A;
	}
	else if (A + B < K && K < A + B + C) {
		cout << 2 * A + B - K;
	}
	else {
		cout << A - C;
	}
	return 0;
}