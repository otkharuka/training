#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> t(N+1);
	vector<int> x(N+1);
	vector<int> y(N+1);

	t[0] = 0;
	x[0] = 0;
	y[0] = 0;
	for (int i = 1; i <= N; i++) {
		cin >> t[i] >> x[i] >> y[i];
	}

	for (int i = 0; i < N; i++) {
		int dr = abs(x[i + 1] - x[i]) + abs(y[i + 1] - y[i]);
		int dt = t[i + 1] - t[i];
		if ((dr > dt) | ((dr % 2) != (dt % 2))) {
			cout << "No" << endl;
			return 0;
		}
	}
	cout << "Yes" << endl;
	return 0;
}