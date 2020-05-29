#include "GameLib/GameLib.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Load.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Parent.h"
#include "Image.h"
using namespace GameLib;

#include "GameLib/Framework.h"


namespace Sequence {
	namespace Game {
		Menu::Menu() {
			mImage = new Image("data/image/menuAlpha.dds");
		}

		Menu::~Menu() {
			delete mImage;
			mImage = 0;
		}

		void Menu::update(Parent* p) {

			if (Framework::instance().isKeyOn('1')) {
				//ゲームを初期化　Playへ
				//mNextを指定
				p->init();
				p->moveTo(Parent::SeqId::SEQ_LOAD);
			}
			else if (Framework::instance().isKeyOn('2')) {
				//ステージ選択　Selectへ
				p->moveTo(Parent::SeqId::SEQ_SELECT);

			}
			else if (Framework::instance().isKeyOn('3')) {
				//タイトル　Titleへ
				p->moveTo(Parent::SeqId::SEQ_TITLE);

			}
			else if (Framework::instance().isKeyOn('4')) {
				//途中のゲームに戻る Playへ
				p->moveTo(Parent::SeqId::SEQ_PLAY);

			}
			mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
		}
	}
}