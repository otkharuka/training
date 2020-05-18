#ifndef INCLUDED_STATE_H
#define INCLUDED_STATE_H

#include "Array2D.h"
//�e�}�X�̏�ԂɊւ���N���X

class Image;

class State {
public:
	State(const char* stageData, int size);
	~State();
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
	enum ImageId {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};
	void setSize(const char* stageData, int size);//�X�e�[�W�̃T�C�Y��stageData����ǂݎ��
	//State::draw()���炵����΂�Ȃ�����private
	void drawCell(int x, int y, unsigned id) const;
	int mWidth;
	int mHeight;
	Array2D< unsigned char > mObjects;//�X�e�[�W�̊e�}�X�̏�Ԃ��i�[
	Image* mImage;

};

#endif