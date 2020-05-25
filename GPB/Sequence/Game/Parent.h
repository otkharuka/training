#ifndef INCLUDED_GAME_PARENT_H
#define INCLUDED_GAME_PARENT_H

class State;

namespace Sequence {
	class Parent;
	namespace Game {
		class Load;
		class Menu;
		class Play;
		class Clear;

		class Parent {
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
			void update(Sequence::Parent* p);
			void moveTo(SeqId id);
			void setStageId(int id);
			State* state();
		private:

			Load * mLoad;
			Menu* mMenu;
			Play* mPlay;
			Clear* mClear;

			State* mState;

			SeqId mNext;
			int mStageId;

		};
	}
}
#endif