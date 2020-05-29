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
		Clear::Clear() {
			mImage = new Image("data/image/clear.dds");
		}

		Clear::~Clear() {
			delete mImage;
			mImage = 0;
		}

		void Clear::update(Parent* p) {
			mImage->draw(0, 0, 0, 0, mImage->width(), mImage->height());
		}
	}
}