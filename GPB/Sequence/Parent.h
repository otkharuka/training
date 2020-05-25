#ifndef INCLUDED_SEQUENCE_PARENT_H
#define INCLUDED_SEQUENCE_PARENT_H

namespace Sequence {

	class Select;
	class Title;
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

		Select * mSelect;
		Title* mTitle;
		Game::Parent* mGame;

		SeqId mNext;
		int mStageId;

	};
}

#endif