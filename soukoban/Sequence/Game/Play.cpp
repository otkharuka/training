#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Play.h"
#include "Sequence/Game/Clear.h"
#include "Sequence/Game/Menu.h"

#include "State.h"
#include "Image.h"
using namespace GameLib;



namespace Sequence {
	namespace Game {
		Play::Play() {
			mImage->init();
		}

		Play::~Play() {
		}

		Child* Play::update(Parent* p) {
			Child* next = this;
			
			State* state = p->state();
			
		

			//���C�����[�v
			//�N���A�`�F�b�N
			if (state->hasCleared()) {
				next = new Clear();
			}
			Framework f = Framework::instance();
			//menu�{�^����������Ă��Ȃ����`�F�b�N
			if (f.isKeyOn('m')) {
				next = new Menu();
			}
			else {
				int dx = 0;
				int dy = 0;
				if (f.isKeyOn('a')) {
					dx -= 1;
				}
				else if (f.isKeyOn('s')) {
					dx += 1;
				}
				else if (f.isKeyOn('w')) {
					dy -= 1;
				}
				else if (f.isKeyOn('z')) {
					dy += 1;
				}
				//�X�V
				state->update(dx, dy);
			}
			
			//�`��
			state->draw();
			return next;
		}
	}
}