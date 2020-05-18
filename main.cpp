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
	//最初の1ループめ
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

		//入力前の状態を一回描画する
		gState->draw();
		return;
	}

	//メインループ
	//入力取得
	cout << "a:left s:right w:up z:down. command?" << endl; //操作説明
	char input;
	cin >> input;
	gState->update(input);
	gState->draw();
	//クリアチェック
	if (gState->hasCleared()) {
		cout << "Congratulation's! you won." << endl;
		delete gState;
		gState = 0;
		return;
	}

	//終了判定
	if (input == 'q') {
		Framework::instance().requestEnd();
	}
	//×ボタン押されてる？
	if (Framework::instance().isEndRequested()) {
		if (gState) {
			delete gState;
			gState = 0;
		}
		return;
	}

}






