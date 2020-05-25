#ifndef INCLUDED_SEQUENCE_SELECT_H
#define INCLUDED_SEQUENCE_SELECT_H

class Image;

namespace Sequence {
	class Parent;

	class Select {
	public:
		Select();
		~Select();
		void update(Parent* p);
	private:
		Image * mImage;

	};
}


#endif