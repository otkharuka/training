#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N, a;
	int Alice = 0;
	int Bob = 0;
	cin >> N;
	int* card = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> a;
		card[i] = a;
	}
	sort(card, card+N);
	int j = N-1;
	while (j >= 0) {
		Alice += card[j];
		j--;
		if (j < 0) break;
		Bob += card[j];
		j--;
	}
	delete[] card;
	cout << Alice - Bob << endl;
	return 0;
}