#include <iostream>

using namespace std;

int main() {
	int N, A, B;
	int sum = 0;
	int res = 0;
	cin >> N >> A >> B;

	for (int i = 1; i <= N; i++) {
		int tmp = i;
		while (tmp > 0) {
			sum += (tmp % 10);
			tmp /= 10;
		}
		if (A <= sum && sum <= B) {
			res += i;
		}
		sum = 0;
	}

	cout << res << endl;
	return 0;
}