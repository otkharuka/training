#include "GameLib/Framework.h"
using namespace GameLib;

#include <fstream>
#include <algorithm>
using namespace std;


void readFile(char** buffer, int* size, const char* filename);
void drawCell(int x, int y, unsigned id);
unsigned getUnsigned(const char* p);
void mainLoop();


//�X�e�[�W�̊e�}�X�̏�Ԃ��i�[����
template< class T > class Array2D {
public:
	Array2D() : mArray(0) {}//�R���X�g���N�^��mArray=0�Ə����ݒ肷��
	~Array2D() {
		delete[] mArray;
		mArray = 0;  
	}
	void setSize(int size0, int size1) {
		mSize0 = size0;
		mSize1 = size1;
		mArray = new T[size0 * size1];
	}
	//Array2D(1, 3)�̏�������mArray�ɃA�N�Z�X�ł���
	T& operator()(int index0, int index1) {
		return mArray[index1 * mSize0 + index0];
	}
	const T& operator()(int index0, int index1) const {
		return mArray[index1 * mSize0 + index0];
	}
private:
	T* mArray;
	int mSize0;
	int mSize1;
};

//�e�}�X�̏�ԂɊւ���N���X
class State {
public:
	State(const char* stageData, int size);
	void update(char input);//�X�e�[�W�̊e�}�X�̏�Ԃ̌�i
	void draw() const;//�X�e�[�W�̊e�}�X�̏�Ԃ�ǂ݂Ƃ��ĉ摜���͂�
	bool hasCleared() const;//�N���A�������ǂ����̃`�F�b�N
private:
	enum Object {
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN,
		OBJ_GOAL = (1 << 7),
	};
	void setSize(const char* stageData, int size);//�X�e�[�W�̃T�C�Y��stageData����ǂݎ��

	int mWidth;
	int mHeight;
	Array2D< unsigned char > mObjects;//�X�e�[�W�̊e�}�X�̏�Ԃ��i�[
									 
};

//�摜�̓\��t���Ɋւ���N���X
class Image {
public:
	Image(const char* filename);
	~Image() {
		delete[] mData;
		mData = 0;
	}
	enum ImageId {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};
	void setSize(int width, int height) {
		mWidth = width;
		mHeight = height;
		mData = new unsigned[width * height];
	}
	void drawPictures(int dstX, int dstY, int srcX, int srcY);

private:
	int mWidth;
	int mHeight;
	unsigned* mData;
};

State* gState = 0;

void Framework::update() {
	mainLoop();
}

void mainLoop() {
	//�ŏ���1���[�v��
	if (!gState) {
		const char* filename = "stageData.txt";
		char* stageData;
		int fileSize;
		readFile(&stageData, &fileSize, filename);

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




//---------------------�ȉ��֐���`------------------------------------------

void readFile(char** buffer, int* size, const char* filename) {
	ifstream in(filename, ifstream::binary);
	if (!in) {
		*buffer = 0;
		*size = 0;
	}
	else {
		in.seekg(0, ifstream::end);
		*size = static_cast< int >(in.tellg());
		in.seekg(0, ifstream::beg);
		*buffer = new char[*size];
		in.read(*buffer, *size);
		//cout.write(*buffer, *size);
	}
}

//imageID=id�̉摜��(x,y)�ɂ͂�
void drawCell(int x, int y, unsigned id) {
	Image* image = 0;
	image = new Image("nimotsuKunImage.dds");
	image->drawPictures(x, y, 32 * id, 0);
}

//unsigned char�ɂ͂����Ă������unsigned int �ɕϊ�����
unsigned getUnsigned(const char* p) { 
	const unsigned char* up = reinterpret_cast<const unsigned char*> (p);
	unsigned ret = 0;
	ret |= (up[0] << 0);
	ret |= (up[1] << 8);
	ret |= (up[2] << 16);
	ret |= (up[3] << 24);
	return ret;
}

State::State(const char* stageData, int size) {
	//�T�C�Y����
	setSize(stageData, size);
	//�z��m��
	mObjects.setSize(mWidth, mHeight);
	//�����l�Ŗ��߂Ƃ�
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			mObjects(x, y) = OBJ_WALL; //���܂��������͕�
									   
		}
	}
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; ++i) {
		unsigned char t;

		switch (stageData[i]) {
		case '#': t = OBJ_WALL; break;
		case ' ': t = OBJ_SPACE; break;
		case 'o': t = OBJ_BLOCK; break;
		case 'O': t = OBJ_BLOCK | OBJ_GOAL; break;
		case '.': t = (OBJ_SPACE | OBJ_GOAL); break;
		case 'p': t = OBJ_MAN; break;
		case 'P': t = OBJ_MAN | OBJ_GOAL; break;
		case '\n': x = 0; ++y; t = OBJ_UNKNOWN; break; //���s����
		default: t = OBJ_UNKNOWN; break;
		}
		if (t != OBJ_UNKNOWN) { //�m��Ȃ������Ȃ疳������
			mObjects(x, y) = t; 
			++x;
		}
	}
}

void State::setSize(const char* stageData, int size) {
	mWidth = mHeight = 0;						 
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; ++i) {
		switch (stageData[i]) {
		case '#': case ' ': case 'o': case 'O':
		case '.': case 'p': case 'P':
			++x;
			break;
		case '\n':
			++y;
			//�ő�l�X�V
			mWidth = max(mWidth, x);
			mHeight = max(mHeight, y);
			x = 0;
			break;
		}
	}
}

void State::draw() const {

	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			unsigned char o = mObjects(x, y);
			unsigned id;
					
			switch (mObjects(x, y)) {
			case OBJ_SPACE | OBJ_GOAL: cout << '.'; id = Image::IMAGE_ID_GOAL;  break;
			case OBJ_WALL | OBJ_GOAL: cout << '#'; id = Image::IMAGE_ID_WALL; break;
			case OBJ_BLOCK | OBJ_GOAL: cout << 'O'; 'O'; id = Image::IMAGE_ID_BLOCK_ON_GOAL; break;
			case OBJ_MAN | OBJ_GOAL: cout << 'P'; 'P'; id = Image::IMAGE_ID_PLAYER; break;
			case OBJ_SPACE: cout << ' '; id = Image::IMAGE_ID_SPACE; break;
			case OBJ_WALL: cout << '#'; id = Image::IMAGE_ID_WALL; break;
			case OBJ_BLOCK: cout << 'o'; id = Image::IMAGE_ID_BLOCK; break;
			case OBJ_MAN: cout << 'p'; id = Image::IMAGE_ID_PLAYER; break;
			}

			drawCell(x*32, y*32, id);
		}
		cout << endl;
	}
}

void State::update(char input) {
	//�ړ������ɕϊ�
	int dx = 0;
	int dy = 0;
	switch (input) {
	case 'a': dx = -1; break; //��
	case 's': dx = 1; break; //�E
	case 'w': dy = -1; break; //��BY�͉����v���X
	case 'z': dy = 1; break; //���B
	}
	//�Z���ϐ���������B
	int w = mWidth;
	int h = mHeight;
	Array2D< unsigned char >& o = mObjects;
	//�l���W������
	int x, y;
	x = y = -1; //�댯�Ȓl
	bool found = false;
	for (y = 0; y < mHeight; ++y) {
		for (x = 0; x < mWidth; ++x) {
			if ((o(x, y) & ~OBJ_GOAL) == OBJ_MAN) {
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}
	//�ړ�
	//�ړ�����W
	int tx = x + dx;
	int ty = y + dy;
	//���W�̍ő�ŏ��`�F�b�N�B�O��Ă���Εs����
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;

	}
	//A.���̕������󔒂܂��̓S�[���B�l���ړ��B
	if ((o(tx, ty) & ~OBJ_GOAL) == OBJ_SPACE) {
		o(tx, ty) = (o(tx, ty) & OBJ_GOAL) | OBJ_MAN;
		o(x, y) = (o(x, y) & OBJ_GOAL) | OBJ_SPACE;
		//B.���̕��������B���̕����̎��̃}�X���󔒂܂��̓S�[���ł���Έړ��B
	}
	else if ((o(tx, ty) & ~OBJ_GOAL) == OBJ_BLOCK) {
		//2�}�X�悪�͈͓����`�F�b�N
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) { //�����Ȃ�
			return;
		}
		if ((o(tx2, ty2) & ~OBJ_GOAL) == OBJ_SPACE) {
			//��������ւ�
			o(tx2, ty2) = (o(tx2, ty2) & OBJ_GOAL) | OBJ_BLOCK;
			o(tx, ty) = (o(tx, ty) & OBJ_GOAL) | OBJ_MAN;
			o(x, y) = (o(x, y) & OBJ_GOAL) | OBJ_SPACE;
		}
	}
}

//�u���b�N�̂Ƃ����goalFlag����ł�false�Ȃ�
//�܂��N���A���ĂȂ�
bool State::hasCleared() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			if (mObjects(x, y) == OBJ_BLOCK) return false;
		}
	}
	return true;
}


Image::Image(const char* filename) {

	char* buffer = 0;
	int imageSize = 0;
	readFile(&buffer, &imageSize, filename);
	setSize(getUnsigned(&(buffer[16])), getUnsigned(&(buffer[12])));

	if (!buffer) {
		cout << "image file could not be read." << endl;
		return;
	}
	if (imageSize != 128 + mHeight * mWidth * 4) {
		cout << "image file is broken." << endl;
		return;
		//������return����Ȃ��ăv���O�����I���ɂ��Ȃ��Ǝ��̃��[�v�ŃA�N�Z�X�ᔽ���ł�
	}

	for (unsigned i = 0; i < mHeight * mWidth; i++) {
		mData[i] = getUnsigned(&buffer[128 + i * 4]);
	}
}

//��ʏ�̍��W(dstX, dstY)�ɁA����[�̍��W��(srcX, srcY)�̉摜���͂�
void Image::drawPictures(int dstX, int dstY, int srcX, int srcY) {
	unsigned* vram = Framework::instance().videoMemory(); //��f��4byte�̕��ɂȂ�Ȃ����ŕ\��
	unsigned windowWidth = Framework::instance().width();

	for (unsigned y = 0; y < 32; y++) {
		for (unsigned x = 0; x < 32; x++) {
			vram[(dstX + x) + (dstY + y) * windowWidth] = mData[(srcX + x) + (srcY + y) * mWidth]; //vram�ɂ����update()�I����ɕ`�悳���
		}
	}
}

