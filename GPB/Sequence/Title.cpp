#include "GameLib/GameLib.h"
using namespace GameLib;

#include "GameLib/Framework.h"

#include "Title.h"
#include "Image.h"
#include "Parent.h"

Title::Title() {
	mImage = new Image("data/image/title.dds");
}

Title::~Title() {
	delete mImage;
	mImage = 0;
}

void Title::update(Parent* p) {

	//�X�y�[�X�L�[�ŃZ���N�g��ʂ�
	if (Framework::instance().isKeyOn(' ')) {
		//mNext���w��
		p->moveTo(Parent::SeqId::SEQ_SELECT);
	}
	mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
}