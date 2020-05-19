#include "State.h"
#include "Image.h"
#include <algorithm>
using namespace std;

State::State(const char* stageData, int size) {
	//サイズ測定
	setSize(stageData, size);
	//配列確保
	mObjects.setSize(mWidth, mHeight);
	//初期値で埋めとく
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mObjects(x, y) = OBJ_WALL; //あまった部分は壁

		}
	}
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; ++i) {
		unsigned char t;

		switch (stageData[i]) {
		case '#': t = OBJ_WALL; break;
		case ' ': t = OBJ_SPACE; break;
		case 'o': t = OBJ_BLOCK; break;
		case 'O': t = OBJ_BLOCK | OBJ_GOAL; break;
		case '.': t = (OBJ_SPACE | OBJ_GOAL); break;
		case 'p': t = OBJ_MAN; break;
		case 'P': t = OBJ_MAN | OBJ_GOAL; break;
		case '\n': x = 0; ++y; t = OBJ_UNKNOWN; break; //改行処理
		default: t = OBJ_UNKNOWN; break;
		}
		if (t != OBJ_UNKNOWN) { //知らない文字なら無視する
			mObjects(x, y) = t;
			++x;
		}
	}
	mImage = new Image("nimotsuKunImage.dds");
}

State::~State() {
	delete mImage;
	mImage = 0;
}

void State::setSize(const char* stageData, int size) {
	mWidth = mHeight = 0;
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; ++i) {
		switch (stageData[i]) {
		case '#': case ' ': case 'o': case 'O':
		case '.': case 'p': case 'P':
			++x;
			break;
		case '\n':
			++y;
			//最大値更新
			mWidth = max(mWidth, x);
			mHeight = max(mHeight, y);
			x = 0;
			break;
		}
	}
}

//imageID=idの画像を(x,y)にはる
void State::drawCell(int x, int y, unsigned id) const {
	mImage->draw(x, y, 32 * id, 0);
}


void State::draw() const {

	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			unsigned char o = mObjects(x, y);
			ImageId id = IMAGE_ID_SPACE;//初期化

			switch (mObjects(x, y)) {
			case OBJ_SPACE | OBJ_GOAL: id = IMAGE_ID_GOAL;  break;
			case OBJ_WALL | OBJ_GOAL:  id = IMAGE_ID_WALL; break;
			case OBJ_BLOCK | OBJ_GOAL: id = IMAGE_ID_BLOCK_ON_GOAL; break;
			case OBJ_MAN | OBJ_GOAL:  id = IMAGE_ID_PLAYER; break;
			case OBJ_SPACE: id = IMAGE_ID_SPACE; break;
			case OBJ_WALL: id = IMAGE_ID_WALL; break;
			case OBJ_BLOCK:  id = IMAGE_ID_BLOCK; break;
			case OBJ_MAN:  id = IMAGE_ID_PLAYER; break;
			}

			drawCell(x * 32, y * 32, id);
		}
	}
}




void State::update(char input) {
	//移動差分に変換
	int dx = 0;
	int dy = 0;
	switch (input) {
	case 'a': dx = -1; break; //左
	case 's': dx = 1; break; //右
	case 'w': dy = -1; break; //上。Yは下がプラス
	case 'z': dy = 1; break; //下。
	}
	//短い変数名をつける。
	int w = mWidth;
	int h = mHeight;
	Array2D< unsigned char >& o = mObjects;
	//人座標を検索
	int x, y;
	x = y = -1; //危険な値
	bool found = false;
	for (y = 0; y < mHeight; ++y) {
		for (x = 0; x < mWidth; ++x) {
			if ((o(x, y) & ~OBJ_GOAL) == OBJ_MAN) {
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}
	//移動
	//移動後座標
	int tx = x + dx;
	int ty = y + dy;
	//座標の最大最小チェック。外れていれば不許可
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;

	}
	//A.その方向が空白またはゴール。人が移動。
	if ((o(tx, ty) & ~OBJ_GOAL) == OBJ_SPACE) {
		o(tx, ty) = (o(tx, ty) & OBJ_GOAL) | OBJ_MAN;
		o(x, y) = (o(x, y) & OBJ_GOAL) | OBJ_SPACE;
		//B.その方向が箱。その方向の次のマスが空白またはゴールであれば移動。
	}
	else if ((o(tx, ty) & ~OBJ_GOAL) == OBJ_BLOCK) {
		//2マス先が範囲内かチェック
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) { //押せない
			return;
		}
		if ((o(tx2, ty2) & ~OBJ_GOAL) == OBJ_SPACE) {
			//順次入れ替え
			o(tx2, ty2) = (o(tx2, ty2) & OBJ_GOAL) | OBJ_BLOCK;
			o(tx, ty) = (o(tx, ty) & OBJ_GOAL) | OBJ_MAN;
			o(x, y) = (o(x, y) & OBJ_GOAL) | OBJ_SPACE;
		}
	}
}

//ブロックのところのgoalFlagが一つでもfalseなら
//まだクリアしてない
bool State::hasCleared() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			if (mObjects(x, y) == OBJ_BLOCK) return false;
		}
	}
	return true;
}
