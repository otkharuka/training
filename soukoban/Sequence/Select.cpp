#include "GameLib/GameLib.h"
using namespace GameLib;

#include "GameLib/Framework.h"

#include "Sequence/Parent.h"
#include "Sequence/Select.h"
#include "Sequence/Game/Parent.h"
//#include "Image.h"
#include "../../../Chapter10/StringRenderer.h"


namespace Sequence {
	Select::Select() {
		//mImage = new Image("data/image/stageSelect.dds");
		//mString = new StringRenderer("data/image/font.dds");
	}

	Select::~Select() {
		//delete mImage;
		//mImage = 0;
		//delete mString;
		//mString = 0;
		StringRenderer::instance()->init();

	}

	Child* Select::update(Parent* p) {
		Child* next = this;
		if (Framework::instance().isKeyOn('1')) {
			next = new Game::Parent();
			//mNext���w��
			p->moveTo(Parent::SeqId::SEQ_GAME);
		}

		//mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
		StringRenderer::instance()->draw(14, 5, "Select Stage");
		StringRenderer::instance()->draw(14, 7, "Press 1 ~ 9");


		return next;
	}
}