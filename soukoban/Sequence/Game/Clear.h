#ifndef INCLUDED_GAME_CLEAR_H
#define INCLUDED_GAME_CLEAR_H

#include "Sequence/Game/Child.h"

class Image;

namespace Sequence{
namespace Game {
	class Parent;

	class Clear : public Child {
	public:
		Clear();
		~Clear();
		Child* update(Parent* p);
	private:
		Image * mImage;
		

	};
}
}


#endif