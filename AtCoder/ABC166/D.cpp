#include <iostream>
#include <vector>
using namespace std;

int main() {
	int X;
	cin >> X;
	bool found = false;

	for (int i = -200; i < 200; i++) {
		for (int j = -200; j < 200; j++) {
			if (pow(i, 5) - pow(j, 5) == X) {
				cout << i << " " << j;
				found = true;
				break;
			}
		}
		if (found) break;
	}
	return 0;
}