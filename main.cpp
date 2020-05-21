#include "GameLib/Framework.h"
using namespace GameLib;
using namespace std;

#include "State.h"
#include "File.h"
#include "Image.h"

void mainLoop();
void title();
void game();

State* gState = 0;
Image* gTitleImage = 0;
bool gPrevInputS = false;
bool gPrevInputA = false;
bool gPrevInputW = false;
bool gPrevInputZ = false;

enum Sequence {
	SEQUENCE_TITLE,
	SEQUENCE_GAME,
};

Sequence gSec = SEQUENCE_TITLE;

namespace GameLib {
	void Framework::update() {
		mainLoop();
	}
}

void mainLoop() {
	switch (gSec) {
	case SEQUENCE_TITLE:
		title();
		break;
	
	case SEQUENCE_GAME:
		game();
		break;
	}
}

void title() {
	if (!gTitleImage) {//gIsTitleSequence=false�̂Ƃ�������
		gTitleImage = new Image("title.dds");
	}
	gTitleImage->draw(0, 0, 0, 0, gTitleImage->width(), gTitleImage->height());
	//�X�y�[�X����������Q�[����ʂɐi��
	if (Framework::instance().isKeyOn(' ')) {
		gSec = SEQUENCE_GAME;
		gTitleImage->init();
		delete gTitleImage;
	}
}


void game() {
	if (Framework::instance().isEndRequested()) {
		if (gState) {
			delete gState;
			gState = 0;
		}
		return;
	}
	//�ŏ��̃t���[��	
	if (!gState) {
		File file("stageData.txt");

		try {
			if (!(file.data())) {
				throw "stage file could not be read";
			}
		}
		catch (char* str) {
			cout << str << endl;
		}

		gState = new State(file.data(), file.size());
		//����`��
		gState->draw();
		return;
	}
	bool cleared = false;
	//���C�����[�v
	//�N���A�`�F�b�N
	if (gState->hasCleared()) {
		cout << "Congratulation! you win." << endl;
		delete gState;
		gState = 0;
		//gIsTitleSequence = true;
		return;
	}
	//���͎擾
	Framework f = Framework::instance();
	int dx = 0;
	int dy = 0;
	bool inputA = f.isKeyOn('a');
	bool inputS = f.isKeyOn('s');
	bool inputW = f.isKeyOn('w');
	bool inputZ = f.isKeyOn('z');
	if (inputA && (!gPrevInputA)) {
		dx -= 1;
	}
	else if (inputS && (!gPrevInputS)) {
		dx += 1;
	}
	else if (inputW && (!gPrevInputW)) {
		dy -= 1;
	}
	else if (inputZ && (!gPrevInputZ)) {
		dy += 1;
	}
	gPrevInputA = inputA;
	gPrevInputS = inputS;
	gPrevInputW = inputW;
	gPrevInputZ = inputZ;
	//�I������
	if (Framework::instance().isKeyOn('q')) {
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//�X�V
	gState->update(dx, dy);
	//�`��
	gState->draw();
}
