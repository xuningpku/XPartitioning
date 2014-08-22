/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月11日 星期二 10时54分33秒
 */

#include <util/filereader.h>
#include <util/assert.h>
#include <sstream>
#include <cstring>

FileReader::FileReader(FileSplitArray fsp) {
   fsp_ = fsp;
   filenum_ = fsp.size();
   fileidx_ = 0;
   remain_ = 0;
   fp_ = NULL;
   InitFileOffset(fileidx_);
}

FileReader::~FileReader() {
    if(fp_) {
        fclose(fp_);
        fp_ = NULL;
    }
}

bool
FileReader::HasNext() {
    return (remain_ > 0);
}

string
FileReader::NextLine() {
    char linebuf[1024]="\0";
    int length; 
//    stringstream oss;
    //do {
        //if( fgets(linebuf, 1024, fp_) == NULL ) break;
        fgets(linebuf, 1024, fp_);
        length = strlen(linebuf);
        remain_ -= length;
 //       oss << linebuf;
   // }while(length == 1024 && linebuf[length-1] != '\n' && remain_ > 0);

    if(remain_ == 0 && fileidx_ + 1 < filenum_){
        fileidx_++;
        InitFileOffset(fileidx_);
    }
    return string(linebuf);
}

void
FileReader::InitFileOffset(int _fidx) {
    if(filenum_ == 0) return ;
	bool isok = false;
	int fidx = _fidx - 1;
	do{
		fidx++;
		FileSplit* fs = fsp_[fidx];
		string file = fs->get_filepath();
		offset_ = fs->get_start();
		remain_ = fs->get_length();
		fileidx_ = fidx;
		Logger(LOG_DEBUG, "Initial Filesplit [%d/%d]: offset=%lld, length=%lld, name=%s\n", fidx, filenum_, offset_, remain_, file.c_str());
		if(fp_) {
			fclose(fp_);
			fp_=NULL;
		}
		fp_ = fopen(file.c_str(), "r");
		Logger(LOG_DEBUG,"offset=%lld\n", offset_);
		if(offset_) {
			//skip a line
			char linebuf[1024]="\0";
			int length;

			fseek(fp_, offset_ - 1, SEEK_SET);
			if( fgetc(fp_) != '\n') {
				//do {
					//if(fgets(linebuf, 1024, fp_) == NULL) break;
					fgets(linebuf, 1024, fp_);
					length = strlen(linebuf);
					remain_ -= length;
					Logger(LOG_DEBUG, "In init: [length=%lld, remain=%lld] getline: %s",length, remain_, linebuf);
				// }while(length == 1024 && linebuf[length-1] != '\n' && remain_ > 0); 
			}
		}
		isok = this->HasNext();
	}while(!isok);
}

