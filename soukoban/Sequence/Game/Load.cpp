                                                    
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
		Load::Load():
		mStart(false),
		mCount(0)
		{
			mImage = new Image("data/image/loading.dds");
		}

		Load::~Load() {
			delete mImage;
			mImage = 0;
		}

		void Load::update(Parent* p) {
			if (!mStart) {
				p->startLoading();
			}
			if (mCount == 60) {
				//mNext���w��
				p->moveTo(Parent::SeqId::SEQ_PLAY);
			}
			mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
			mCount++;
		}
	}
}