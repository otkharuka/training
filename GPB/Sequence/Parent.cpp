#include "Parent.h"
#include "Select.h"
#include "Title.h"
#include "Sequence/Game/Parent.h"

namespace Sequence {

	Parent::Parent() :	
		mSelect(0),
		mTitle(0),
		mGame(0),
		mNext(SEQ_NONE),
		mStageId(0)
	{
		mTitle = new Title();
	}

	Parent::~Parent() {
		delete mSelect; mSelect = 0;
		delete mTitle; mTitle = 0;
		delete mGame; mGame = 0;
	}

	void Parent::update() {
		if (mSelect) {
			//thisは Parent* で、updateを読んだオブジェクトを返す
			mSelect->update(this);
		}
		else if (mTitle) {
			mTitle->update(this);
		}
		else if (mGame) {
			mGame->update(this);
		}

		switch (mNext) {
		case SEQ_SELECT:
			delete mTitle; mTitle = 0; //メモリの二重解放がおこらないように0をいれる
			delete mGame; mGame = 0;
			mSelect = new Select();
			break;
		case SEQ_TITLE:
			delete mSelect; mSelect = 0;
			delete mGame; mGame = 0;
			mTitle = new Title();
			break;
		case SEQ_GAME:
			delete mSelect; mSelect = 0;
			delete mTitle; mTitle = 0; //メモリの二重解放がおこらないように0をいれる
			mGame = new Game::Parent();
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