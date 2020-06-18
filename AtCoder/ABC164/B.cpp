#include <iostream>
using namespace std;

int main() {
	int tHP, tATK, aHP, aATK;
	cin >> tHP >> tATK >> aHP >> aATK;

	int turnT = (tHP + (aATK - 1))  / aATK;
	int turnA = (aHP + (tATK - 1))  / tATK;
	if (turnT >= turnA) {
		cout << "Yes";
	}
	else if (turnT < turnA) {
		cout << "No";
	}
	return 0;
}