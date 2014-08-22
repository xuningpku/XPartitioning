/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月20日 星期四 19时04分52秒
 */
#ifndef __ABSTRACTHEURISTIC_H__
#define __ABSTRACTHEURISTIC_H__

#include <core/type.h>
#include <core/partitionstatistic.h>
#include <util/random.h>

enum HeuristicRuleType {
    HRT_NOTSET=-1, 
    HRT_BALANCED=0, 
    HRT_CHUNK, 
    HRT_HASH, 
    HRT_DG,
    HRT_RG, 
    HRT_TRIANGLE,
    HRT_BALANCE_BIG, 
    HRT_PREFER_BIG, 
    HRT_AVOID_BIG,
    HRT_GREEDY_EVOCUT,
    HRT_NON_NEIGHBOR,
    HRT_H_BALANCE, //balance cpucost
    HRT_H_IOG, //greedy on iocost
    HRT_H_IOB //greedy balance + greedy on iocost
};

enum WeightType {
    WT_NONE, 
    WT_LINEAR, 
    WT_EXPO
};

class HeuristicRule {
    public:
        static int const NOT_DECIDED = -1;
        virtual ~HeuristicRule () {};
        HeuristicRule(PartitionStatistic& stat, HeuristicRuleType htype, WeightType wtype)
            :stat_(stat), htype_(htype), wtype_(wtype), isvertexcount_(1),edgeweight_(1) {}

        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target) = 0;
        double GetWeight(pid_t pnum, WeightType wtype) {
            vnum_t vcapacity = stat_.get_vertexcapacity();
            vnum_t vcount = stat_.GetVertexCount(pnum);
            if(!isvertexcount_) {
                vcount = stat_.GetEdgeCount(pnum);
                vcapacity = stat_.get_edgecapacity();
            }

		//	fprintf(stderr,"%lld %lld\n", vcount,vcapacity);
            switch(wtype) {
                case WT_NONE:
                    return 1.0;
                case WT_LINEAR:
                    return (double)(1.0 - 1.0 * vcount/vcapacity);
                case WT_EXPO:
                    return (double)(1.0 - exp((double)(vcount-vcapacity))) ;
                defaut:
                    Logger(LOG_FATAL,"Unsupportted weight type!");
            }
        }

        pid_t RandomGetAPid(vector<pid_t>& reserved) {
            int t = rgen_.GetRandom();
//            Logger(LOG_DEBUG, "The random number=%d", t);
            return reserved[t % reserved.size()];
        }

        void set_heuristicaruletype(HeuristicRuleType type) { htype_ = type; }
        void set_weighttype(WeightType type) { wtype_ = type; }
        void set_isvertexbalance(bool flag) { isvertexcount_ = flag; }
    
    protected:        
        HeuristicRuleType htype_;
        WeightType wtype_;
        PartitionStatistic& stat_; //must initialize in initalization list
        Random rgen_;
        bool isvertexcount_;
        double edgeweight_;
};

#endif    // #ifndef __ABSTRACTHEURISTIC_H__
