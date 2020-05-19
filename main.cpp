#include "GameLib/Framework.h"
using namespace GameLib;

#include "State.h"
#include "File.h"

void mainLoop();

State* gState = 0;

namespace GameLib{
	void Framework::update(){
		mainLoop();
	}
}

void mainLoop(){
	if ( Framework::instance().isEndRequested() ){
		if ( gState ){
			delete gState;
			gState = 0;
		}
		return;
	}
	//�ŏ��̃t���[��	
	if ( !gState ){ 
		File file( "stageData.txt" );

		try {
			if ( !( file.data() ) ){
				throw "stage file could not be read";
			}
		}
		catch(char* str) {
			cout << str << endl;
		}

		gState = new State( file.data(), file.size() );
		//����`��
		gState->draw();
		return; //���̂܂܏I���
	}
	bool cleared = false;
	//���C�����[�v
	//�N���A�`�F�b�N
	if ( gState->hasCleared() ){
		cout << "Congratulation! you win." << endl;
		delete gState;
		gState = 0;
		return;
	}
	//���͎擾
	cout << "a:left s:right w:up z:down. command?" << endl; //�������
	char input;
	cin >> input;
	//�I������
	if ( input == 'q' ){
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//�X�V
	gState->update( input );
	//�`��
	gState->draw();
}


