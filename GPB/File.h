#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

class File{
public:
   File( const char* filename );
   ~File();
   //�����o�ϐ����擾���邾���̊֐��i�ύX���Ȃ��j���炤�����const������
   int size() const;
   char* data() const;
   unsigned getUnsigned( int p) const;
private:
   int mSize;
   char* mData;
};

#endif
