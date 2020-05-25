#include "GameLib/GameLib.h"
using namespace GameLib;

#include "GameLib/Framework.h"

#include "Select.h"
#include "Image.h"
#include "Parent.h"

namespace Sequence {
	Select::Select() {
		mImage = new Image("data/image/stageSelect.dds");
	}

	Select::~Select() {
		delete mImage;
		mImage = 0;
	}

	void Select::update(Parent* p) {

		//１～９を押してステージを選ぶ
		if (Framework::instance().isKeyOn('1')) {
			//mNextを指定
			p->moveTo(Parent::SeqId::SEQ_GAME);
			//ステージ番号を指定
			p->setStageId(1);
		}
		mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
	}
}