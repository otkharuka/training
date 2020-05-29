#ifndef INCLUDED_GAME_LOAD_H
#define INCLUDED_GAME_LOAD_H

#include "Sequence/Game/Child.h"

class Image;

namespace Sequence {
	namespace Game {
		class Parent;

		class Load : public Child {
		public:
			Load();
			~Load();
			void update(Parent* p);
		private:
			Image* mImage;
			bool mStart;
			int mCount;

		};
	}
}


#endif