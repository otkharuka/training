#include "GameLib/Framework.h"
using namespace GameLib;
using namespace std;

#include "State.h"
#include "File.h"
#include "Image.h"

void mainLoop();
void title();
void select();
void load();
void game();
void menu();
void clear();

State* gState = 0;
Image* gTitleImage = 0;
Image* gSelectImage = 0;
Image* gLoadImage = 0;
Image* gMenuImage = 0;
Image* gClearImage = 0;




bool gPrevInputS = false;
bool gPrevInputA = false;
bool gPrevInputW = false;
bool gPrevInputZ = false;

enum Sequence {
	SEQUENCE_TITLE,
	SEQUENCE_SELECT,
	SEQUENCE_LOAD,
	SEQUENCE_GAME,
	SEQUENCE_MENU,
	SEQUENCE_CLEAR,
};

Sequence gSeq = SEQUENCE_TITLE;
int gSelect;

namespace GameLib {
	void Framework::update() {
		mainLoop();
	}
}

void mainLoop() {
	switch (gSeq) {
	case SEQUENCE_TITLE:
		title();
		break;
	case SEQUENCE_SELECT:
		select();
		break;
	case SEQUENCE_LOAD:
		load();
		break;
	case SEQUENCE_GAME:
		game();
		break;
	case SEQUENCE_MENU:
		menu();
		break;
	case SEQUENCE_CLEAR:
		clear();
		break;
	}
}

void drawImage(Image* image, const char* filename) {
	if (!image) {
		image = new Image(filename);
	}
	image->draw(0, 0, 0, 0, image->width(), image->height());
	
}

void title() {
	drawImage(gTitleImage, "imageData/title.dds");
	
	//�X�y�[�X����������Z���N�g��ʂɐi��
	if (Framework::instance().isKeyOn(' ')) {
		gSeq = SEQUENCE_SELECT;
		gTitleImage->init();
	}
	delete gTitleImage;
}


void select() {
	drawImage(gSelectImage, "imageData/stageSelect.dds");
	
	//�P�`�X�������ăX�e�[�W��I��
	if (Framework::instance().isKeyOn('1')) {
		gSelect = 1;
		gSeq = SEQUENCE_LOAD;
		gSelectImage->init();
	}
	delete gSelectImage;
}


void load() {
	drawImage(gLoadImage, "imageData/loading.dds");
	gSeq = SEQUENCE_GAME;
	gLoadImage->init();
	delete gLoadImage;
}


void menu() {
	drawImage(gMenuImage, "imageData/menuAlpha.dds");
	Framework f = Framework::instance();
	//���Ȃ���
	if (f.isKeyOn('1')) {
		//�Q�[����������
		delete gState;
		gState = 0;

		gLoadImage->init();
		delete gMenuImage;
		gSeq = SEQUENCE_GAME;
	}
	//�X�e�[�W�I��
	else if (f.isKeyOn('2')) {
		delete gState;
		gState = 0;

		gLoadImage->init();
		delete gMenuImage;
		gSeq = SEQUENCE_SELECT;
	}
	//�^�C�g��
	else if (f.isKeyOn('3')) {
		delete gState;
		gState = 0;

		gLoadImage->init();
		delete gMenuImage;
		gSeq = SEQUENCE_TITLE;
	}
	//�Q�[���ɖ߂�
	else if (f.isKeyOn('4')) {
		gLoadImage->init();
		delete gMenuImage;
		gSeq = SEQUENCE_GAME;
	}
}

void clear() {
	drawImage(gClearImage, "imageData/clear.dds");
	gSeq = SEQUENCE_TITLE;
	gLoadImage->init();
	delete gClearImage;
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
	
	//���C�����[�v
	//�N���A�`�F�b�N
	if (gState->hasCleared()) {
		cout << "Congratulation! you win." << endl;
		delete gState;
		gState = 0;
		gSeq = SEQUENCE_CLEAR;
		return;
	}
	//menu�{�^����������Ă��Ȃ����`�F�b�N
	if (Framework::instance().isKeyOn('m')) {
		gSeq = SEQUENCE_MENU;
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
