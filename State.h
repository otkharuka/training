#ifndef INCLUDED_STATE_H
#define INCLUDED_STATE_H

#include "Array2D.h"
//各マスの状態に関するクラス

class Image;

class State {
public:
	State(const char* stageData, int size);
	~State();
	void update(char input);//ステージの各マスの状態の後進
	void draw() const;//ステージの各マスの状態を読みとって画像をはる
	bool hasCleared() const;//クリアしたかどうかのチェック
	
private:
	enum Object {
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN,
		OBJ_GOAL = (1 << 7),
	};
	enum ImageId {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};
	void setSize(const char* stageData, int size);//ステージのサイズをstageDataから読み取る
	//State::draw()からしかよばれないためprivate
	void drawCell(int x, int y, unsigned id) const;
	int mWidth;
	int mHeight;
	Array2D< unsigned char > mObjects;//ステージの各マスの状態を格納
	Image* mImage;

};

#endif