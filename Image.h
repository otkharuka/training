#ifndef INCLUDED_IMAGE_H
#define INCLUDED_IMAGE_H


//‰æ‘œ‚Ì“\‚è•t‚¯‚ÉŠÖ‚·‚éƒNƒ‰ƒX
class Image {
public:
	Image(const char* filename);
	~Image() {
		delete[] mData;
		mData = 0;
	}
	
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

#endif