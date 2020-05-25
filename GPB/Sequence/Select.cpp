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

		//�P�`�X�������ăX�e�[�W��I��
		if (Framework::instance().isKeyOn('1')) {
			//mNext���w��
			p->moveTo(Parent::SeqId::SEQ_GAME);
			//�X�e�[�W�ԍ����w��
			p->setStageId(1);
		}
		mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
	}
}