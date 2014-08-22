/*
* Author: Shao Yingxia
* Create Date: 2012年12月10日 星期一 10时18分08秒
*
*/

#include <core/graphkinfe.h>
#include <util/logger.h>
#include <util/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GraphKinfe::GraphKinfe(int argc, char** args) {
    Init(argc, args);
}

GraphKinfe::~GraphKinfe() { 
/*    int i;
    for(i = 0; i < loaders.size(); i++) {
        if(loaders[i] != NULL)
        {
            delete loaders[i];
            loaders[i] = null;
        }
    }*/
}

void 
GraphKinfe::Usage() {
    printf("App Usage:\n");
    printf("\t-n  <num>, number of loaders.\n");
    printf("\t-g  <path>, file or directory path of graph.\n");
    printf("\t-sp <num>, the minimum split size(KB).\n");
}

void 
GraphKinfe::Start() {
    if(isready_ == false) {
        Logger(LOG_WARNING, "Failed to be ready!\n");
        return ;
    }

    int i;
    for(i = 0; i < loaders_.size(); i++) {
        loaders_[i].Start();
    }

    LoadersJoin();
}

void
GraphKinfe::LoadersJoin() {
    int i;
    for(i = 0; i < loaders_.size(); i++) {
        loaders_[i].Join();
    }
    return;
}

void GraphKinfe::Init(int argc, char** args) {
	Time timer;
    //1. process the optitions
    if((isready_ = ProcessOptions(argc, args)) == false)
        return ;

	timer.Start();
    //2. split graph data
    Logger(LOG_DEBUG, "Processing file split\n");
    fsp_ = FileSplitor(graphpath_, nloader_, minsplitsize_);
	timer.Stop();
	Logger(LOG_INFO,"Split graph costs %lfs\n", timer.GetElapsedTime());

    //3. initial loader
	timer.Start();
    Logger(LOG_DEBUG, "initialze loader.\n");
    isready_ = InitLoaders();
	timer.Stop();
	Logger(LOG_INFO,"Init Loaders costs %lfs\n", timer.GetElapsedTime());

}

bool
GraphKinfe::ProcessOptions(int argc, char** args) {
    nloader_ = 1;
    graphpath_ = "";
    isready_ = false;
    minsplitsize_ = 10485760; //10M
    
    //1. process the optitions
    int i;
    for(i = 1; i < argc; i++)
    {
        if(strcmp(args[i], "-n") == 0 && i + 1 < argc) {
            nloader_ = atoi(args[++i]);
        }
        else if(strcmp(args[i], "-g") == 0 && i + 1 < argc) {
            graphpath_ = string(args[++i]);
        }
        else if(strcmp(args[i], "-sp") == 0 && i + 1 < argc) {
            minsplitsize_ = atoi(args[++i]) * 1024;
        }
        else
        {
            Usage();
            return false;
        }
    }

    if(graphpath_.length() == 0 || nloader_ < 1)
    {
        Usage();
        return false;
    }
    Logger(LOG_DEBUG, "Options:\n\tgraphpath=%s\n\tnloader=%d\n\tminsplitsize=%lld\n",graphpath_.c_str(),nloader_, minsplitsize_);
    return true;
}

bool 
GraphKinfe::InitLoaders() {
   int i;
   //1. get system info
   //here we force the thread assign to specific cpu.
   int cpunum = sysconf(_SC_NPROCESSORS_CONF);
   int curidx = 0;
  
   Logger(LOG_DEBUG, "Total CPU number: %d\n", cpunum);
   //2. create loaders
   for(i = 0; i < nloader_; i++) {
       cpu_set_t cpuset;
       CPU_ZERO(&cpuset);
       CPU_SET(curidx % cpunum, &cpuset); //round-robin
       loaders_.push_back(Loader(i, cpuset));
       curidx++;
   }

   //3. distribute file splits
   FileSplitArray fsparray = fsp_.get_filesplits();
   int stepsize = fsparray.size() / nloader_;
   int remain = fsparray.size() % nloader_;

   int idx=0, qurum = stepsize + (remain?1:0);
   remain--;
  
  // logger(LOG_DEBUG, "filesplit number=%u, stepsize=%d\n", fsparray.size(), stepsize);
   for(i = fsparray.size()-1; i >= 0; i--) {
       Logger(LOG_DEBUG, "insert %d filesplit into %d loader\n", i, idx);
       loaders_[idx].add_filesplit(fsparray[i]);
       qurum--;
       if(qurum == 0) {
           idx++;
           qurum = stepsize + (remain > 0?1:0);
           remain--;
       }
   }

   Logger(LOG_DEBUG, "Success passing init_loaders function\n");

   return true;
}
