#include "File.h"
#include <fstream>
using namespace std;

File::File(const char* filename) {
	ifstream in(filename, ifstream::binary);
	if (!in) {
		mBuffer = 0;
		mSize = 0;
	}
	else {
		in.seekg(0, ifstream::end);
		mSize = static_cast< int >(in.tellg());
		in.seekg(0, ifstream::beg);
		mBuffer = new char[mSize];
		in.read(mBuffer, mSize);
		//cout.write(*buffer, *size);
	}
}

File::~File() {
	delete[] mBuffer;
	mBuffer = 0;
}

char* File::setData() const { return mBuffer; }
int File::setSize() const { return mSize; }

//unsigned char‚É‚Í‚¢‚Á‚Ä‚¢‚éî•ñ‚ğunsigned int ‚É•ÏŠ·‚·‚é
/*unsigned File::getUnsigned(const int p) const {
	const unsigned char* up = reinterpret_cast<const unsigned char*> (&mBuffer[p]);
	unsigned ret = 0;
	ret |= (up[0] << 0);
	ret |= (up[1] << 8);
	ret |= (up[2] << 16);
	ret |= (up[3] << 24);
	return ret;
}*/
unsigned File::getUnsigned(int p) const {
	const unsigned char* up;
	up = reinterpret_cast< const unsigned char* >(mBuffer);
	unsigned r = up[p];
	r |= up[p + 1] << 8;
	r |= up[p + 2] << 16;
	r |= up[p + 3] << 24;
	return r;
}