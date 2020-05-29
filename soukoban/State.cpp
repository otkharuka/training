#include "State.h"
#include "Image.h"

//�I�u�W�F�N�g�N���X
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
	//�}�X�`��֐�
	enum ImageID{
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};
	Object() : mType( OBJ_WALL ), mGoalFlag( false ), mMoveX( 0 ), mMoveY( 0 ){}
	//�X�e�[�W�f�[�^�̕����Ŏ�����������
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
	//�w�i�`��
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
	//�������̕`��
	void drawForeground( int x, int y, const Image* image, int moveCount ) const {
	
		ImageID id = IMAGE_ID_SPACE; 
	
		switch (mType) {
		case OBJ_BLOCK | OBJ_GOAL: id = IMAGE_ID_BLOCK_ON_GOAL; break;
		case OBJ_MAN | OBJ_GOAL:  id = IMAGE_ID_PLAYER; break;
		case OBJ_BLOCK:  id = IMAGE_ID_BLOCK; break;
		case OBJ_MAN:  id = IMAGE_ID_PLAYER; break;
		}
		if (id != IMAGE_ID_SPACE) { //�w�i�ȊO�Ȃ�
									//�ړ����v�Z
			int dx = mMoveX * (32 - moveCount);
			int dy = mMoveY * (32 - moveCount);
			image->draw(x * 32 - dx, y * 32 - dy, id * 32, 0);
		}
	}

	//�ړ����Z�b�g
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
	//�T�C�Y����
	setSize( stageData, size );
	//�z��m��
	mObjects.setSize( mWidth, mHeight );
	//�X�e�[�W�����ݒ�
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
	//�摜�ǂݍ���
	mImage = new Image( "nimotsuKunImage.dds" );
}

State::~State(){
	delete mImage;
	mImage = 0;
}

void State::setSize( const char* stageData, int size ){
	const char* d = stageData; //�ǂݍ��݃|�C���^
	mWidth = mHeight = 0; //������
	//���݈ʒu
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
				//�ő�l�X�V
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
	//�ړ����J�E���g��32�ɒB������
	if ( mMoveCount == 32 ){
		mMoveCount = 0; //�����߂��āA
		//�ړ���������
		for ( int y = 0; y < mHeight; ++y ){
			for ( int x = 0; x < mWidth; ++x ){
				mObjects( x, y ).mMoveX = 0;
				mObjects( x, y ).mMoveY = 0;
			}
		}
	}
	//�ړ����͍X�V���Ȃ��B
	if ( mMoveCount > 0 ){
		++mMoveCount;
		return;
	}
	//�Z���ϐ���������B
	int w = mWidth;
	int h = mHeight;
	Array2D< Object >& o = mObjects;
	//�l���W������
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
	//�ړ�
	//�ړ�����W
	int tx = x + dx;
	int ty = y + dy;
	//���W�̍ő�ŏ��`�F�b�N�B�O��Ă���Εs����
	if ( tx < 0 || ty < 0 || tx >= w || ty >= h ){
		return;
	}
	//A.���̕������󔒂܂��̓S�[���B�l���ړ��B
	if ((o(tx, ty).mType & ~Object::OBJ_GOAL) == Object::OBJ_SPACE){
		o( tx, ty ).move( dx, dy, Object::OBJ_MAN );
		o( x, y ).move( dx, dy, Object::OBJ_SPACE );
		mMoveCount = 1; //�ړ��J�n
	//B.���̕��������B���̕����̎��̃}�X���󔒂܂��̓S�[���ł���Έړ��B
	}else if ((o(tx, ty).mType & ~Object::OBJ_GOAL) == Object::OBJ_BLOCK){
		//2�}�X�悪�͈͓����`�F�b�N
		int tx2 = tx + dx;
		int ty2 = ty + dy; 
		if ( tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h ){ //�����Ȃ�
			return;
		}
		if ((o(tx2, ty2).mType & ~Object::OBJ_GOAL) == Object::OBJ_SPACE){
			//��������ւ�
			o( tx2, ty2 ).move( dx, dy, Object::OBJ_BLOCK );
			o( tx, ty ).move( dx, dy, Object::OBJ_MAN );
			o( x, y ).move( dx, dy, Object::OBJ_SPACE );
			mMoveCount = 1; //�ړ��J�n
		}
	}
}


bool State::hasCleared() const {
	for ( int y = 0; y < mHeight; ++y ){
		for ( int x = 0; x < mWidth; ++x ){
			//�S�[���ɂ̂��ĂȂ��u���b�N����ł������false��Ԃ�
			if (mObjects(x, y).mType == Object::OBJ_BLOCK) return false;
		}
	}
	return true;
}
