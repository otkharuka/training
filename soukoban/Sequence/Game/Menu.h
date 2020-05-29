#ifndef INCLUDED_GAME_MENU_H
#define INCLUDED_GAME_MENU_H

#include "Sequence\Game\Child.h"

class Image;

namespace Sequence {
	namespace Game {
		class Parent;

		class Menu : public Child {
		public:
			Menu();
			~Menu();
			void update(Parent* p);
		private:
			Image * mImage;

		};
	}
}


#endif