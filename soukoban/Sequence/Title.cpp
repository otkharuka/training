#include "GameLib/GameLib.h"
using namespace GameLib;

#include "GameLib/Framework.h"

#include "Sequence/Parent.h"
#include "Sequence/Title.h"
#include "Sequence/Select.h"
#include "Image.h"
#include "../../../Chapter10/StringRenderer.h"

namespace Sequence {
	Title::Title() {
		//mImage = new Image("data/image/title.dds");
		//mString = new StringRenderer("data/image/font.dds");
		StringRenderer::create("data/image/font.dds");
	}	

	Title::~Title() {
		//delete mImage;
		//mImage = 0;
		//delete mString;
		//mString = 0;
		StringRenderer::instance()->init();
	}

	Child* Title::update(Parent* p) {
		Child* next = this;

		//スペースキーでセレクト画面へ
		if (Framework::instance().isKeyOn(' ')) {
			next = new Select();
		}
		//mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
		StringRenderer::instance()->draw(15, 5, "SOUKOBAN");
		StringRenderer::instance()->draw(12, 7, "PRESS SPACEKEY");

		return next;
	}
}