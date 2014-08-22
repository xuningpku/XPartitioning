/*
 * Here mainly implemented 10 heuristical rules based on
 * Streaming Graph Partitioning for Large Distributed Graphs, Isabelle Stanton, KDD 12
 *
 * Author: Shao Yingxia
 * Create Date: 2012年12月13日 星期四 20时18分51秒
 */
#ifndef __HOMOHEURISTIC_H__
#define __HOMOHEURISTIC_H__

#include <core/abstractheuristic.h>


class BalancedRule : public HeuristicRule {
    public:
        BalancedRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype)
                     :HeuristicRule(stat, type, wtype) {
        }
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class ChunkRule : public HeuristicRule { 
    public:
        ChunkRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype)
                     :HeuristicRule(stat, type, wtype) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class HashRule : public HeuristicRule {
    public:
        HashRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype)
                     :HeuristicRule(stat, type, wtype) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class DeterministicGreedyRule : public HeuristicRule {
    public:
        DeterministicGreedyRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype)
                     :HeuristicRule(stat, type, wtype) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class MinNonNeighborRule : public HeuristicRule {
    public:
        MinNonNeighborRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype)
                     :HeuristicRule(stat, type, wtype) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class RandomizedGreedyRule : public HeuristicRule {
    public:
        RandomizedGreedyRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype)
                     :HeuristicRule(stat, type, wtype) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class TrianglesRule : public HeuristicRule {
    public:
        TrianglesRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype)
                     :HeuristicRule(stat, type, wtype) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class BalanceBigRule : public HeuristicRule {
    public:
        BalanceBigRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype, vnum_t degreethredhold)
                     :HeuristicRule(stat, type, wtype),degreethredhold_(degreethredhold) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
        vnum_t degreethredhold_;
};

class PreferBigRule : public BalanceBigRule {
    public:
        PreferBigRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype, int buffersize, vnum_t degreethredhold)
                     :BalanceBigRule(stat, type,wtype, degreethredhold),buffsize_(buffersize),remain_(0) {}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
        virtual pid_t EmptyBuffer();
       vector<vid_t> buffer_;
       int remain_;
       int buffsize_;
};

class AvoidBigRule : public PreferBigRule {
    public:
        AvoidBigRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype, int buffersize, vnum_t degreethredhold)
                     :PreferBigRule(stat, type, wtype, buffersize, degreethredhold){}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

class GreedyEvoCutRule : public PreferBigRule {
    public:
        GreedyEvoCutRule(PartitionStatistic& stat, HeuristicRuleType type, WeightType wtype, int buffersize, vnum_t degreethredhold)
                     :PreferBigRule(stat, type,wtype, buffersize, degreethredhold){}
        virtual pid_t MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target);
};

#endif    // #ifndef __HOMOHEURISTIC_H__

