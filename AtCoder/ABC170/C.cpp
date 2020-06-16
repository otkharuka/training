#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
	int X, N;
	unordered_map<int, int> p;
	int count = 0;

	cin >> X >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		p[tmp]++;
	}

	if (p[X] == 0) {
		cout << X;
	}
	else if (p[X] > 0) {
		for (int i = 1; i < 200; i++) {
			int y = X - i;
			if (p[y] == 0) { //p‚ÉŠÜ‚Ü‚ê‚È‚¢
				cout << y;
				break;
			}
			else if (p[y] > 0) { //‚‚ÉŠÜ‚Ü‚ê‚é
				count++;
				if (count >= N) {
					cout << y - 1;
					break;
				}
			}

			int x = X + i;
			if (p[x] == 0) { //p‚ÉŠÜ‚Ü‚ê‚È‚¢
				cout << x;
				break;
			}
			else if (p[x] > 0) { //‚‚ÉŠÜ‚Ü‚ê‚é
				count++;
				if (count >= N) {
					cout << x + 1;
					break;
				}
			}
		}
	}

	return 0;
}