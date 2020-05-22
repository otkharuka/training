#ifndef INCLUDED_SELECT_H
#define INCLUDED_SELECT_H

class Image;
class Parent;

class Select {
public:
	Select();
	~Select();
	void update(Parent* p);
private:
	Image* mImage;
	
};


#endif