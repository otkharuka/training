#ifndef INCLUDED_SEQUENCE_TITLE_H
#define INCLUDED_SEQUENCE_TITLE_H

#include "Sequence/Child.h"

//class Image;
class StringRenderer;

namespace Sequence {
	class Parent;

	class Title : public Child {
	public:
		Title();
		~Title();
		Child* update(Parent* p);
	private:
		//Image* mImage;
		StringRenderer* mString;
	};
}


#endif