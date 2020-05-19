#include "GameLib/Framework.h"
using namespace GameLib;
using namespace std;

#include "State.h"
#include "File.h"

void mainLoop();

State* gState = 0;
bool gPrevInputS = false;
bool gPrevInputA = false;
bool gPrevInputW = false;
bool gPrevInputZ = false;

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
	//最初のフレーム	
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
		//初回描画
		gState->draw();
		return; 
	}
	bool cleared = false;
	//メインループ
	//クリアチェック
	if ( gState->hasCleared() ){
		cout << "Congratulation! you win." << endl;
		delete gState;
		gState = 0;
		return;
	}
	//入力取得
	cout << "a:left s:right w:up z:down. command?" << endl; //操作説明
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
	//終了判定
	if ( Framework::instance().isKeyOn('q')) {
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//更新
	gState->update(dx, dy);
	//描画
	gState->draw();
}


