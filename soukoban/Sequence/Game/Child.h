#ifndef INCLUDED_GAME_CHILD_H
#define INCLUDED_GAME_CHILD_H

namespace Sequence {
	namespace Game {
		class Parent;

		class Child {
		public:
			virtual void update(Parent*) = 0;
			virtual ~Child() {};
		};
	}
}

#endif