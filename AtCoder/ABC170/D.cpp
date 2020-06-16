#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> A(N);
	//bool devided = false;
	int ans = 0;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	sort(A.begin(), A.end());
	int AMax = A[N - 1];
	vector<bool> devided(AMax + 1);
	for (int i = 0; i <= AMax; i++) {
		devided[i] = true;
	}
	
	for (int i = 0; i < N; i++) {
		int a = A[i];
		int n = 2;
		if (i > 0 && A[i] == A[i - 1]) {
			n = 1;
		}
		while (a * n <=  AMax) {
			devided[a * n] = false;
			n++;
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (devided[A[i]]) ans++;
	}


	/*
	if (A[0] == A[1]) ans--;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			int x = A[i];
			if (x < A[j]) {
				break;
			}
			else {
				if (x % A[j] == 0) {
					devided = true;
					break;
				}
			}
		}
		if (!devided) {
			ans++;
		}
		devided = false;
	}
	*/
	cout << ans;
	return 0;
}