#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, M;
	cin >> N >> M;
	int H[100100];
	bool isHighest[100100];
	int count = 0;

	for (int i = 0; i < N; i++) {
		isHighest[i] = true; //“¹‚ª‚Å‚Ä‚¢‚È‚¢ê‡‚à‚æ‚¢“W–]‘ä‚É‚È‚é‚©‚ç
	}
	for (int i = 0; i < N; i++) {
		cin >> H[i];
	}
	for (int i = 0; i < M; i++) {
		int A, B;
		int heightA, heightB;
		cin >> A >> B;
		heightA = H[A - 1];
		heightB = H[B - 1];

		if (heightA > heightB) {
			isHighest[B - 1] = false;
		}
		else if (heightA < heightB) {
			isHighest[A - 1] = false;
		}
		else {
			isHighest[A - 1] = false;
			isHighest[B - 1] = false;
		}

	}
	
	for (int i = 0; i < N; i++) {
		if (isHighest[i] == true) {
			count++;
		}
	}

	cout << count;

	return 0;
}