#include <iostream>

using namespace std;

int main() {
	int a, b;
	int sum = 0;

	cin >> a;
	while (a > 0) {
		sum += (a % 10);
		a /= 10;
	}
	cout << sum << endl;
	cin >> b;
	return 0;
}