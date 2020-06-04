#include "GameLib/GameLib.h"
using namespace GameLib;

#include "GameLib/Framework.h"

#include "Sequence/Parent.h"
#include "Sequence/Select.h"
#include "Sequence/Game/Parent.h"
#include "Image.h"

namespace Sequence {
	Select::Select() {
		mImage = new Image("data/image/stageSelect.dds");
	}

	Select::~Select() {
		delete mImage;
		mImage = 0;
	}

	Child* Select::update(Parent* p) {
		Child* next = this;
		if (Framework::instance().isKeyOn('1')) {
			next = new Game::Parent();
			//mNext‚ğw’è
			p->moveTo(Parent::SeqId::SEQ_GAME);
		}

		mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
		return next;
	}
}