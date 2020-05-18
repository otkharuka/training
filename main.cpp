#include "GameLib/Framework.h"
#include "File.h"
#include "State.h"
#include "Image.h"

using namespace GameLib;


#include <algorithm>
using namespace std;


void mainLoop();


State* gState = 0;

void Framework::update() {
	mainLoop();
}

void mainLoop() {
	//�ŏ���1���[�v��
	if (!gState) {
		//const char* filename = "stageData.txt";
		//File* f = 0;
		//f = new File(filename);
		File file("stageData.txt");
		char* stageData = file.setData();
		int fileSize = file.setSize();
		
		if (!stageData) {
			cout << "stage file could not be read." << endl;
			return;
		}

		gState = new State(stageData, fileSize);

		delete[] stageData;
		stageData = 0;

		//���͑O�̏�Ԃ����`�悷��
		gState->draw();
		return;
	}

	//���C�����[�v
	//���͎擾
	cout << "a:left s:right w:up z:down. command?" << endl; //�������
	char input;
	cin >> input;
	gState->update(input);
	gState->draw();
	//�N���A�`�F�b�N
	if (gState->hasCleared()) {
		cout << "Congratulation's! you won." << endl;
		delete gState;
		gState = 0;
		return;
	}

	//�I������
	if (input == 'q') {
		Framework::instance().requestEnd();
	}
	//�~�{�^��������Ă�H
	if (Framework::instance().isEndRequested()) {
		if (gState) {
			delete gState;
			gState = 0;
		}
		return;
	}

}






