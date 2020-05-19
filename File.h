#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

class File{
public:
   File( const char* filename );
   ~File();
   //メンバ変数を取得するだけの関数（変更しない）からうしろにconstをつける
   int size() const;
   char* data() const;
   unsigned getUnsigned( int p) const;
private:
   int mSize;
   char* mData;
};

#endif
