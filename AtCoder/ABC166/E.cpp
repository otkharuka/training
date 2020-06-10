#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
	int N;
	cin >> N;
	int A;
	unordered_map<int, int> B;
	unordered_map<int, int> C;
	int count = 0;

	for (int i = 1; i <= N; i++) {
		cin >> A; 
		B[i - A] += 1;
		C[i + A] += 1;
	}

	for (auto itr = B.begin(); itr != B.end(); itr++) {
		if (C[itr->first] > 0) {
			count += (itr->second) * C[itr->first];
		}
	}

	cout << count;

	return 0;
}