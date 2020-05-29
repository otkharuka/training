#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"

#include "Sequence/Game/Play.h"
#include "Sequence/Game/Parent.h"
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

		void Play::update(Parent* p) {
			
			State* state = p->state();
			
		

			//メインループ
			//クリアチェック
			if (state->hasCleared()) {
				p->moveTo(Parent::SEQ_CLEAR);
			}
			Framework f = Framework::instance();
			//menuボタンがおされていないかチェック
			if (f.isKeyOn('m')) {
				p->moveTo(Parent::SEQ_MENU);
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
				//更新
				state->update(dx, dy);
			}
			
			//描画
			state->draw();
		}
	}
}