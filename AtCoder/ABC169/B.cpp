#include <iostream>
#include <math.h>

using namespace std;

int main() {
	int N;
	long long A[100100];
	double digit = 0.0;
	long long res = 1;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		if (A[i] == 0) {
			cout << 0;
			return 0;
		}
	}
	/*
	for (int i = 0; i < N; i++) {
		digit += log10(A[i]);
		cout << digit << endl;
		if (digit > 18.0) {
			res = -1;
			break;
		}
		else {
			res *= A[i];
		}

	}
	*/
	for (int i = 0; i < N; i++) {
		//‘å¬ŠÖŒW‚ð’m‚è‚½‚¢‚¾‚¯‚Å³Šm‚È’l‚Í‚¢‚ç‚È‚¢‚©‚çŠ„‚èŽZ‚ÍØ‚èŽÌ‚Ä‚Å‚æ‚¢
		if (A[i] <= (1000000000000000000 / res)) {
			res *= A[i];
		}
		else {
			cout << -1;
			return 0;
		}
	}

	
	cout << res;
	return 0;
}