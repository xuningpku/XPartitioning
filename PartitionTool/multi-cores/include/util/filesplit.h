/*
* Author: Shao Yingxia
* Create Date: 2012年12月10日 星期一 11时08分53秒
*/
#ifndef __FILESPLIT_H__
#define __FILESPLIT_H__

#include <string>
#include <sstream>
#include <util/logger.h>

using namespace std;

typedef long long addr_t;

/**
 * The filesplit contains information of a block for the 
 * graph file.
 */
class FileSplit
{
    public:
        FileSplit(addr_t start, addr_t length, string path)
            :start_(start), length_(length), gfile_(path) {
                Logger(LOG_DEBUG, "Split: %s\n", toString().c_str());
        }

        ~FileSplit() {}

        addr_t get_start() { return start_; }
        addr_t get_length() { return length_; }
        string get_filepath() { return gfile_; }

        string toString() {
            stringstream oss;
            oss << "start="<<start_<<" end="<<(start_+length_)<<" in file: "<<
                gfile_;
            return oss.str();
        }

    private:
       addr_t start_;
       addr_t length_;
       string gfile_;
        
};

typedef vector<FileSplit*> FileSplitArray;

#endif    // #ifndef __FILESPLIT_H__

