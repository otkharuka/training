#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H

class Image;

class StringRenderer {
public:
	static void create(const char* FontImageFilename);
	static void destroy();
	void draw(int x, int y, const char* str);
	void init();


	static StringRenderer* instance();

private:
	StringRenderer(const char* FontImageFilename);
	StringRenderer(const StringRenderer&);
	~StringRenderer();

	Image* mFontImage;
	static StringRenderer* mInstance;
};




#endif
