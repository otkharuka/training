#include "Parent.h"
#include "Select.h"
#include "Title.h"

Parent::Parent() :
	mSelect(0),
	mTitle(0),
	mNext(SEQ_NONE),
	mStageId(0)
{
	mTitle = new Title();
}

Parent::~Parent() {
	delete mSelect;
	delete mTitle;
}

void Parent::update() {
	if (mSelect) {
		//thisは Parent* で、updateを読んだオブジェクトを返す
		mSelect->update(this);
	}
	else if (mTitle) {
		mTitle->update(this);
	}

	switch (mNext) {
	case SEQ_SELECT:
		delete mTitle; mTitle = 0; //メモリの二重解放がおこらないように0をいれる
		mSelect = new Select();
	case SEQ_TITLE:
		delete mSelect; mSelect = 0;
		mTitle = new Title();
	}

	mNext = SEQ_NONE;
}

void Parent::moveTo(SeqId id) {
	mNext = id;
}

void Parent::setStageId(int id) {
	mStageId = id;
}