                                                    
#include "GameLib/GameLib.h"
#include "Sequence/Game/Parent.h"
#include "Sequence/Game/Load.h"
#include "Sequence/Game/Play.h"
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

		Child* Load::update(Parent* p) {
			Child* next = this;
			if (!mStart) {
				p->startLoading();
			}
			if (mCount == 60) {
				next = new Play();
			}
			mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
			mCount++;
			return next;
		}
	}
}