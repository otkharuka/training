#pragma once
class File {
public:
	File(const char* filename);
	~File();
	//メンバ変数を取得するだけの関数（変更しない）からうしろにconstをつける
	char* setData() const;
	int setSize() const;
	
private:
	char* mBuffer;
	int mSize;

};

