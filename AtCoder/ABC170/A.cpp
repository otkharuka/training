#include <iostream>
using namespace std;

int main() {
	long long x;
	int index = 1;
	while (index < 6) {
		cin >> x;
		if (x == 0) {
			cout << index;
			break;
		}
		index++;
	}
	return 0;
}