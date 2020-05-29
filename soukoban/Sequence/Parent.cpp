#include "Parent.h"
#include "Select.h"
#include "Title.h"
#include "Sequence/Game/Parent.h"

namespace Sequence {

	Parent::Parent() :	
		mNext(SEQ_NONE),
		mStageId(0)
	{
		mChild = new Title();
	}

	Parent::~Parent() {
		delete mChild; mChild = 0;
		
	}

	void Parent::update() {
		if (mChild) {
			mChild->update(this);
		}


		switch (mNext) {
		case SEQ_SELECT:
			delete mChild; mChild = 0;
			mChild = new Select();
			break;

		case SEQ_TITLE:
			delete mChild; mChild = 0;
			mChild = new Title();
			break;

		case SEQ_GAME:
			delete mChild; mChild = 0; 
			mChild = new Game::Parent();
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
}