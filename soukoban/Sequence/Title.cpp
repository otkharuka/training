#include "GameLib/GameLib.h"
using namespace GameLib;

#include "GameLib/Framework.h"

#include "Sequence/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/Select.h"
#include "Image.h"

namespace Sequence {
	Title::Title() {
		mImage = new Image("data/image/title.dds");
	}

	Title::~Title() {
		delete mImage;
		mImage = 0;
	}

	Child* Title::update(Parent* p) {
		Child* next = this;

		//スペースキーでセレクト画面へ
		if (Framework::instance().isKeyOn(' ')) {
			next = new Select();
		}
		mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
		return next;
	}
}