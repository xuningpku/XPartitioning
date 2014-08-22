/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月11日 星期二 10时48分21秒
 */
#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <vector>
#include <iostream>
//#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <util/filesplit.h>

using namespace std;

class FileReader {
    public:
        FileReader(FileSplitArray fsp);
        ~FileReader();

        bool HasNext();
        string NextLine();

    private:
        void InitFileOffset(int fidx);

    private:
        FileSplitArray fsp_;
        int filenum_;
//        ifstream fout;
        FILE* fp_;        
		int fileidx_;
        addr_t offset_;
        addr_t remain_;
};

#endif    // #ifndef __FILEREADER_H__

