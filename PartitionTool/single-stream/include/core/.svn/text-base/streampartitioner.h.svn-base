/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月12日 星期三 13时29分16秒
 */
#ifndef __STREAMPARTITIONER_H__
#define __STREAMPARTITIONER_H__

#include <core/graphpartition.h>
#include <core/partitionstatistic.h>
//#include <util/filereader.h>

class StreamPartitioner {

    public:
        StreamPartitioner(GraphPartition& gpart, PartitionStatistic& stat)
            :gpart_(gpart), stat_(stat) {}
        ~StreamPartitioner() {}
        virtual void ProcessData(vnum_t seq, vid_t source, int num, vidarray& target, bool haspartitioned)=0;
        virtual void LoadPartitionedGraph(string path)=0;

        virtual bool IsSamePartition(vid_t source, vid_t target, pid_t& spid, pid_t& tpid) = 0;
        virtual double GetIOCost(pid_t spid, pid_t tpid) = 0;
        virtual int GetPartitionNumber() {
            return stat_.get_partitionnumber();
        }

        GraphPartition& gpart_;
        PartitionStatistic& stat_; //critical section
};

#endif    // #ifndef __STREAMPARTITIONER_H__

