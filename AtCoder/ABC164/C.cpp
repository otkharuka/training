#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
	set<string> gacha;
	int count = 1;
	int N;
	cin >> N;
	while (count <= N) {
		string s;
		cin >> s;
		gacha.insert(s);
		count++;
	}
	cout << gacha.size();
	
	return 0;
}