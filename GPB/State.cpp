#include "State.h"
#include "Image.h"

//オブジェクトクラス
class State::Object{
public:
	enum Type{
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN,
		OBJ_GOAL = (1 << 7),
	};
	//マス描画関数
	enum ImageID{
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};
	Object() : mType( OBJ_WALL ), mGoalFlag( false ), mMoveX( 0 ), mMoveY( 0 ){}
	//ステージデータの文字で自分を初期化
	void set( char c ){
		switch ( c ){
			case '#': mType = OBJ_WALL; break;
			case ' ': mType = OBJ_SPACE; break;
			case 'o': mType = OBJ_BLOCK; break;
			case 'O': mType = static_cast<Type>((OBJ_BLOCK | OBJ_GOAL)); break;
			case '.': mType = static_cast<Type>((OBJ_SPACE | OBJ_GOAL)); break;
			case 'p': mType = OBJ_MAN; break;
			case 'P': mType = static_cast<Type>(OBJ_MAN | OBJ_GOAL); break;
		}
	}
	//背景描画
	void drawBackground( int x, int y, const Image* image ) const {
		ImageID id = IMAGE_ID_SPACE;

		switch (mType) {
		case OBJ_SPACE | OBJ_GOAL: id = IMAGE_ID_GOAL;  break;
		case OBJ_WALL | OBJ_GOAL:  id = IMAGE_ID_WALL; break;
		case OBJ_SPACE: id = IMAGE_ID_SPACE; break;
		case OBJ_WALL: id = IMAGE_ID_WALL; break;
		}
		image->draw(x * 32, y * 32, id * 32, 0);
	}
	//動くもの描画
	void drawForeground( int x, int y, const Image* image, int moveCount ) const {
	
		ImageID id = IMAGE_ID_SPACE; 
	
		switch (mType) {
		case OBJ_BLOCK | OBJ_GOAL: id = IMAGE_ID_BLOCK_ON_GOAL; break;
		case OBJ_MAN | OBJ_GOAL:  id = IMAGE_ID_PLAYER; break;
		case OBJ_BLOCK:  id = IMAGE_ID_BLOCK; break;
		case OBJ_MAN:  id = IMAGE_ID_PLAYER; break;
		}
		if (id != IMAGE_ID_SPACE) { //背景以外なら
									//移動を計算
			int dx = mMoveX * (32 - moveCount);
			int dy = mMoveY * (32 - moveCount);
			image->draw(x * 32 - dx, y * 32 - dy, id * 32, 0);
		}
	}

	//移動をセット
	void move( int dx, int dy, Type replaced ){
		mMoveX = dx;
		mMoveY = dy;
		mType = static_cast<Type>((mType & OBJ_GOAL) | replaced);
	}

	Type mType;
	bool mGoalFlag;
	int mMoveX;
	int mMoveY;
};

State::State( const char* stageData, int size ) : mImage( 0 ),mMoveCount( 0 ){	
	//サイズ測定
	setSize( stageData, size );
	//配列確保
	mObjects.setSize( mWidth, mHeight );
	//ステージ初期設定
	int x = 0;
	int y = 0;

	for (int i = 0; i < size; ++i) {
		switch (stageData[i]) {
		case '#':
		case ' ':
		case 'o':
		case 'O':
		case '.':
		case 'p':
		case 'P':
			mObjects(x, y).set(stageData[i]);
			x++;
			break;
		case '\n':
			x = 0;
			y++;
			break;
		}
	}
	//画像読み込み
	mImage = new Image( "nimotsuKunImage.dds" );
}

State::~State(){
	delete mImage;
	mImage = 0;
}

void State::setSize( const char* stageData, int size ){
	const char* d = stageData; //読み込みポインタ
	mWidth = mHeight = 0; //初期化
	//現在位置
	int x = 0;
	int y = 0;
	for ( int i = 0; i < size; ++i ){
		switch ( stageData[ i ] ){
			case '#': case ' ': case 'o': case 'O':
			case '.': case 'p': case 'P':
				++x;
				break;
			case '\n': 
				++y;
				//最大値更新
				mWidth = ( mWidth > x ) ? mWidth : x;
				mHeight = ( mHeight > y ) ? mHeight : y;
				x = 0; 
				break;
		}
	}
}

void State::draw() const {
	
	for ( int y = 0; y < mHeight; ++y ){
		for ( int x = 0; x < mWidth; ++x ){
			mObjects( x, y ).drawBackground( x, y, mImage );
		}
	}
	for ( int y = 0; y < mHeight; ++y ){
		for ( int x = 0; x < mWidth; ++x ){
			mObjects( x, y ).drawForeground( x, y, mImage, mMoveCount );
		}
	}
}

void State::update( int dx, int dy ){
	//移動中カウントが32に達したら
	if ( mMoveCount == 32 ){
		mMoveCount = 0; //巻き戻して、
		//移動を初期化
		for ( int y = 0; y < mHeight; ++y ){
			for ( int x = 0; x < mWidth; ++x ){
				mObjects( x, y ).mMoveX = 0;
				mObjects( x, y ).mMoveY = 0;
			}
		}
	}
	//移動中は更新しない。
	if ( mMoveCount > 0 ){
		++mMoveCount;
		return;
	}
	//短い変数名をつける。
	int w = mWidth;
	int h = mHeight;
	Array2D< Object >& o = mObjects;
	//人座標を検索
	int x, y;
	bool found = false;
	for ( y = 0; y < mHeight; ++y ){
		for ( x = 0; x < mWidth; ++x ){
			if ( o( x, y ).mType == Object::OBJ_MAN ){
				found = true;
				break;
			}
		}
		if ( found ){
			break;
		}
	}
	//移動
	//移動後座標
	int tx = x + dx;
	int ty = y + dy;
	//座標の最大最小チェック。外れていれば不許可
	if ( tx < 0 || ty < 0 || tx >= w || ty >= h ){
		return;
	}
	//A.その方向が空白またはゴール。人が移動。
	if ((o(tx, ty).mType & ~Object::OBJ_GOAL) == Object::OBJ_SPACE){
		o( tx, ty ).move( dx, dy, Object::OBJ_MAN );
		o( x, y ).move( dx, dy, Object::OBJ_SPACE );
		mMoveCount = 1; //移動開始
	//B.その方向が箱。その方向の次のマスが空白またはゴールであれば移動。
	}else if ((o(tx, ty).mType & ~Object::OBJ_GOAL) == Object::OBJ_BLOCK){
		//2マス先が範囲内かチェック
		int tx2 = tx + dx;
		int ty2 = ty + dy; 
		if ( tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h ){ //押せない
			return;
		}
		if ((o(tx2, ty2).mType & ~Object::OBJ_GOAL) == Object::OBJ_SPACE){
			//順次入れ替え
			o( tx2, ty2 ).move( dx, dy, Object::OBJ_BLOCK );
			o( tx, ty ).move( dx, dy, Object::OBJ_MAN );
			o( x, y ).move( dx, dy, Object::OBJ_SPACE );
			mMoveCount = 1; //移動開始
		}
	}
}


bool State::hasCleared() const {
	for ( int y = 0; y < mHeight; ++y ){
		for ( int x = 0; x < mWidth; ++x ){
			//ゴールにのってないブロックが一つでもあればfalseを返す
			if (mObjects(x, y).mType == Object::OBJ_BLOCK) return false;
		}
	}
	return true;
}
