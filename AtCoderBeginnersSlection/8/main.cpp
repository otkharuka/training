#include <iostream>
#include <algorithm>

using namespace std;
int main() {
	int N;
	int d[110];
	int count = 1;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> d[i];
	}
	sort(d, d + N);
	for (int i = 0; i < N-1; i++) {
		if (d[i + 1] - d[i] > 0) {
			count++;
		}
	}
	cout << count << endl;
	return 0;
}