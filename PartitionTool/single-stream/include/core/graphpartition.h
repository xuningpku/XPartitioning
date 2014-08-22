/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月12日 星期三 14时23分35秒
 */
#ifndef __GRAPHPARTITION_H__
#define __GRAPHPARTITION_H__

#include <vector>
#include <core/type.h>
using namespace std;

class GraphPartition {
    public:
        GraphPartition(int partitionnumber);
        ~GraphPartition() {}
        void Add(pid_t pid, vid_t source, int num, vidarray& target);
    private:
        int partitionnumber_;
        vector<pid_t> partitionedgraph_;
};
#endif    // #ifndef __GRAPHPARTITION_H__

