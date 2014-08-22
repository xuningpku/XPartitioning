/*
* Author: Shao Yingxia
* Create Date: 2012年12月10日 星期一 10时21分19秒
*/
#ifndef __GRAPHKNIFE_H__
#define __GRAPHKNIFE_H__

#include <util/logger.h>
#include <util/filereader.h>
#include <core/streampartitioner.h>
#include <core/edgecutspartitioner.h>
#include <core/homoheuristic.h>
#include <core/heterheuristic.h>
#include <core/partitionstatistic.h>
#include <vector>
#include <string>

using namespace std;

    static const int RULESIZE = 14;
    static const char* HR_NAME[] = {
        "balance",
        "chunk",
        "hash",
        "dg",
        "rg",
        "triangle",
        "balancebig",
        "preferbig",
        "avoidbig",
        "evocut",
        "nn",
        "hbalance",
        "hiog",
        "hiob"
    };

    static const int WEIGHTSIZE = 3;
    static const char* WEIGHT_NAME[] = {
        "none",
        "linear",
        "expo"
    };

class GraphKnife
{
    public:
        GraphKnife(int argc, char** args);
        ~GraphKnife();
        void Start();
        void Usage();
		bool ProcessOptions(int argc, char** args);
    private:
        HeuristicRule* GetHeuristicRule(PartitionStatistic& stat, HeuristicRuleType htype, WeightType wtype);
		void GetVertexAndEdgeNumber();

    private:
        string graphpath_;              //graph file path [required]
        string topoconfigpath_;         //topology configuration file path [required]
        string outpath_;                //outpath of partition meta data [required]
		int partitionnumber_;           //partition number[required]
		
        string format_;                 //graph file format [optional: default=elist]

        vnum_t vertexnum_;                 //total number of vertex of the graph
        enum_t edgenum_;                   //total number of edges of the graph

        HeuristicRuleType htype_;       //Heursitic Rule Type
        WeightType wtype_;              //Weight Type
        bool isedgecuts_;               //Edge-Cuts or Vertex-Cuts [default = edge-cuts]
        bool isready_;                  //ready or not
        int  scoretype_;				//score type of hiob method
        bool isvertexbalance_;			//default: balancing the cpu load by vertex number
        bool haspartitioned_;			
        string partitionedgraph_;
        
        /* fennel related input */ 
        double iocpufactor_;
        double balancefactor_;
        double gama_;
        bool usefennel_;
};

#endif    // #ifndef __GRAPHKNIFE_H__
