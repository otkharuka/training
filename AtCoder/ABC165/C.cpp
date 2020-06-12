#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N, M, Q;
vector<vector<int>> num(100, vector<int>(4));
int maxScore = 0;

void dfs(int A, string s) {
	s += static_cast<char>(A);
	if (s.size() == N) {
		int score = 0;
		for (int i = 0; i < Q; i++) {
			int a = num[i][0] - 1;
			int b = num[i][1] - 1;
			int c = num[i][2];
			int d = num[i][3];
			if (static_cast<int>(s[b]) - static_cast<int>(s[a]) == c) {
				score += d;
			}
		}
		if (score >= maxScore) maxScore = score;
		return;
	}

	for (int m = 1; m <= M; m++) {
		dfs(m, s);
	}
}

int main() {
	
	cin >> N >> M >> Q;
	for (int i = 0; i < Q; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> num[i][j];
		}
	}

	for (int m = 1; m <= M; m++) {
		dfs(m, "");
	}

	cout << maxScore;
	
	return 0;
}