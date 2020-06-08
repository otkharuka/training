#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N;
	long long K;
	int A[200100];
	cin >> N >> K;

	int nextTown = 1;
	vector<bool> visited(N + 1);
	vector<int> visitedOrder(N + 1);

	int period = 0;
	int margin = 0;
	bool periodic = false;

	for (int i = 1; i <= N; i++) {
		cin >> A[i];
		visited[i] = false;
	}

	if (N < K) {
		for (int i = 0; i < N; i++) {
			if (visited[nextTown]) {
				periodic = true;
				period = i - visitedOrder[nextTown];
				margin = visitedOrder[nextTown];
				break;
			}
			visited[nextTown] = true;
			visitedOrder[nextTown] = i;
			nextTown = A[nextTown];
		}
	}
	else {
		//ŽüŠú‚ª‚È‚¢ê‡
		for (int i = 0; i < K; i++) {
			nextTown = A[nextTown];
		}
	}

	if (periodic) {
		int surplus = (K - margin) % period;
		int count = 0;
		nextTown = 1;
		while (count < surplus + margin) {
			nextTown = A[nextTown];
			count++;
		}
	}

	cout << nextTown;
	return 0;
}