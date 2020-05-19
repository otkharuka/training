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
		return; //そのまま終わる
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
	char input;
	cin >> input;
	//終了判定
	if ( input == 'q' ){
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//更新
	gState->update( input );
	//描画
	gState->draw();
}


