/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月13日 星期四 20时04分20秒
 */

#include <core/edgecutspartitioner.h>
#include <util/logger.h>
#include <sstream>

using namespace std;

EdgeCutsPartitioner::EdgeCutsPartitioner
(GraphPartition& gpart, PartitionStatistic& stat, HeuristicRule& rule)
    :StreamPartitioner(gpart, stat),rule_(rule) {

}

void
EdgeCutsPartitioner::ProcessData(vnum_t seq, vid_t source, int num, vidarray& target, bool haspartitioned) {
    if(haspartitioned) {
        stat_.BatchUpdateEdgeInfo(stat_.GetPartitionId(source), num);
    }
    else {
        add_vertex(seq, source, num, target, haspartitioned);
    }
}

void
EdgeCutsPartitioner::LoadPartitionedGraph(string path) {
    FILE* fp = fopen(path.c_str(), "r");
    vnum_t vid;
    pid_t pid;
    while(fscanf(fp, "%d %d", &vid, &pid) != EOF) {
        stat_.UpdateVertexInfo(vid, pid);
    }
    return ;
}

void
EdgeCutsPartitioner::add_vertex(vnum_t seq, vid_t source, int num, vidarray& target, bool haspartitioned) {
    pid_t pos = -1;
    pos = rule_.MakeDecision(seq, source, num, target);
	Logger(LOG_DEBUG, "pos=%d", pos);
    stat_.UpdateVertexInfo(source, pos);
    stat_.BatchUpdateEdgeInfo(pos, num);
    gpart_.Add(pos, source, num, target);
}

bool
EdgeCutsPartitioner::IsSamePartition(vid_t source, vid_t target, pid_t& pid, pid_t& tpid) {
    pid_t psrc = stat_.GetPartitionId(source);
    pid_t ptgt = stat_.GetPartitionId(target);
    pid = psrc;
    tpid = ptgt;
//    Logger(LOG_INFO, "source=%d target=%d", psrc, ptgt);
/*    if(HashTable<vid_t, pid_t>::NOT_FOUND == psrc){
        Logger(LOG_WARNING, "Source Node %d not found in HashTable!", source);
    }
    if(HashTable<vid_t, pid_t>::NOT_FOUND == ptgt)
        Logger(LOG_WARNING, "Target Node %d not found in HashTable!", target);
    */

    return (psrc ==ptgt);

    if(HashTable<vid_t, pid_t>::NOT_FOUND == psrc ||
        HashTable<vid_t, pid_t>::NOT_FOUND == ptgt ||
     psrc == ptgt)
        return true;
    return false;
}

double
EdgeCutsPartitioner::GetIOCost(pid_t spid, pid_t tpid) {
    if(tpid == HashTable<vid_t, pid_t>::NOT_FOUND) 
        return 0.0;
    return stat_.GetNode(spid).get_bandwidth(tpid);
}
