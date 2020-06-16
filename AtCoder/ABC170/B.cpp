#include <iostream>
using namespace std;

int main() {
	int X, Y;
	cin >> X >> Y;

	for (int crane = 0; crane <= X; crane++) {
		int turtle = X - crane;
		if (crane * 2 + turtle * 4 == Y) {
			cout << "Yes";
			return 0;
		}
	}
	cout << "No";
	return 0;
}