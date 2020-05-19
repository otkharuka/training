#include "Image.h"
#include "File.h"

#include "GameLib/Framework.h"
using namespace GameLib;

Image::Image( const char* filename ) : 
mWidth( 0 ),
mHeight( 0 ),
mData( 0 ){
	File f( filename );
	mHeight = f.getUnsigned( 12 );
	mWidth = f.getUnsigned( 16 );
	mData = new unsigned[ mWidth * mHeight ];
	try {

		if (!f.data()) {
			throw "image file could not be read.";
		}
		if (f.size() != 128 + mHeight * mWidth * 4) {
			throw "image file is broken.";
		}
	}
	catch (char* str) {
		cout << str << endl;

	}

	for ( int i = 0; i < mWidth * mHeight; ++i ){
		mData[ i ] = f.getUnsigned( 128 + i * 4 );
	}
}

Image::~Image(){
	delete[] mData;
	mData = 0;
}

int Image::width() const {
	return mWidth;
}

int Image::height() const {
	return mHeight;
}

void Image::draw(int dstX, int dstY, int srcX, int srcY) const{
	unsigned* vram = Framework::instance().videoMemory(); //‰æ‘f‚Í4byte‚Ì•‰‚É‚È‚ç‚È‚¢”‚Å•\Œ»
	unsigned windowWidth = Framework::instance().width();

	for (unsigned y = 0; y < 32; y++) {
		for (unsigned x = 0; x < 32; x++) {
			vram[(dstX + x) + (dstY + y) * windowWidth] = mData[(srcX + x) + (srcY + y) * mWidth]; //vram‚É‚¢‚ê‚Äupdate()I—¹Œã‚É•`‰æ‚³‚ê‚é
		}
	}
}
