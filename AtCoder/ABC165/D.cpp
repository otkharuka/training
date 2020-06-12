#include <iostream>
using namespace std;

int main() {
	int A;
	long long B, N;
	cin >> A >> B >> N;

	if (N < B) {
		cout << static_cast<long long>(A * N / B);
	}
	else {
		cout << static_cast<long long>(A * (B - 1) / B);
		/*
		for (long long x = 0; x <= N; x++) {
			long long a = (A * (B-1) / B);
			long long b = (x / B);
			long long sum = a - A * b;
			if (max < sum) {
				max = sum;
			}
			if (b > 0) break;
		}*/
	}

	return 0;
}