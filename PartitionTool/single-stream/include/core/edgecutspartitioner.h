/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月12日 星期三 14时18分58秒
 */
#ifndef __EDGECUTSPARTITIONER_H__
#define __EDGECUTSPARTITIONER_H__

#include <core/streampartitioner.h>
#include <core/abstractheuristic.h>

class EdgeCutsPartitioner : public StreamPartitioner {

    public:
        EdgeCutsPartitioner(GraphPartition& gpart, PartitionStatistic& stat, HeuristicRule& rule);
        ~EdgeCutsPartitioner() {}

        virtual void ProcessData(vnum_t seq, vid_t source, int num, vidarray& target, bool haspartitioned);
        virtual void LoadPartitionedGraph(string path);
        virtual bool IsSamePartition(vid_t source, vid_t target, pid_t& pid, pid_t& tpid);
        virtual double GetIOCost(pid_t spid, pid_t tpid);

    private:
        void add_vertex(vnum_t seq, vid_t source, int num, vidarray& target, bool haspartitioned);

    private:
        HeuristicRule& rule_;
};

#endif    // #ifndef __EDGECUTSPARTITIONER_H__

