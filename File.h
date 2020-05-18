#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

class File {
public:
	File(const char* filename);
	~File();
	//メンバ変数を取得するだけの関数（変更しない）からうしろにconstをつける
	char* setData() const;
	int setSize() const;
	unsigned getUnsigned(const int p) const;
	
private:
	char* mBuffer;
	int mSize;
	
};

#endif
