/*
* Author: Shao Yingxia
* Create Date: 2012年12月10日 星期一 10时21分19秒
*/
#ifndef __GRAPHKINFE_H__
#define __GRAPHKINFE_H__

#include <core/loader.h>
#include <util/filesplitor.h>
#include <vector>
#include <string>

using namespace std;

class GraphKinfe
{
    public:
        GraphKinfe(int argc, char** args);
        ~GraphKinfe();
        void Start();
        void Usage();
/*
        void set_graphpath(string path) { graphpath = path ; }
        string get_graphpath() { return graphpath; }
*/
    private:
        void Init(int agrc, char** args);
        bool InitLoaders();
        bool ProcessOptions(int argc, char** args);
        void LoadersJoin();

    private:
        int nloader_; //number of loaders, i.e the degree of parallelism
        vector<Loader> loaders_;
        FileSplitor fsp_;
        string graphpath_;
		addr_t minsplitsize_;
        bool isready_;
};

#endif    // #ifndef __GRAPHKINFE_H__

