/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月11日 星期二 10时48分21秒
 */
#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <core/streampartitioner.h>

using namespace std;

class FileReader {
    public:
        FileReader(StreamPartitioner& spart, string gpath, string fmt);
        ~FileReader();
        void Start(bool haspartition);
        void LoadPartitionedGraph(string path);
       
        void Reset();
       // bool HasNext();
       // string NextLine();
       // void ReadFromAdjacency(bool haspartitioned);
        void ReadFromEdgeList(bool haspartititoned);

        void GetCutsRatio(vector<vector<enum_t> >& edgecuts, enum_t& edgenum, vector<double>& iocost, double& miniocost, bool remap=false);
        double DoReMap(vector<vector<enum_t> >& cuts, vector<vector<double> >& costs);

    private:
        string format_;
        string gpath_;
        FILE*  fp_;        
		StreamPartitioner& partitioner_;
};

#endif    // #ifndef __FILEREADER_H__

