#include <iostream>
using namespace std;

int main() {
	long long X;
	long long deposit = 100;
	cin >> X;
	int year = 0;
	
	while (deposit < X) {
		deposit *= 1.01;
		year++;
	}

	cout << year;

	return 0;
}