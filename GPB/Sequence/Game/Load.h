#ifndef INCLUDED_GAME_LOAD_H
#define INCLUDED_GAME_LOAD_H

class Image;

namespace Sequence {
	namespace Game {
		class Parent;

		class Load {
		public:
			Load();
			~Load();
			void update(Parent* p);
		private:
			Image * mImage;

		};
	}
}


#endif