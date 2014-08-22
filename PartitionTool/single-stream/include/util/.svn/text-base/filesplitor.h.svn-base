/*
* Author: Shao Yingxia
* Create Date: 2012年12月10日 星期一 11时12分15秒
*/
#ifndef __FILESPLITOR_H__
#define __FILESPLITOR_H__

#include <string>
#include <vector>
#include <util/filesplit.h>

using namespace std;

class FileSplitor
{
    public:
        /*
         * the default minsplitssize = 10M
         */
        FileSplitor() {} 
        FileSplitor(string graphpath, int numofsplits, addr_t minsplitsize=10485760);
        ~FileSplitor();

        FileSplitArray get_filesplits();

    private:
        string graphpath_;
        int numofsplits_;
        addr_t minsplitsize_;
        FileSplitArray fsp_;
};

#endif    // #ifndef __FILESPLITOR_H__

