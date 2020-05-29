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
				//�Q�[�����������@Play��
				//mNext���w��
				p->init();
				p->moveTo(Parent::SeqId::SEQ_LOAD);
			}
			else if (Framework::instance().isKeyOn('2')) {
				//�X�e�[�W�I���@Select��
				p->moveTo(Parent::SeqId::SEQ_SELECT);

			}
			else if (Framework::instance().isKeyOn('3')) {
				//�^�C�g���@Title��
				p->moveTo(Parent::SeqId::SEQ_TITLE);

			}
			else if (Framework::instance().isKeyOn('4')) {
				//�r���̃Q�[���ɖ߂� Play��
				p->moveTo(Parent::SeqId::SEQ_PLAY);

			}
			mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
		}
	}
}