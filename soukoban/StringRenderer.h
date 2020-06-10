#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H

class Image;

class StringRenderer {
public:
	StringRenderer(const char* FontImageFilename);
	~StringRenderer();
	void draw(int x, int y, const char* str);

private:
	Image* mFontImage;
};




#endif
