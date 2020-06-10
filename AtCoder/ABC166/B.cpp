#include <iostream>
#include <string>
using namespace std;

int main() {
	int N, K;
	cin >> N >> K;
	bool hasOkashi[110];
	for (int i = 0; i < N; i++) {
		hasOkashi[i] = false;
	}
	int count = 0;


	for (int i = 0; i < K; i++) {
		int d;
		cin >> d;
		for (int j = 0; j < d; j++) {
			int A;
			cin >> A;
			hasOkashi[A-1] = true;
		}
	}

	for (int i = 0; i < N; i++) {
		if (hasOkashi[i] == false) count++;
	}

	cout << count;
	
	return 0;
}