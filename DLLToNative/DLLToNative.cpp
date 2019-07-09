// DLLToNative.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"

using namespace std;

static char * ReadAllBytes(const char * filename, int * read)
{
	ifstream ifs(filename, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	int length = pos;

	char *pChars = new char[length];
	ifs.seekg(0, ios::beg);
	ifs.read(pChars, length);


	ifs.close();
	*read = length;
	return pChars;
}

static void outHeaderFile(const char* src, int size, int oriSize)
{
	byte* buf = new byte[size];
	memcpy_s(buf, size, src, size);

	ofstream fout("../FontChangeLib/FontChangeBIN.h");

	fout << "#pragma once" << endl << endl
		 << "static int orignalSize = " << oriSize << ";" << endl
		 << "static char FontChangeDLL[] = {" << endl
		 << "\t";

	for (int i = 0; i < size; i++)
	{
		char tmp[5];
		snprintf(tmp, sizeof(tmp), "0x%X", buf[i]);
		fout << tmp;

		if (i == size - 1) {
			fout << endl << "};";
			break;
		}

		fout << ", ";
		if (!(i % 20))
			fout << endl << "\t";
	}

	delete[] buf;
	fout.close();
}

int main()
{
	int length;
	char *buf = ReadAllBytes("FontChangeCore.dll", &length);

	int dstLength = LZ4_compressBound(length);
	char* dstbuf = new char[dstLength];

	int compressionSize = LZ4_compress_HC(buf, dstbuf, length, dstLength, LZ4HC_CLEVEL_DEFAULT);
	
	outHeaderFile(dstbuf, compressionSize, length);

	delete[] buf;
	delete[] dstbuf;
    return 0;
}

