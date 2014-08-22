/*
* Author: Shao Yingxia
* Create Date: 2012年12月10日 星期一 11时15分04秒
*/

#include <util/filesplitor.h>
#include <util/logger.h>
#include <util/assert.h>
#include <math.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


/*
 * the default minsplitssize = 10M
 */
FileSplitor::FileSplitor(string graphpath, int numberofsplits, addr_t minsplitsize)
    :graphpath_(graphpath), numofsplits_(numberofsplits),
    minsplitsize_(minsplitsize) {

}

FileSplitor::~FileSplitor() {
    int i;
    for(i = 0; i < fsp_.size(); i++)
        delete fsp_[i];
    fsp_.clear();
}

FileSplitArray 
FileSplitor::get_filesplits() {
    struct stat info;
    vector<string> files;
    int i;
    addr_t totalsize; //in bytes

    fsp_.clear();
    
    //1. prepare files need to be splited
    if(stat(graphpath_.c_str(), &info)) {
        Logger(LOG_FATAL,"Failed to stat %s\n", graphpath_.c_str());
        return fsp_; //empty fsp
    }

    if(S_ISDIR(info.st_mode)) {
        DIR* dp = opendir(graphpath_.c_str());
        struct dirent* dc; //directory's contains
        string file;
        while((dc = readdir(dp)) != NULL) {
            if(dc->d_name[0] == '.') {
                continue;
            }
            file = graphpath_;
            if(file.find_last_of("/") != (file.length() -1))
                file += "/";
            file+= dc->d_name;
            files.push_back(file);
//            logger(LOG_DEBUG, "File \"%s\" in \"%s\" dir.\n", file.c_str(), graphpath.c_str());
        }
    }
    else {
        ASSERT4(S_ISREG(info.st_mode));
        files.push_back(graphpath_);
        Logger(LOG_DEBUG, "Single file %s.\n", graphpath_.c_str());
    }

    //2. get the total size of graph
    totalsize=0;
    for(i = 0; i < files.size(); i++) {
        stat(files[i].c_str(), &info);
        totalsize += info.st_size;
//        logger(LOG_DEBUG, "file \"%s\" size=%ld\n", files[i].c_str(), info.st_size);
    }

    //3. generate splits
    addr_t goalsize = max(totalsize / numofsplits_, minsplitsize_);
    addr_t remainbytes, length;

    Logger(LOG_INFO, "Split graph[totalsize=%lld] into %d small graph[%lld]\n", totalsize, numofsplits_, goalsize);
    for(i = 0; i < files.size(); i++) {
        stat(files[i].c_str(), &info);
        remainbytes = length = info.st_size;
        if(length == 0) continue;
        while(remainbytes > goalsize) {
            fsp_.push_back(new FileSplit(length - remainbytes, goalsize, files[i]));
           // fsp.push_back(filesplit(length - remainbytes, goalsize, files[i]));
            remainbytes -= goalsize;
        }
        if(remainbytes)
            fsp_.push_back(new FileSplit(length - remainbytes, remainbytes, files[i]));
    }
    return fsp_;
}

