#ifndef INCLUDED_GAME_PARENT_H
#define INCLUDED_GAME_PARENT_H

#include "Sequence/Child.h"

class State;

namespace Sequence {
	class Parent;
	namespace Game {
		class Child;

		class Parent : public Sequence::Child {
		public:
			Parent();
			~Parent();

			//parent下のシーケンス遷移
			enum SeqId {
				SEQ_SELECT,
				SEQ_TITLE,

				SEQ_LOAD,
				SEQ_MENU,
				SEQ_PLAY,
				SEQ_CLEAR,

				SEQ_NONE,
			};
			Sequence::Child* update(Sequence::Parent* p);
			void moveTo(SeqId id);
			void setStageId(int id);
			State* state();
			void startLoading();
			void init();
		private:
		    Sequence::Game::Child * mChild;

			State* mState;

			SeqId mNext;
			int mStageId;

		};
	}
}
#endif