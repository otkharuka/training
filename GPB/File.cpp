#include "File.h"
#include <fstream>
using namespace std;

File::File( const char* filename ) : mSize( 0 ), mData( 0 ){
	ifstream in(filename, ifstream::binary);
	if (!in) {
		mData = 0;
		mSize = 0;
	}
	else {
		in.seekg(0, ifstream::end);
		mSize = static_cast< int >(in.tellg());
		in.seekg(0, ifstream::beg);
		mData = new char[mSize];
		in.read(mData, mSize);
		//cout.write(*buffer, *size);
	}
}

File::~File(){
	delete[] mData;
	mData = 0;
}

int File::size() const {
	return mSize;
}

char* File::data() const {
	return mData;
}

//unsigned char‚É‚Í‚¢‚Á‚Ä‚¢‚éî•ñ‚ğunsigned int ‚É•ÏŠ·‚·‚é
unsigned File::getUnsigned(const int p) const {
	const unsigned char* up = reinterpret_cast<const unsigned char*> (&mData[p]);
	unsigned ret = 0;
	ret |= (up[0] << 0);
	ret |= (up[1] << 8);
	ret |= (up[2] << 16);
	ret |= (up[3] << 24);
	return ret;
}