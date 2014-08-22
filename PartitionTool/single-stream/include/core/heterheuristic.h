/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月20日 星期四 19时14分39秒
 */
#ifndef __HETERHEURISTIC_H__
#define __HETERHEURISTIC_H__

#include <core/abstractheuristic.h>

class HeterBalanced : public HeuristicRule {
    public:
    HeterBalanced(PartitionStatistic& stat, HeuristicRuleType htype, WeightType wtype):HeuristicRule(stat, htype, wtype) {}
    virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets);

};

class HeterGreedyIO : public HeuristicRule {
    public:
    HeterGreedyIO(PartitionStatistic& stat, HeuristicRuleType htype, WeightType wtype):HeuristicRule(stat, htype, wtype) {}
    virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets);
};

class HeterGreedyIOWithBalance : public HeuristicRule {
    public:
    HeterGreedyIOWithBalance(PartitionStatistic& stat, HeuristicRuleType htype, WeightType wtype)
        :HeuristicRule(stat, htype, wtype),scoretype_(0),usefennel_(false){}
    virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets);
   
    typedef struct {
        int scoretype;
        double iocost, miniocost, maxiocost;
        double cpucost, mincpucost,maxcpucost;
        double accuiocost;
        double iocpu_factor;
        double balance_factor;
        double deltacpucost;
        int degree;
    }ScorePara;

    void setScoretype(int t) {
        scoretype_ = t;
    }

    void setUseFennel(bool usefennel) {
        usefennel_ = usefennel;
    }

 //   void setIsVertexCount(bool flag) { isVertexcount_ = flag; }

    private:
        pid_t minrule(vnum_t seq, vid_t source, int num, vidarray& targets);
        pid_t capacityrule(vnum_t seq, vid_t source, int num, vidarray& targets);
        pid_t maxrule(vnum_t seq, vid_t source, int num, vidarray& targets);
        pid_t fennelrule(vnum_t seq, vid_t source, int num, vidarray& targets);
        pid_t fennelstandard(vnum_t seq, vid_t source, int num, vidarray& targets);
        pid_t workloadbasedrule(vnum_t seq, vid_t source, int num ,vidarray& targets);
        double getscore(ScorePara sp);
        int scoretype_;
        bool usefennel_;
//        bool isvertexcount_;
};

#endif    // #ifndef __HETERHEURISTIC_H__

