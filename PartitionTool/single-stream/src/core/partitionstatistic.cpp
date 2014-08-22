/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月12日 星期三 14时55分08秒
 */

#include <core/partitionstatistic.h>
#include <util/logger.h>

PartitionStatistic::PartitionStatistic(int partitionnumber)
    :partitionnumber_(partitionnumber), toposize_(0), vertexcapacity_(0), edgecapacity_(0){
        int i;
        for(i = 0; i < partitionnumber; i++) {
            vcounter_.push_back(Counter<vnum_t>());
            ecounter_.push_back(Counter<enum_t>());
            cost.push_back(0.0);
        }
}

PartitionStatistic::PartitionStatistic(int partitionnumber, string path) {
    new (this)PartitionStatistic(partitionnumber); //here call the Placement new operator
    SetUpConfiguration(path);
}

PartitionStatistic::~PartitionStatistic() {
}

vnum_t
PartitionStatistic::GetVertexCount(pid_t pid) {
    return vcounter_[pid];
}

enum_t
PartitionStatistic::GetEdgeCount(pid_t pid) {
    return ecounter_[pid];
}

void
PartitionStatistic::GetIntersectionCount(int num, vidarray& target, vector<Counter<vnum_t> >& icounter) {
    int i;
    int size = num;
    pid_t pid;
    for(i = 0; i < size; i++) {
        pid = GetPartitionId(target[i]);
        if(pid != HashTable<vid_t, pid_t>::NOT_FOUND) {
            icounter[pid]++;
        }
    }
}

/*
 * Make sure vid has been processed, before
 * calling isContainVertex
 */
bool 
PartitionStatistic::isContainVertex(vid_t vid, pid_t pid) {
    return (pid == v2pmap_.GetValue(vid));
}

bool
PartitionStatistic::isVertexProcessed(vid_t vid) {
    return (v2pmap_.GetValue(vid) != HashTable<vid_t, pid_t>::NOT_FOUND);
}

pid_t
PartitionStatistic::GetPartitionId(vid_t vid) {
    return v2pmap_.GetValue(vid);
}

void
PartitionStatistic::UpdateVertexInfo(vid_t vid, pid_t pid) {
    v2pmap_.Insert(vid, pid);
    vcounter_[pid].inc();
}

void
PartitionStatistic::UpdateEdgeInfo(vid_t source, vid_t target, pid_t pid) {
    ecounter_[pid].inc();
}

void PartitionStatistic::BatchUpdateEdgeInfo(pid_t pid, enum_t num) {
    ecounter_[pid].inc(num);
}

void
PartitionStatistic::GetBalanceFactor(BalanceStat& bs, vector<double>& vc, vector<double>& ec, bool isvertexbalance) {
    vnum_t vertex = 0;
    enum_t edge = 0;
    double vload = 0, eload = 0;
    vnum_t max_vertex = 0, max_edge = 0;
    vnum_t min_vertex = 1<<31, min_edge = 1<<31;
    double max_vload = 0, max_eload = 0;
    double min_vload = 1e20, min_eload = 1e20;
    double vbf = -1, ebf = -1, ecbf = -1, vcbf = -1;
    double mvbf = -1, mebf = -1, mecbf = -1, mvcbf = -1;
    //vector<double> vc(get_partitionnumber());
    //vector<double> ec(get_partitionnumber());


    int i;
    for(i = 0; i < vc.size(); i++) {
        vc[i] = 0.0;
        ec[i] = 0.0;
    }
    
    printf("In get Balance Factor\n");
    for(i = 0; i < partitionnumber_; i++) {
        vertex += vcounter_[i];
        edge   += ecounter_[i];
        printf("Pid=%d: edge=%lld, vertex=%lld\n", i, (long long)ecounter_[i], (long long)vcounter_[i]);
        vc[i] = vcounter_[i] * GetCpuCost(i);
        ec[i] = ecounter_[i] * GetCpuCost(i);
        
        vload += vc[i];
        eload += ec[i];

        max_vload = max_vload >= vc[i] ? max_vload : vc[i];
        max_eload = max_eload >= ec[i] ? max_eload : ec[i];

        max_vertex = max_vertex >= vcounter_[i] ? max_vertex : vcounter_[i];
        max_edge = max_edge >= ecounter_[i] ? max_edge : ecounter_[i];
        
        min_vload = min_vload <= vc[i] ? min_vload : vc[i];
        min_eload = min_eload <= ec[i] ? min_eload : ec[i];

        min_vertex = min_vertex <= vcounter_[i] ? min_vertex : vcounter_[i];
        min_edge = min_edge <= ecounter_[i] ? min_edge : ecounter_[i];
    }
    mvbf = (max_vertex * 1.0 / (min_vertex + 1e-5));
    mvcbf = (max_vload / (min_vload + 1e-5));
    
    mebf = (max_edge * 1.0 / (min_edge + 1e-5));
    mecbf = (max_eload / (min_eload + 1e-5));
    
    vbf = (max_vertex * 1.0 / vertex * partitionnumber_);
    vcbf = (max_vload / vload * partitionnumber_);
    
    //Logger(LOG_INFO, "vertex=%d edge=%d maxedge=%d eload=%lf maxeload=%lf pnum=%d", vertex, edge, max_edge, eload, max_eload, partitionnumber_);
    ebf = (max_edge * 1.0 / edge * partitionnumber_);
    ecbf = (max_eload / eload * partitionnumber_);

    bs.setVertexBf(vbf);
    bs.setEdgeBf(ebf);
    bs.setVertexBasedCostBf(vcbf);
    bs.setEdgeBasedCostBf(ecbf);
    bs.setIsVertexBalance(isvertexbalance);
   /* 
    if(isvertexbalance) {
        cc = vc;
    }
    else { 
        cc = ec; 
    }
	*/
}
/*
void
PartitionStatistic::SetUpConfiguration(string path, vnum_t tn) {
    FILE* fp = fopen(path.c_str(), "r");
    char buffer[1024];
    pid_t id, id2;
    double cc, ioc;
    while(fgets(buffer, 1024, fp) != NULL) {
        if(buffer[0] == '#' || buffer[0]=='\0') continue;
        string line(buffer);
        if(line.find("toposize") == 0) {
            sscanf(buffer, "toposize=%d",&toposize_);
            for(int i = 0; i < toposize_; i++)
                topologyconfig_.push_back(NodeConfig());
            continue;
        } 
        if(line.find("ccnode") == 0) {
            sscanf(buffer, "ccnode%d=%lf", &id, &cc);
            topologyconfig_[id].set_cpucost(cc);
            continue;
        }
        if(line.find("iocnode") == 0) {
            sscanf(buffer, "iocnode%d iocnode%d %lf", &id, &id2, &cc);
            topologyconfig_[id].AddBandWidth(id2, cc);
            topologyconfig_[id2].AddBandWidth(id, cc);
        }
    }
    if(toposize_ != partitionnumber_) 
        partitionnumber_ = toposize_; //now we need the partitionnumber == toposize_
    fclose(fp);
    
    //set up vertex capacity for each node
    if(tn) {
        int i,j;
        double base, ncpucost;
        for(i = 0; i < toposize_; i++) {
            base = 0.0;
            ncpucost = topologyconfig_[i].get_cpucost();
            for(j = 0; j < toposize_; j++) {
                base += ncpucost / topologyconfig_[i].get_cpucost();
            }
            topologyconfig_[i].set_vcapacity(floor(tn/base + 0.5));
        }
    }
}
*/
/* Setup to read configuration*/
void
PartitionStatistic::SetUpConfiguration(string path, vnum_t tn) {
    FILE* fp = fopen(path.c_str(), "r");
    pid_t id, i, j;
	double cc;
	double cpu_factor, io_factor;
	fscanf(fp, "%d %lf %lf", &toposize_, &cpu_factor, &io_factor);
    for(i = 0; i < toposize_; i++)
        topologyconfig_.push_back(NodeConfig());
	for(i = 0; i < toposize_; i++) {
		for(j = 0; j < toposize_; j++) {
			fscanf(fp,"%lf", &cc);
//			printf("%d ", cc);
			if(i == j) {
				if(cc < 1e-5) cc=1.0;
				topologyconfig_[i].set_cpucost(cc*cpu_factor);
				continue;
			}
			topologyconfig_[i].AddBandWidth(j, cc*io_factor);
		}
//		printf("\n");
	}
    if(toposize_ != partitionnumber_) 
        partitionnumber_ = toposize_; //now we need the partitionnumber == toposize_
    fclose(fp);
    
    //set up vertex capacity for each node
    if(tn) {
        int i,j;
        double base, ncpucost;
        for(i = 0; i < toposize_; i++) {
            base = 0.0;
            ncpucost = topologyconfig_[i].get_cpucost();
            for(j = 0; j < toposize_; j++) {
                base += ncpucost / topologyconfig_[i].get_cpucost();
            }
            topologyconfig_[i].set_capacity(floor(tn/base + 0.5));
        }
    }
}

