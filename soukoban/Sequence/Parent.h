#ifndef INCLUDED_SEQUENCE_PARENT_H
#define INCLUDED_SEQUENCE_PARENT_H

#include "Sequence/Child.h"

namespace Sequence {

	class Child;
	namespace Game {
		class Parent;
	}

	class Parent {
	public:
		Parent();
		~Parent();

		//parent下のシーケンス遷移
		enum SeqId {
			SEQ_TITLE,
			SEQ_SELECT,
			SEQ_GAME,

			SEQ_NONE,
		};
		void update();
		void moveTo(SeqId id);
		void setStageId(int id);
	private:

		//Select * mSelect;
		//Title* mTitle;
		//Game::Parent* mGame;
		Child* mChild;

		SeqId mNext;
		int mStageId;

	};
}

#endif