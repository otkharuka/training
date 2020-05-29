#include "GameLib/GameLib.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Load.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Parent.h"
#include "File.h"
#include "State.h"




namespace Sequence {
	namespace Game {

		Parent::Parent() :
			mChild(0),
			mState(0),
			mNext(SEQ_NONE),
			mStageId(0)
		{
			mChild = new Load();
		}

		Parent::~Parent() {
			delete mChild; mChild= 0;
		}

		void Parent::update(Sequence::Parent* p) {
	
			if (mChild) {
				mChild->update(this);
			}

			switch (mNext) {

			case SEQ_LOAD:
				delete mChild; mChild= 0;
				mChild = new Load();
				break;

			case SEQ_PLAY:
				delete mChild; mChild = 0;
				mChild = new Play();
				break;

			case SEQ_CLEAR:
				delete mChild; mChild = 0;
				mChild = new Clear();
				break;

			case SEQ_MENU:
				delete mChild; mChild = 0;
				mChild = new Menu();
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

		void Parent::startLoading() {
			File file("data/stageData.txt"); 
			mState = new State(file.data(), file.size());
		}

		void Parent::init() {
			delete mState;
			mState = 0;
		}
	}
}