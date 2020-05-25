#include <iostream>
#include <map>

using namespace std;

int main() {
	int N;
	map<int, int> mp;
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		int d;
		cin >> d;
		mp[d]++;
	}
	cout << mp.size()<< endl;
	return 0;
}