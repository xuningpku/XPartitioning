/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月11日 星期二 10时54分33秒
 */

#include <util/filereader.h>
#include <util/assert.h>
#include <util/logger.h>
#include <core/graphpartition.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;


FileReader::FileReader(StreamPartitioner& spart, string gpath, string fmt):
   partitioner_(spart), format_(fmt), gpath_(gpath){
	fp_ = fopen(gpath.c_str(), "r");
	if(fp_ == NULL) {
		Logger(LOG_FATAL, "Failed to open file %s", gpath.c_str());
	}
   	/* 
	struct stat info;

    //1. prepare files need to be processed
    if(stat(gpath_.c_str(), &info)) {
        Logger(LOG_FATAL,"Failed to stat %s\n", gpath_.c_str());
    }
	
    vector<string> files;
    
    if(S_ISDIR(info.st_mode)) {
        DIR* dp = opendir(gpath_.c_str());
        struct dirent* dc; //directory's contains
        string file;
        while((dc = readdir(dp)) != NULL) {
            if(dc->d_name[0] == '.') {
                continue;
            }
            file = gpath_;
            if(file.find_last_of("/") != (file.length() -1))
                file += "/";
            file+= dc->d_name;
            files.push_back(file);
        }
    }
    else {
        ASSERT4(S_ISREG(info.st_mode));
        files.push_back(gpath_);
        Logger(LOG_DEBUG, "Single file %s.\n", gpath_.c_str());
    }

    totalfiles_ = files.size();
   // fp_ = new FILE*[totalfiles_];

    //2. open files
    for(int i = 0; i < totalfiles_; i++) {
        Logger(LOG_DEBUG, "Open file %s.", files[i].c_str());
        FILE* fp = fopen(files[i].c_str(), "r");
        if(fp != NULL) {
            fp_.push_back(fp);
        }
        else 
            Logger(LOG_WARNING, "failed to open file %s", files[i].c_str());
    }
	*/
    Logger(LOG_DEBUG, "Pass Init");
}

FileReader::~FileReader() {
	fclose(fp_);
/*
    int i = 0;
    for(i = 0; i < totalfiles_; i++) {
        if(fp_[i])
            fclose(fp_[i]);
    }
	*/
}

void
FileReader::Start(bool haspartition) {
/*
    if(string("adj").compare(format_) == 0) {
        ReadFromAdjacency(haspartition);
    }
    else */if(string("elist").compare(format_) == 0) {
        ReadFromEdgeList(haspartition);
    }
    else {
        Logger(LOG_FATAL, "Unsupported File Format.\n");
    }
}

/*
bool
FileReader::HasNext() {
    return !feof(fp_);
}
*/

/*
 * TODO: Now Assume that a line is less than 1024 chars.
 */

 /*
string
FileReader::NextLine() {
    char linebuf[1024]="\0";
    
    while(fgets(linebuf, 1024, fp_[fileidx_]) == NULL) {
        if(!HasNext()) {
             if(fileidx_ + 1 < totalfiles_) fileidx_++;
             else break;
        }
    }

    if(!HasNext() && fileidx_ + 1 < totalfiles_) {
        fileidx_++;
    }
    return string(linebuf);
}
*/
/*
void
FileReader::ReadFromAdjacency(bool haspartition) {
    Logger(LOG_DEBUG, "In Edge Adj Reader");
    vid_t source, tmpv, nextsource;
    int degree = 0;
    int edgenum, vertexnum;
    vidarray targets;

    string line;
    while(HasNext()) {
        line = NextLine();
        if(line.empty()) continue;
        stringstream strm(line);
        strm >> source;
        while(strm.good()) {
            strm >> tmpv;
            if(strm.fail()) break;
            targets.push_back(tmpv);
            degree++;
            edgenum++;
        }
        vertexnum++;
        break;
    }

    while(HasNext()) {
        line = NextLine();
        if(line.empty()) continue;
        stringstream strm(line);
        strm >> nextsource;
        if(nextsource != source) {
            partitioner_.ProcessData(vertexnum, source, degree, targets, haspartition);
            degree = 0;
            source = nextsource;
            targets.clear();
            vertexnum++;
        }
    
        while(strm.good()) {
            strm >> tmpv;
            if(strm.fail()) break;
            targets.push_back(tmpv);
            degree++;
            edgenum++;
        }
    }
    //add last unit into partition
    partitioner_.ProcessData(vertexnum, source, degree, targets, haspartition); 
    targets.clear();
    Logger(LOG_DEBUG, "Vertex: %d Edge: %d\n", vertexnum, edgenum);
}
*/
void
FileReader::ReadFromEdgeList(bool haspartition) {
    Logger(LOG_DEBUG, "In Edge List Reader");
    int vertexnum = 0, edgenum =0;
	int totvertex, totedge;
    vid_t source, tmpv, nextsource;
    int degree = 0;
    vidarray targets;
	/*read first line: vertex number, edge number*/
	fscanf(fp_, "%d %d", &totvertex, &totedge);
    //Logger(LOG_DEBUG, "Vertex: %d Edge: %d", totvertex, totedge);
	
	/*read first edge*/
	fscanf(fp_, "%d %d", &source, &tmpv);
   // Logger(LOG_DEBUG, "s: %d e: %d", source, tmpv);
	edgenum++; vertexnum++;degree = 1;
	targets.push_back(tmpv);

	/*
    //string line;
    while(HasNext()) {
        line = NextLine();
        if(line.empty()) continue;
        edgenum++;
        //stringstream strm(line);
        //strm >> source;
        //strm >> tmpv;
        sscanf(line.c_str(), "%d %d", &source, &tmpv);
        degree=1;
        vertexnum++;
        targets.push_back(tmpv);
        break;
    }
	*/
	
	/* read whole file*/
    while(fscanf(fp_, "%d %d", &nextsource, &tmpv) != EOF) {
//        line = NextLine();
//        if(line.empty()) continue;
       // stringstream strm(line);
      //  strm >> nextsource;
      //  strm >> tmpv;

//        sscanf(line.c_str(), "%d %d", &nextsource, &tmpv);
		//Logger(LOG_DEBUG, "phase1");
        edgenum++;
        if(nextsource != source) {
		//	Logger(LOG_DEBUG, "phase2");
	//		Logger(LOG_DEBUG, "no.=%d: vid: %d degree: %d edgenum=%d", vertexnum, source, degree, edgenum);
            //add one unit into partition
            partitioner_.ProcessData(vertexnum, source, degree, targets, haspartition);             
            degree = 1;
            vertexnum++;
            source = nextsource;
            targets.clear();
            targets.push_back(tmpv);
		//	Logger(LOG_DEBUG, "phase2");
        }
        else {
		//	Logger(LOG_DEBUG, "phase3");
            degree++;
            targets.push_back(tmpv);
		//	Logger(LOG_DEBUG, "phase4");
        }
	//	Logger(LOG_DEBUG, "phase5");
    }
    //add last unit into partition
    partitioner_.ProcessData(vertexnum, source, degree, targets, haspartition);             
    targets.clear();
	//ASSERT0(vertexnum == totvertex && edgenum == totedge);
    Logger(LOG_DEBUG, "Vertex: %d Edge: %d", vertexnum, edgenum);
}

void
FileReader::Reset() {
	fseek(fp_, 0, SEEK_SET);
	/*
    int i;
    for(i = 0; i < totalfiles_; i++) {
        fseek(fp_[i], 0, SEEK_SET);
    }
    fileidx_ = 0;
    while(!HasNext() && fileidx_ < totalfiles_) {
        fileidx_++;
    }
	*/
    return ;
}

void
FileReader::GetCutsRatio(vector<vector<enum_t> >& edgecuts, enum_t& edgenum, vector<double>& iocost, double& miniocost, bool remap){
    string line;
    int src, target;
    int spid, tpid;
    int pnum = partitioner_.GetPartitionNumber();
    
    vector< vector< double> > costs(pnum, vector<double>(pnum, 0.0));
    vector< enum_t > edgecount(pnum, 0);
    
	for(int i = 0; i < pnum; i++)
        for(int j = 0; j < pnum; j++)
            costs[i][j] = partitioner_.GetIOCost(i,j);

    edgenum = 0;
    miniocost = 0.0;
    for(int i = 0; i < edgecuts.size(); i++) {
        for(int j = 0; j < edgecuts[i].size(); j++)
            edgecuts[i][j] = 0;
    }
    for(int i = 0; i < iocost.size(); i++) {
        iocost[i] = 0.0;
    }
    if(format_.compare("elist") == 0) {
        /* edge-list form*/
		/* pass the first line*/
        fscanf(fp_, "%d %d", &src, &target);
		while(fscanf(fp_, "%d %d", &src, &target) != EOF) {
            //line = NextLine();
            //if(line.empty()) continue;
            //sscanf(line.c_str(), "%d %d", &src, &target);
//            Logger(LOG_INFO, "src=%d target=%d", src, target);
            if(!partitioner_.IsSamePartition(src, target, spid, tpid)){
                miniocost += partitioner_.GetIOCost(spid, tpid);
                iocost[spid] += partitioner_.GetIOCost(spid, tpid);
                if(tpid != -1)
                    edgecuts[spid][tpid]++;
                else
                    edgecuts[spid][spid]++;
            }
			edgecount[spid]++;
			if(tpid != -1) 
				edgecount[tpid]++;
            edgenum++;
        }
    }
	/*
    else {*/
    /* adj-list without degree form*/
	/*
        while(HasNext()) {
            line = NextLine();
            if(line.empty()) continue;
            stringstream strm(line);
            strm >> src;
            while(strm.good()) {
                strm >> target;
                if(strm.fail()) break;
                if(!partitioner_.IsSamePartition(src, target, spid, tpid)){
                    miniocost += partitioner_.GetIOCost(spid, tpid);
                    iocost[spid] += partitioner_.GetIOCost(spid, tpid);
                    if(tpid != -1)
                        edgecuts[spid][tpid]++;
                    else
                        edgecuts[spid][spid]++;
                }
                edgenum++;
            }
        }
    }
	*/
	double edgebf = 0;
	int i;
	enum_t max_edgecount = 0;
	for(i = 0; i < pnum;  i++) {
		if(max_edgecount < edgecount[i])
			max_edgecount = edgecount[i];
	}
	edgebf = max_edgecount * 1.0 / edgenum * pnum;
	Logger(LOG_INFO, "Edge Balacne factor (with in/out edge): %lf", edgebf);

/*
    if(remap) {
        Logger(LOG_DEBUG, "iocost before remap: %lf", miniocost);
        miniocost = DoReMap(edgecuts, costs);
    }
	*/
//    edgeratio = (edgecuts*1.0/edgenum);
//    ioc = iocost;
//    Logger(LOG_DEBUG, "EdgeNum: %d\n", edgenum);
//    Logger(LOG_DEBUG, "Edge Cuts Matrix:");
//    for(int i = 0; i < pnum; i++) {
//        for(int j = 0; j < pnum; j++)
//            cout << edgecuts[i][j] <<" ";
//        cout <<endl;
//    }
    return ;
}

double
FileReader::DoReMap(vector<vector<enum_t> >& cuts, vector<vector<double> >& costs) {
    int*idx = new int[cuts.size()];
    int size = cuts.size();
    int i,j;
    for(i = 0; i < size; i++) {
        idx[i] = i;
    }
    double miniocost=1e20, iocost=0.0;
    int cnt= 0;
    do
    {
        iocost = 0.0;
        for(i = 0; i < size; i++)
            for(j = 0; j < size; j++)
                iocost += cuts[idx[i]][idx[j]] * costs[i][j];
        Logger(LOG_DEBUG,"Iteration %d: costs=%lf",cnt, iocost);
        cnt++;
        if(iocost < miniocost) miniocost = iocost;
    }while(next_permutation(idx, idx + size));
    return miniocost;
}

void
FileReader::LoadPartitionedGraph(string path) {
    partitioner_.LoadPartitionedGraph(path);
}
