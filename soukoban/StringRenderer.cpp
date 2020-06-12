#include "GameLib/Framework.h"
using namespace GameLib;

#include "StringRenderer.h"
#include "Image.h"

StringRenderer* StringRenderer::mInstance = 0;

StringRenderer::StringRenderer(const char* filename) {
	mFontImage = new Image(filename);
}

StringRenderer::~StringRenderer() {
	delete mFontImage;
	mFontImage = 0;
}

void StringRenderer::create(const char* filename) {
	if (!mInstance) {
		mInstance = new StringRenderer(filename);
	}
}

void StringRenderer::destroy() {
	delete mInstance;
	mInstance = 0;
}

StringRenderer* StringRenderer::instance() {
	return mInstance;
}


void StringRenderer::draw(int row, int column, const char* str) {
	const int windowWidth = Framework::instance().width();
	const int windowHeight = Framework::instance().height();

	const int charWidth = 8;
	const int charHeight = 16;
	int dstX = row * charWidth;
	int dstY = column * charHeight;

	for (int i = 0; str[i] != '\0'; i++) {
		int t = str[i];
		if (t < 32 || t >= 128) {
			t = 127;
		}
		t -= 32;
		int srcX = (t % 16) * charWidth;
		int srcY = (t / 16) * charHeight;
		mFontImage->draw(dstX, dstY, srcX, srcY, charWidth, charHeight);
		dstX += charWidth;
		if ((dstX + charWidth) > windowWidth) break;
		if ((dstY + charHeight) > windowHeight) break;


	}
}

void StringRenderer::init() {
	mFontImage->init();
}

