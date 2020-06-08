#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, M, X;
	cin >> N >> M >> X;
	
	int C[100100];
	vector<vector<int>> A(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		cin >> C[i];
		for (int j = 0; j < M; j++) {
			cin >> A.at(i).at(j);
		}
	}

	int minSum = 2000000;
	bool complete = true;



	for (unsigned i = 0; i < (1 << N); i++) {
		int understanding[20];
		for (int i = 0; i < 20; i++) {
			understanding[i] = 0;
		}
		int sum = 0;

		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				//ŽQl‘j‚ð‘I‚ñ‚Å‚¢‚½ê‡
				sum += C[j];
				for (int k = 0; k < M; k++) {
					understanding[k] += A[j][k];
				}
			}
		}
		for (int k = 0; k < M; k++) {
			if (understanding[k] < X) complete = false;
		}
		if (complete) {
			if (sum < minSum) minSum = sum;
		}
		complete = true;
	}

	if (minSum == 2000000) {
		cout << -1;
	}
	else {
		cout << minSum;
	}
	
	cin >> N;
	return 0;
}