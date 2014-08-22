/*
 * Loader is a single thread that is repsonsible
 * for reading sub-graph from file and distributing
 * to a partition based on partition algorithm
 *
* Author: Shao Yingxia
* Create Date: 2012年12月09日 星期日 23时38分23秒
*/
#ifndef __LOADER_H__
#define __LOADER_H__

#include <string>
#include <vector>
#include <sched.h>

#include <util/filesplit.h>
#include <util/filereader.h>
#include <util/genericthread.h>
//#include <core/partitioner.h>

using namespace std;

class Loader: public GenericThread
{
	public:
		/*basic funtion of loader*/
		Loader(int id, cpu_set_t cpu_set);
		~Loader(); //need to close file
        virtual void BeforeRun();
        virtual void Run();
        virtual void AfterRun();
		/*function of parser*/
		virtual void LineParser(string line);
				

        void add_filesplit(FileSplit* fs) {
            //logger(LOG_DEBUG,"Input filesplit: %s\n", fs.tostring().c_str());
            inputfiles_.push_back(fs);
        }																	
		void set_format(string datafmt);

	private:
		cpu_set_t cpuset_;
		FileSplitArray inputfiles_;
		string format_; //default is adj.
        FileReader* fr_;

 //       Partitioner part_;
};

#endif    // #ifndef __LOADER_H__

