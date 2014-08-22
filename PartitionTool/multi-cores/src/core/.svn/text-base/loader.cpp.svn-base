/*
* Author: Shao Yingxia
* Create Date: 2012年12月09日 星期日 23时37分13秒
*/
#include <core/loader.h>
#include <util/logger.h>
#include <util/time.h>
#include <util/assert.h>
#include <util/filereader.h>

Loader::Loader(int id, cpu_set_t cpu_set)
	:GenericThread(id), format_("adj"), cpuset_(cpu_set),fr_(NULL) {
        inputfiles_.clear();
}

Loader::~Loader() {
    if(fr_ != NULL) {
        delete fr_;
        fr_ = NULL;
    }
}

void
Loader::BeforeRun() {
	if(pthread_setaffinity_np(get_thread(), sizeof(cpu_set_t), &cpuset_) == -1){
		Logger(LOG_WARNING, "Failed to set affintiy of loader %lud\n", get_thread());
	}

	Logger(LOG_DEBUG, "loader %d is successsful to set affinity.\n", get_id());
    //1. parepare: open input file and get reader
    fr_ = new FileReader(inputfiles_);
}

void
Loader::Run() {
    Logger(LOG_DEBUG, "In run......\n");
	Time timer;
    string line;
    long long count = 0;
	timer.Start();
    while(fr_->HasNext()) {
        line = fr_->NextLine();
       // LineParser(line);
        count++;
		/*
        if(count==1)
            Logger(LOG_INFO, "loader %d: Firstline= %s",get_id(), line.c_str()); 
		if(count % 100000000L == 0) 
            Logger(LOG_INFO, "loader %d: Read %lld lines", get_id(), count); 
			*/
    }
	timer.Stop();
    Logger(LOG_INFO, "loader %d: cost %lfs to loading data",get_id(), timer.GetElapsedTime()); 
   // Logger(LOG_INFO, "loader %d: Lastline= %s",get_id(), line.c_str()); 
    Logger(LOG_INFO,"loader %d read %lld lines.\n", get_id(), count);
}

void
Loader::AfterRun() {
    //logger(LOG_DEBUG, "In after_run ......\n");
}

void Loader::LineParser(string line) {
   //logger(LOG_INFO, "loader %d: %s",get_id(), line.c_str()); 
}

void Loader::set_format(string datafmt) {
	format_ = datafmt;
}
