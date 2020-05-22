#ifndef INCLUDED_TITLE_H
#define INCLUDED_TITLE_H

class Image;
class Parent;

class Title {
public:
	Title();
	~Title();
	void update(Parent* p);
private:
	Image * mImage;

};


#endif