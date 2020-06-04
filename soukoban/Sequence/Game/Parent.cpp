#include "GameLib/GameLib.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Load.h"
#include "Sequence/Select.h"
#include "Sequence/Title.h"

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

		Sequence::Child* Parent::update(Sequence::Parent* p) {
			Sequence::Child* next = this;
			Sequence::Game::Child* nextChild = mChild->update(this);
			if (nextChild != mChild) {
				delete mChild;
				mChild = 0;
				mChild = nextChild;
			}
			nextChild = 0;

			switch (mNext) {

			case SEQ_SELECT:
				next = new Select();
				break;

			case SEQ_TITLE:
				next = new Title();
				break;
			}
			mNext = SEQ_NONE;
			return next;
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