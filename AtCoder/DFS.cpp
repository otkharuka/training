#include <iostream>
#include <vector>

using namespace std;

bool gClear = false;
char c[510][510];
bool checked[510][510];
int H, W;
int sX, sY;


void search(int x, int y) {

	if (x < 0 || x >= H || y < 0 || y >= W) return;
	if (gClear == true) return;
	if (checked[x][y]) {
		return;
	}
	else {
		checked[x][y] = true;
	}
	
	if (c[x][y] == '#') return;
	
	if (c[x][y] == 'g') {
		gClear = true;
		return;
	}

	search(x + 1, y);
	search(x - 1, y);
	search(x, y + 1);
	search(x, y - 1);

}
int main() {
	cin >> H >> W;
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> c[i][j];
			checked[i][j] = false;
			if (c[i][j] == 's') {
				sX = i;
				sY = j;
			}
		}
	}

	search(sX, sY);

	if (gClear == true) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	return 0;
}
