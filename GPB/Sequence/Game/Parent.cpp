#include "GameLib/GameLib.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Load.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Parent.h"



namespace Sequence {
	namespace Game {

		Parent::Parent() :
			mLoad(0),
			mMenu(0),
			mPlay(0),
			mClear(0),
			mNext(SEQ_NONE),
			mStageId(0)
		{
			mLoad = new Load();
		}

		Parent::~Parent() {
			delete mLoad; mLoad = 0;
			delete mMenu; mMenu = 0;
			delete mPlay; mPlay = 0;
			delete mClear; mClear = 0;
		}

		void Parent::update(Sequence::Parent* p) {
			if (mLoad) {
				//thisは Parent* で、updateを読んだオブジェクトを返す
				mLoad->update(this);
			}
			else if (mMenu) {
				mMenu->update(this);
			}
			else if (mPlay) {
				mPlay->update(this);
			}
			else if (mClear) {
				mClear->update(this);
			}

			switch (mNext) {

			case SEQ_MENU:
				delete mLoad; mLoad = 0;
				delete mPlay; mPlay = 0;

				mMenu = new Menu();
				break;
			case SEQ_PLAY:
				delete mLoad; mLoad = 0;
				delete mMenu; mMenu = 0; //メモリの二重解放がおこらないように0をいれる

				mPlay = new Play();
				break;
			case SEQ_CLEAR:
				delete mMenu; mMenu = 0; //メモリの二重解放がおこらないように0をいれる
				delete mPlay; mPlay = 0;

				mClear = new Clear();
				break;
			case SEQ_SELECT:
				p->moveTo(Sequence::Parent::SEQ_SELECT);
				break;
			case SEQ_TITLE:
				p->moveTo(Sequence::Parent::SEQ_TITLE);
				break;


			}

			mNext = SEQ_NONE;
		}

		void Parent::moveTo(SeqId id) {
			mNext = id;
		}

		void Parent::setStageId(int id) {
			mStageId = id;
		}

		State* Parent::state() {
			return mState;
		}
	}
}