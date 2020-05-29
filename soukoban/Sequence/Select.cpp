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

		if (Framework::instance().isKeyOn('1')) {
			//mNext‚ðŽw’è
			p->moveTo(Parent::SeqId::SEQ_GAME);
		}

		mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
	}
}