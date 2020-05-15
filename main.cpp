#include "GameLib/Framework.h"
using namespace GameLib;

#include <fstream>
#include <algorithm>
using namespace std;


void readFile(char** buffer, int* size, const char* filename);
void drawCell(int x, int y, unsigned id);
unsigned getUnsigned(const char* p);
void mainLoop();


//ステージの各マスの状態を格納する
template< class T > class Array2D {
public:
	Array2D() : mArray(0) {}//コンストラクタでmArray=0と初期設定する
	~Array2D() {
		delete[] mArray;
		mArray = 0;  
	}
	void setSize(int size0, int size1) {
		mSize0 = size0;
		mSize1 = size1;
		mArray = new T[size0 * size1];
	}
	//Array2D(1, 3)の書き方でmArrayにアクセスできる
	T& operator()(int index0, int index1) {
		return mArray[index1 * mSize0 + index0];
	}
	const T& operator()(int index0, int index1) const {
		return mArray[index1 * mSize0 + index0];
	}
private:
	T* mArray;
	int mSize0;
	int mSize1;
};

//各マスの状態に関するクラス
class State {
public:
	State(const char* stageData, int size);
	void update(char input);//ステージの各マスの状態の後進
	void draw() const;//ステージの各マスの状態を読みとって画像をはる
	bool hasCleared() const;//クリアしたかどうかのチェック
private:
	enum Object {
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN,
		OBJ_GOAL = (1 << 7),
	};
	void setSize(const char* stageData, int size);//ステージのサイズをstageDataから読み取る

	int mWidth;
	int mHeight;
	Array2D< unsigned char > mObjects;//ステージの各マスの状態を格納
									 
};

//画像の貼り付けに関するクラス
class Image {
public:
	Image(const char* filename);
	~Image() {
		delete[] mData;
		mData = 0;
	}
	enum ImageId {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};
	void setSize(int width, int height) {
		mWidth = width;
		mHeight = height;
		mData = new unsigned[width * height];
	}
	void drawPictures(int dstX, int dstY, int srcX, int srcY);

private:
	int mWidth;
	int mHeight;
	unsigned* mData;
};

State* gState = 0;

void Framework::update() {
	mainLoop();
}

void mainLoop() {
	//最初の1ループめ
	if (!gState) {
		const char* filename = "stageData.txt";
		char* stageData;
		int fileSize;
		readFile(&stageData, &fileSize, filename);

		if (!stageData) {
			cout << "stage file could not be read." << endl;
			return;
		}
		gState = new State(stageData, fileSize);
		
		delete[] stageData;
		stageData = 0;

		//入力前の状態を一回描画する
		gState->draw();
		return;
	}

	//メインループ
	//入力取得
	cout << "a:left s:right w:up z:down. command?" << endl; //操作説明
	char input;
	cin >> input;
	gState->update(input);
	gState->draw();
	//クリアチェック
	if (gState->hasCleared()) {
		cout << "Congratulation's! you won." << endl;
		delete gState;
		gState = 0;
		return;
	}

	//終了判定
	if (input == 'q') {
		Framework::instance().requestEnd();
	}
	//×ボタン押されてる？
	if (Framework::instance().isEndRequested()) {
		if (gState) {
			delete gState;
			gState = 0;
		}
		return;
	}

}




//---------------------以下関数定義------------------------------------------

void readFile(char** buffer, int* size, const char* filename) {
	ifstream in(filename, ifstream::binary);
	if (!in) {
		*buffer = 0;
		*size = 0;
	}
	else {
		in.seekg(0, ifstream::end);
		*size = static_cast< int >(in.tellg());
		in.seekg(0, ifstream::beg);
		*buffer = new char[*size];
		in.read(*buffer, *size);
		//cout.write(*buffer, *size);
	}
}

//imageID=idの画像を(x,y)にはる
void drawCell(int x, int y, unsigned id) {
	Image* image = 0;
	image = new Image("nimotsuKunImage.dds");
	image->drawPictures(x, y, 32 * id, 0);
}

//unsigned charにはいっている情報をunsigned int に変換する
unsigned getUnsigned(const char* p) { 
	const unsigned char* up = reinterpret_cast<const unsigned char*> (p);
	unsigned ret = 0;
	ret |= (up[0] << 0);
	ret |= (up[1] << 8);
	ret |= (up[2] << 16);
	ret |= (up[3] << 24);
	return ret;
}

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

void State::draw() const {

	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			unsigned char o = mObjects(x, y);
			unsigned id;
					
			switch (mObjects(x, y)) {
			case OBJ_SPACE | OBJ_GOAL: cout << '.'; id = Image::IMAGE_ID_GOAL;  break;
			case OBJ_WALL | OBJ_GOAL: cout << '#'; id = Image::IMAGE_ID_WALL; break;
			case OBJ_BLOCK | OBJ_GOAL: cout << 'O'; 'O'; id = Image::IMAGE_ID_BLOCK_ON_GOAL; break;
			case OBJ_MAN | OBJ_GOAL: cout << 'P'; 'P'; id = Image::IMAGE_ID_PLAYER; break;
			case OBJ_SPACE: cout << ' '; id = Image::IMAGE_ID_SPACE; break;
			case OBJ_WALL: cout << '#'; id = Image::IMAGE_ID_WALL; break;
			case OBJ_BLOCK: cout << 'o'; id = Image::IMAGE_ID_BLOCK; break;
			case OBJ_MAN: cout << 'p'; id = Image::IMAGE_ID_PLAYER; break;
			}

			drawCell(x*32, y*32, id);
		}
		cout << endl;
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


Image::Image(const char* filename) {

	char* buffer = 0;
	int imageSize = 0;
	readFile(&buffer, &imageSize, filename);
	setSize(getUnsigned(&(buffer[16])), getUnsigned(&(buffer[12])));

	if (!buffer) {
		cout << "image file could not be read." << endl;
		return;
	}
	if (imageSize != 128 + mHeight * mWidth * 4) {
		cout << "image file is broken." << endl;
		return;
		//ここでreturnじゃなくてプログラム終了にしないと次のループでアクセス違反がでる
	}

	for (unsigned i = 0; i < mHeight * mWidth; i++) {
		mData[i] = getUnsigned(&buffer[128 + i * 4]);
	}
}

//画面上の座標(dstX, dstY)に、左上端の座標が(srcX, srcY)の画像をはる
void Image::drawPictures(int dstX, int dstY, int srcX, int srcY) {
	unsigned* vram = Framework::instance().videoMemory(); //画素は4byteの負にならない数で表現
	unsigned windowWidth = Framework::instance().width();

	for (unsigned y = 0; y < 32; y++) {
		for (unsigned x = 0; x < 32; x++) {
			vram[(dstX + x) + (dstY + y) * windowWidth] = mData[(srcX + x) + (srcY + y) * mWidth]; //vramにいれてupdate()終了後に描画される
		}
	}
}

