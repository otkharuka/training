#ifndef INCLUDED_SEQUENCE_SELECT_H
#define INCLUDED_SEQUENCE_SELECT_H

#include "Sequence/Child.h"

//class Image;
//class StringRenderer;

namespace Sequence {
	class Parent;

	class Select : public Child {
	public:
		Select();
		~Select();
		Child* update(Parent* p);
	private:
		//Image * mImage;
		//StringRenderer* mString;

	};
}


#endif