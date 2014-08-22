/*
* Author: Shao Yingxia
* Create Date: 2012骞�2鏈�0鏃�鏄熸湡涓�10鏃�8鍒�8绉�*
*/

#include <core/graphknife.h>
#include <util/logger.h>
#include <util/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GraphKnife::GraphKnife(int argc, char** args)
    :isready_(true), format_("elist"), vertexnum_(-1), edgenum_(-1), 
	htype_(HRT_NOTSET), wtype_(WT_NONE), scoretype_(1), partitionedgraph_(""),
	partitionnumber_(1),outpath_(""),topoconfigpath_(""),graphpath_(""),
	isedgecuts_(true),isvertexbalance_(true),haspartitioned_(false),
    iocpufactor_(1), gama_(0), usefennel_(false),
	balancefactor_(1){
    isready_ = ProcessOptions(argc, args);
}

GraphKnife::~GraphKnife(){
}

void 
GraphKnife::Usage() {
    int i;
    printf("App Usage:\n");
    printf("\t-p  <num>, number of partitions.\n");
    //printf("\t-v  <num>, vertex number of graph.\n");
    //printf("\t-en  <num>, edge number of graph.\n");
    printf("\t-c  <string>, specify the network topology configuration.\n");
    printf("\t-g  <path>, file or directory path of graph.\n");
    printf("\t-o  <path>, specify the output path of partition metadata.\n");
    printf("\t-pm <path>, file or directory path of partitioned graph.\n");
    printf("\t-hp <bool>, indicate the graph has partitioned.[false]\n");
    printf("\t-f  <string>, specify the format of input file.[elist]\n");
    printf("\t-e  <bool>, true: edge-cuts, false: vertex-cuts. [true]\n");
    printf("\t-s  <int>, scoretype for hiob[1]\n");
    printf("\t-b  <int>, balance type: edge or vertex.[vertex]\n");
    printf("\t-uf <bool>, indicate to use fennel. [false]\n");
    printf("\t-fc <double>, set iocpufactor. [1]\n");
    printf("\t-bf <double>, set iocpufactor. [1]\n");
    printf("\t-gama <double>, set gama parameter. [0]\n");
    printf("\t-m  <heuristical rule>, specify the heuristical rule for the partitioner.\n");
    printf("\t\tFollowing rules are valid:\n");
    for(i = 0; i < RULESIZE; i++)
        printf("\t\t\t%s\n", HR_NAME[i]);
    printf("\t-w  <weight mode>, specify the weight mode.\n");
    printf("\t\tFollowing modes are valid:\n");
    for(i = 0; i < WEIGHTSIZE; i++)
        printf("\t\t\t%s\n", WEIGHT_NAME[i]);
}

HeuristicRule*
GraphKnife::GetHeuristicRule(PartitionStatistic& stat, HeuristicRuleType htype, WeightType wtype) {
    switch(htype) {
        case HRT_DG:
            return (new DeterministicGreedyRule(stat, htype, wtype)); 
            break;
        case HRT_BALANCED:
            return (new BalancedRule(stat, htype, wtype));
            break;
        case HRT_CHUNK:
            return (new ChunkRule(stat, htype, wtype));
            break;
        case HRT_HASH: 
            return (new HashRule(stat, htype, wtype));
            break;
        case HRT_NON_NEIGHBOR: 
            return (new MinNonNeighborRule(stat, htype, wtype));
            break;
        case HRT_H_BALANCE:
            return (new HeterBalanced(stat, htype,wtype));
        case HRT_H_IOG:
            return (new HeterGreedyIO(stat, htype,wtype));
        case HRT_H_IOB:
            return (new HeterGreedyIOWithBalance(stat, htype,wtype));
        case HRT_RG:
        case HRT_TRIANGLE:
        case HRT_BALANCE_BIG:
        case HRT_PREFER_BIG:
        case HRT_AVOID_BIG:
        case HRT_GREEDY_EVOCUT:
        case HRT_NOTSET:
            Logger(LOG_INFO, "Do not set the heuristic rule for partitioner");
        default:
            return NULL;
    }
}

bool
GraphKnife::ProcessOptions(int argc, char** args) {    
    //1. process the optitions
    int i, idx;
    for(i = 1; i < argc; i++)
    {
        if(strcmp(args[i], "-p") == 0 && i + 1 < argc) {
            partitionnumber_ = atoi(args[++i]);
        }
		/*
        else if(strcmp(args[i], "-v") == 0 && i + 1 < argc) {
            vcapacity_ = atoi(args[++i]);
        }
        else if(strcmp(args[i], "-en") == 0 && i + 1 < argc) {
            edgenum_ = atoi(args[++i]);
        }
		*/
        else if(strcmp(args[i], "-pm") == 0 && i + 1 < argc) {
            i++; 
            partitionedgraph_ = string(args[i]);
        }
        else if(strcmp(args[i], "-hp") == 0 && i + 1 < argc) {
            i++; 
            haspartitioned_ = (strcmp(args[i],"true") == 0 ? true : false);
        }
        else if(strcmp(args[i], "-c") == 0 && i + 1 < argc) {
            topoconfigpath_ = string(args[++i]);
        }
        else if(strcmp(args[i], "-f") == 0 && i + 1 < argc) {
            format_ = string(args[++i]);
        }
        else if(strcmp(args[i], "-g") == 0 && i + 1 < argc) {
            graphpath_ = string(args[++i]);
        }
        else if(strcmp(args[i], "-e") == 0 && i + 1 < argc) {
            i++;
            isedgecuts_ = (strcmp(args[i],"true") == 0 ? true : false);
        }
        else if(strcmp(args[i], "-s") == 0 && i + 1 < argc) {
            i++;
            scoretype_ = atoi(args[i]);
        }
        else if(strcmp(args[i], "-b") == 0 && i + 1 < argc) {
            i++;
            isvertexbalance_ = (strcmp(args[i],"edge") == 0 ? false : true); 
        }
        else if(strcmp(args[i], "-o") == 0 && i + 1 < argc) {
            i++;
            outpath_ = string(args[i]);
        }
        else if(strcmp(args[i], "-fc") == 0 && i + 1 < argc) {
        	iocpufactor_ = atof(args[++i]);
        }
        else if(strcmp(args[i], "-bf") == 0 && i + 1 < argc) {
        	balancefactor_ = atof(args[++i]);
        }
        else if(strcmp(args[i], "-gama") == 0 && i + 1 < argc) {
            gama_ = atof(args[++i]);
        }
        else if(strcmp(args[i], "-uf") == 0 && i + 1 < argc) {
            i++;
            usefennel_ = (strcmp(args[i],"false") == 0 ? false : true); 
        }
        else if(strcmp(args[i], "-m") == 0 && i + 1 < argc) {
            i++; 
			printf("%sx\n", args[i]);
            for(idx = 0; idx < RULESIZE; idx++) {
                if(strcmp(args[i], HR_NAME[idx]) == 0) {
                    htype_ = (HeuristicRuleType)(idx);
                    break;
                }
            }
        }
        else if(strcmp(args[i], "-w") == 0 && i + 1 < argc) {
            i++; 
            for(idx = 0; idx < WEIGHTSIZE; idx++) {
                if(strcmp(args[i], WEIGHT_NAME[idx]) == 0) {
                    wtype_ = (WeightType)(idx);
                    break;
                }
            }
        }
        else
        {
			printf("%s\n", args[i]);
            Usage();
			isready_ = false;
            return false;
        }
    }
    Logger(LOG_INFO, "Options:\n\tgraphpath=%s\n\tconfig=%s\n\tnpart=%d\n\thaspartitioned=%d\n\tpartitionedgraph=%s\n\tisvertexbalance=%d\n\thtype=%d\n\twtype=%d\n\tedgecuts=%d\n\tscoretype=%d\n\tusefennel=%d\n\tiocpufactor=%lf\n\tgama=%lf\n\tbalancefactor=%lf\n",
            graphpath_.c_str(), topoconfigpath_.c_str(), partitionnumber_, haspartitioned_, partitionedgraph_.c_str(), isvertexbalance_ , htype_, wtype_, isedgecuts_, scoretype_,usefennel_, iocpufactor_, gama_, balancefactor_);

    if(graphpath_.length() == 0 || (htype_ == HRT_NOTSET && !haspartitioned_ ))
    {
        Usage();
		isready_ = false;
        return false;
    }
    
	isready_ = true;
	return true;
}

void
GraphKnife::GetVertexAndEdgeNumber() {
	FILE* fp = fopen(graphpath_.c_str(), "r");
	fscanf(fp, "%lld %lld", &vertexnum_, &edgenum_);
	fclose(fp);
	return;
}

void 
GraphKnife::Start() {
    if(isready_ == false) {
        Logger(LOG_WARNING, "Failed to be ready!\n");
        return ;
    }

    /*
     * some classes would be large, so use Pointer.
     */
    FileReader* pFileReader = NULL;
    GraphPartition* pGraphPartition = NULL;
    PartitionStatistic* pPartitionStatistic = NULL;
    StreamPartitioner* pPartitioner = NULL;
    HeuristicRule* pHeuristicRule = NULL;

    Logger(LOG_DEBUG, "Setup Partitioner: partitionnumber=%d", partitionnumber_);
   
    //2. setup partitioner    
    pGraphPartition = new GraphPartition(partitionnumber_);
    pPartitionStatistic = new PartitionStatistic(partitionnumber_);
    GetVertexAndEdgeNumber();
    Logger(LOG_INFO, "vertexnum=%lld edgenum=%lld pnum=%d\n", vertexnum_, edgenum_, partitionnumber_);
    Logger(LOG_DEBUG, "vertexnum=%d edgenum=%d pnum=%d\n", (vertexnum_ > 0), (edgenum_>0), (partitionnumber_ >0));
   
   if((vertexnum_ > 0) && (partitionnumber_ > 0)) {
	  // cout << "here"<<endl;
	   Logger(LOG_DEBUG, "set vertexcacapcity....");
        pPartitionStatistic->set_vertexcapacity(floor(vertexnum_*1.0/partitionnumber_ + 0.5));
   }
    if((edgenum_ > 0) && (partitionnumber_ > 0) ) {
	   //cout << "here2"<<endl;
	   Logger(LOG_DEBUG, "set edgecacapcity....");
        pPartitionStatistic->set_edgecapacity(floor(edgenum_*1.0/partitionnumber_ + 0.5));
    }

    if(topoconfigpath_ != "") {
        pPartitionStatistic->SetUpConfiguration(topoconfigpath_, vertexnum_);
		if (iocpufactor_ != 0)
			pPartitionStatistic->set_iocpufactor(iocpufactor_);
		if (balancefactor_ != 0)
			pPartitionStatistic->set_balancefactor(balancefactor_);
		if (gama_ != 0)
			pPartitionStatistic->set_gama(gama_);    
        pPartitionStatistic->DumpNodeConfig();
    }

	if(haspartitioned_) {
		/*fake htype_ to enable create Partitioner correctly*/	
		htype_ = HRT_HASH;
	}
	
    if(isedgecuts_) {
        pHeuristicRule = GetHeuristicRule(*pPartitionStatistic, htype_, wtype_);
        pHeuristicRule->set_isvertexbalance(isvertexbalance_);
        if(htype_ == HRT_H_IOB) {
            ((HeterGreedyIOWithBalance*)pHeuristicRule)->setScoretype(scoretype_);
            ((HeterGreedyIOWithBalance*)pHeuristicRule)->setUseFennel(usefennel_);
        }
        if(pHeuristicRule == NULL){
            Logger(LOG_FATAL, "Unspported Heuristical Rule");
            return;
        }
        pPartitioner = new EdgeCutsPartitioner(*pGraphPartition, *pPartitionStatistic, *pHeuristicRule);
    }
    else {
        return ;
        Logger(LOG_FATAL, "Unsportted Vertex-Cuts in this version.");
    }

    Logger(LOG_DEBUG, "Setup FileReader");
    //3. setup filereader
    Time timer;
    pFileReader = new FileReader(*pPartitioner, graphpath_, format_);
    timer.Start();
    if(haspartitioned_) pFileReader->LoadPartitionedGraph(partitionedgraph_);
    pFileReader->Start(haspartitioned_);
    timer.Stop();
    Logger(LOG_INFO, "Partition Processing costs %lfs", timer.GetElapsedTime());
   
    //pPartitionStatistic->DumpPartitionTable();
    //pPartitionStatistic->DumpPartitionLoad();

    pFileReader->Reset();
    double ratio, tot_miniocost, ratio2;
    vector<double> vcpucost(partitionnumber_, 0.0);
    vector<double> ecpucost(partitionnumber_, 0.0);
    vector<double> iocost(partitionnumber_, 0.0);
    BalanceStat bs;
    vector<vector<enum_t> > edgecuts(partitionnumber_, vector<enum_t>(partitionnumber_, 0));
    enum_t edgenum = 0, cutedge = 0, cutedge2=0;

    timer.Start();
    Logger(LOG_INFO, "Get BalacneFactor....");
    pPartitionStatistic->GetBalanceFactor(bs, vcpucost, ecpucost, isvertexbalance_);
    Logger(LOG_INFO, "Get CutsRatio....\n");
    pFileReader->GetCutsRatio(edgecuts, edgenum, iocost, tot_miniocost, htype_ == HRT_DG );
    timer.Stop();

    Logger(LOG_INFO, "edgenum = %d, edgenum_ = %d", edgenum, edgenum_);
	//ASSERT0((edgenum==edgenum_));
    double maxvcpucost= -1e20, maxecpucost = -1e20, maxiocost= -1e20, maxvtot= -1e20;
	double maxetot=-1e20,miniocost=1e20;
	vector<enum_t> edgecutsunit(partitionnumber_, 0);
	enum_t max_edgecuts = 0;
	enum_t min_edgecuts = 1<<29;
	printf("Detailed edge-cut info:\n");
    for(int k = 0; k < partitionnumber_; k++) {
        maxvcpucost = maxvcpucost > vcpucost[k] ? maxvcpucost : vcpucost[k];
        maxecpucost = maxecpucost > ecpucost[k] ? maxecpucost : ecpucost[k];
        maxiocost = maxiocost > iocost[k] ? maxiocost : iocost[k];
        miniocost = miniocost < iocost[k] ? miniocost : iocost[k];
        maxvtot = maxvtot > (vcpucost[k] + iocost[k]) ? (maxvtot) : (vcpucost[k] + iocpufactor_*iocost[k]);
        maxetot = maxetot > (ecpucost[k] + iocost[k]) ? (maxetot) : (ecpucost[k] + iocpufactor_*iocost[k]);
        for(int ll=0; ll < partitionnumber_; ll++) {
			printf("%lld ", edgecuts[k][ll]);
            cutedge += edgecuts[k][ll];
			edgecutsunit[k] += edgecuts[k][ll];
            if(k != ll)
                cutedge2 += edgecuts[k][ll];
        }
		printf("\n");
    }

    if(outpath_ != "" && !haspartitioned_){
        FILE* outfp = NULL;
        outfp = fopen(outpath_.c_str(), "w");
        pPartitionStatistic->DumpPartitionTable(outfp);
        fclose(outfp);
    }
    /* count vertex having out-edge*/
    ratio = cutedge * 1.0 / edgenum;
    /* count vertex without out-edge*/
    ratio2 = cutedge2 * 1.0 / edgenum;

	for(int k = 0; k < partitionnumber_; k++) {
		printf("pid %d: ec=%lld cpucost=%lf\n", k, edgecutsunit[k], ecpucost[k]);
		if(edgecutsunit[k] > max_edgecuts) max_edgecuts = edgecutsunit[k];
		if(edgecutsunit[k] < min_edgecuts) min_edgecuts = edgecutsunit[k];
	}

	Logger(LOG_INFO, "Max Edge Cuts=%lld, Min Edge Cuts=%lld", max_edgecuts, min_edgecuts);  
	Logger(LOG_INFO, "Get EdgeCuts Ratio costs %lfs", timer.GetElapsedTime());  
    Logger(LOG_INFO, "EdgeNumber: %lld, EdgeCuts: %lld", edgenum, cutedge);
    Logger(LOG_INFO, "EdgeCuts ratio= %lf%%, EdgeCuts ratio2= %lf%%",ratio*100, ratio2*100);
    Logger(LOG_INFO, "Vertex_BF= %lf, VCPULoad_BF= %lf", bs.getVertexBf(), bs.getVertexBasedCostBf());
    Logger(LOG_INFO, "Edge_BF= %lf, ECPULoad_BF= %lf", bs.getEdgeBf(), bs.getEdgeBasedCostBf());
    Logger(LOG_INFO, "TotalMinIoCost= %lf[remap=%s]", tot_miniocost, ((htype_==HRT_DG?"true":"false")));
    Logger(LOG_INFO, "MaxVertexCpuCost= %lf, MaxEdgeCpuCost= %lf", maxvcpucost, maxecpucost);
	Logger(LOG_INFO, "MaxIoCost = %lf, MinIoCost=%lf, bf=%lf", maxiocost, miniocost, maxiocost/(miniocost+1e-5));
	Logger(LOG_INFO, "MaxVertexTotalMixCost= %lf, MaxEdgeTotalMixCost= %lf", maxvtot, maxetot);
   
    delete pFileReader;
    delete pPartitioner;
    delete pHeuristicRule;
    delete pPartitionStatistic;
    delete pGraphPartition;
}
