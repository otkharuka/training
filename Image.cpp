#include "GameLib/Framework.h"
#include "Image.h"
#include "File.h"
using namespace GameLib;

Image::Image(const char* filename) {


	//File* imageFile = 0;
	//imageFile = new File(filename);
	File imageFile(filename);


	setSize(imageFile.getUnsigned(16), imageFile.getUnsigned(12));

	if (imageFile.setData()) {
		cout << "image file could not be read." << endl;
		return;
	}
	if (imageFile.setSize() != 128 + mHeight * mWidth * 4) {
		cout << "image file is broken." << endl;
		return;
		//ここでreturnじゃなくてプログラム終了にしないと次のループでアクセス違反がでる
	}

	for (unsigned i = 0; i < mHeight * mWidth; i++) {
		mData[i] = imageFile.getUnsigned(128 + i * 4);
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



