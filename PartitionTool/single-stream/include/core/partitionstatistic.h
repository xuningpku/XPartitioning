/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月12日 星期三 14时24分27秒
 */
#ifndef __PARTITIONSTATISTIC_H__
#define __PARTITIONSTATISTIC_H__

#include <core/graphpartition.h>
#include <core/nodeconfig.h>
#include <util/hashtable.h>
#include <util/counter.h>
#include <vector>
#include <cmath>

using namespace std;

class BalanceStat{
    public:
        void setVertexBf(double vbf) { vertex_balance_factor_ = vbf; }
        double getVertexBf() { return vertex_balance_factor_; }

        void setEdgeBf(double ebf) { edge_balance_factor_ = ebf; }
        double getEdgeBf() { return edge_balance_factor_; }

        void setEdgeBasedCostBf(double ecbf) { edge_based_cost_balance_factor_ = ecbf; } 
        double getEdgeBasedCostBf() { return edge_based_cost_balance_factor_; }

        void setVertexBasedCostBf(double vcbf) { vertex_based_cost_balance_factor_ = vcbf; }
        double getVertexBasedCostBf() { return vertex_based_cost_balance_factor_; }

        void setIsVertexBalance(bool flag) { isvertexbalance_ = flag; }
        bool getIsVertexBalance() { return isvertexbalance_; }
    private:
        double vertex_balance_factor_;
        double edge_based_cost_balance_factor_;
        double vertex_based_cost_balance_factor_;
        double edge_balance_factor_;
        bool isvertexbalance_;
};

/*
 * Record the statistic of partitions which will
 * help the partitioner do a better decision.
 * Also need to remember some global information
 */
class PartitionStatistic {
    public:
        PartitionStatistic(int partititonnumber);
        PartitionStatistic(int partititonnumber, string path);
        ~PartitionStatistic();

        vnum_t GetVertexCount(pid_t pid);
        enum_t GetEdgeCount(pid_t pid);
        void GetIntersectionCount(int num, vidarray& target, vector<Counter<vnum_t> >& icounter);
        bool isContainVertex(vid_t vid, pid_t pid);
        bool isVertexProcessed(vid_t vid);
        pid_t GetPartitionId(vid_t vid);
        void UpdateVertexInfo(vid_t vid, pid_t pid);
        void InsertVertex(vid_t vid, pid_t pid) { v2pmap_.Insert(vid, pid); }
        void UpdateEdgeInfo(vid_t source, vid_t target, pid_t pid);
        void BatchUpdateEdgeInfo(pid_t, enum_t);
        void SetUpConfiguration(string path, vnum_t totalnodenumber = 0);
        void GetBalanceFactor(BalanceStat& bs, vector<double>& vcpucost, vector<double>& ecpucost, bool isvertexbalance);
        double GetCpuCost(pid_t i) { return topologyconfig_[i].get_cpucost(); }
        double GetCpuCostLimit(pid_t i) { return topologyconfig_[i].get_capacity(); }
        void GetNode(pid_t i, NodeConfig& node) { node = topologyconfig_[i]; }
        NodeConfig GetNode(pid_t i) { return topologyconfig_[i]; }


        int get_partitionnumber() { return partitionnumber_; }
        void set_partitionnumer(int partnum) { partitionnumber_ = partnum; }
        enum_t get_edgecapacity() { return edgecapacity_; }
        void set_edgecapacity(enum_t ec) { edgecapacity_ = ec; }
        vnum_t get_vertexcapacity() { return vertexcapacity_; }
        void set_vertexcapacity(vnum_t vc) { vertexcapacity_ = vc; }
        
        double get_iocpufactor() { return iocpufactor_; }
        void set_iocpufactor(double fc) { iocpufactor_ = fc; }
        double get_balancefactor() { return balancefactor_; }
        void set_balancefactor(double fc) { balancefactor_ = fc; }

        double get_gama() { return gama_; }
        void set_gama(double gama) { gama_ = gama; }

        /* Dump Function */
        void DumpPartitionTable(FILE* fp = NULL) { v2pmap_.dump(fp); }
        
        void DumpPartitionLoad() {
            int i = 0;
            for(i = 0; i < partitionnumber_; i++) {
                cout <<vcounter_[i] <<" ";
            }
            cout <<endl;
        }

        void DumpNodeConfig() {
            cout <<"Total node: "<<toposize_<<endl;
            for(int i = 0; i < toposize_; i++) {
                cout <<"node "<<i<<": "<<topologyconfig_[i].toString() <<endl;
            }
        }

        void AddCost(pid_t pid, double cc) { cost[pid] += cc; };
        double GetAccuIoCost(pid_t pid) { return cost[pid]; }

    private:
        /*static information which from outside*/
        int partitionnumber_;
        int toposize_;
        enum_t edgecapacity_;
        vnum_t vertexcapacity_;
        double iocpufactor_;
        double balancefactor_;
        double gama_;
        vector<NodeConfig> topologyconfig_;

        /*dynamic information which is generated during the partition*/
        HashTable<vid_t, pid_t> v2pmap_; //hash table records the vertex to machine map
        vector<Counter<vnum_t> > vcounter_; //vcounter records the number of vertex;
        vector<Counter<enum_t> > ecounter_; //ecounter records the number of edge;
        /*debug*/
        vector<double> cost;

};

#endif    // #ifndef __PARTITIONSTATISTIC_H__

