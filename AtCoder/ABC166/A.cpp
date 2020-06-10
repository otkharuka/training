#include <iostream>
#include <string>
using namespace std;

int main() {
	string S;
	cin >> S;
	
	if (S == "ARC") {
		cout << "ABC";
	}
	else if (S == "ABC") {
		cout << "ARC";
	}
	return 0;
}