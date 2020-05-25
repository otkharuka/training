#ifndef INCLUDED_GAME_CLEAR_H
#define INCLUDED_GAME_CLEAR_H

class Image;

namespace Sequence{
namespace Game {
	class Parent;

	class Clear {
	public:
		Clear();
		~Clear();
		void update(Parent* p);
	private:
		Image * mImage;

	};
}
}


#endif