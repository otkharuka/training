#pragma once
class File {
public:
	File(const char* filename);
	~File();
	//�����o�ϐ����擾���邾���̊֐��i�ύX���Ȃ��j���炤�����const������
	char* setData() const;
	int setSize() const;
	
private:
	char* mBuffer;
	int mSize;

};

