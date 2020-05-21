#include <iostream>
using namespace std;

int main() {
	int N;
	cin >> N;
	int* arr = new int[N];
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		arr[i] = tmp;
	}

	int count = 0;
	bool flag = 1;
	while (flag) {
		for (int i = 0; i < N; i++) {
			if (arr[i] % 2 == 0) {
				flag *= 1;
				arr[i] /= 2;
			}
			else {
				flag *= 0;
				break;
			}
		}
		if (!flag) {
			break;
		}
		count++;
	}
	delete[] arr;
	cout << count << endl;

}
