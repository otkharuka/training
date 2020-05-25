#include "GameLib/Framework.h"
using namespace GameLib;
using namespace std;

#include "State.h"
#include "File.h"
#include "Image.h"
#include"Sequence/Parent.h"

Sequence::Parent* gSeq;

void mainLoop();


namespace GameLib {
	void Framework::update() {
		mainLoop();
	}
}

void mainLoop() {
	
}


void game() {
	//I—¹”»’è
	if (Framework::instance().isEndRequested()) {
		if (gSeq) {
			delete gSeq;
			gSeq = 0;
		}
		return;
	}
	

	//Å‰‚ÌƒtƒŒ[ƒ€	
	if (!gSeq) {
		gSeq = new Sequence::Parent();
	}
	
	gSeq->update();
	
}
