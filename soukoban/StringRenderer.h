#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H

class Image;

class StringRenderer {
public:
	void draw(int x, int y, const char* str);
	static void create(const char* FontImageFilename);
	static void destroy();

	static StringRenderer* instance();

private:
	StringRenderer(const char* FontImageFilename);
	StringRenderer(const StringRenderer&);
	~StringRenderer();

	Image* mFontImage;
	static StringRenderer* mInstance;
};




#endif
