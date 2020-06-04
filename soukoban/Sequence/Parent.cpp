#include "Sequence/Parent.h"
#include "Sequence/Title.h"


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
	
		Child* next = mChild->update(this);
		if (next != mChild) {
			delete mChild;
			mChild = 0;
			mChild = next;
		}
		next = 0;
	}

	void Parent::moveTo(SeqId id) {
		mNext = id;
	}

	void Parent::setStageId(int id) {
		mStageId = id;
	}
}