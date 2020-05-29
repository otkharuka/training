#ifndef INCLUDED_GAME_PLAY_H
#define INCLUDED_GAME_PLAY_H

#include "Sequence\Game\Child.h"

class Image;
class State;

namespace Sequence {
	namespace Game {
		class Parent;

		class Play : public Child {
		public:
			Play();
			~Play();
			void update(Parent* p);
		private:
			Image * mImage;

		};
	}
}


#endif