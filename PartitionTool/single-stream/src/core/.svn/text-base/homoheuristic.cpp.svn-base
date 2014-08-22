/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月13日 星期四 20时34分56秒
 */

#include <core/type.h>
#include <core/homoheuristic.h>
#include <util/counter.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

using namespace std;


/******************************
 *********Balanced*************
 *****************************/
pid_t
BalancedRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target) {
    vnum_t minvcount, tmp_vcount;
    int partitionnumber = stat_.get_partitionnumber();

    vector<pid_t> reserved;
    pid_t i;

    minvcount = stat_.GetVertexCount(0);
    reserved.push_back(0);
    for(i = 1; i < partitionnumber; i++) {
       tmp_vcount = stat_.GetVertexCount(i);
       if(tmp_vcount < minvcount) {
           minvcount = tmp_vcount;
           reserved.clear();
           reserved.push_back(i);
       }
       else if(tmp_vcount == minvcount) {
           reserved.push_back(i);
       }
    }
    return RandomGetAPid(reserved);
}

/******************************
 * ********Chunk***************
 * ***************************/
pid_t
ChunkRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target) {
    vnum_t vcapacity = stat_.get_vertexcapacity();
    pid_t idx = seq/ vcapacity;
    return idx;
}

/*******************************
 * ***********Hash**************
 * ****************************/
pid_t
HashRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& target) {
    return (source % stat_.get_partitionnumber());
}

/*******************************
 * *****DeterministicGreedy*****
 * ****************************/
pid_t
DeterministicGreedyRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    pid_t idx, i;
    vnum_t vcount = 1<<29;
    double weight;
    double max_weight = -1.0, tmp_weight, eps=1e-5;
    int partitionnumber = stat_.get_partitionnumber(); 
    vector<Counter<vnum_t> > intersection_count(partitionnumber, Counter<vnum_t>());
    vector<pid_t> reserved;
    
    stat_.GetIntersectionCount(num, targets, intersection_count);

    for(i = 0; i < partitionnumber; i++) {
            reserved.push_back(i);
    }
    vnum_t ivcount;
    if(wtype_ == WT_NONE) {
        for(i = 0; i < partitionnumber; i++) {
            if(isvertexcount_)
                ivcount = stat_.GetVertexCount(i);
            else
                ivcount = stat_.GetEdgeCount(i);
         //  if(ivcount >= stat_.get_vertexcapacity()) continue;
            tmp_weight = intersection_count[i];
            if(tmp_weight - max_weight > eps) {
                max_weight = tmp_weight;
                reserved.clear();
                reserved.push_back(i);
                vcount = ivcount;
            }
            else if(fabs(tmp_weight - max_weight) < eps) {
                    if(ivcount < vcount) {
                        vcount = ivcount;
                        reserved.clear();
                        reserved.push_back(i);
                    }
                    else if(ivcount == vcount) {
                        reserved.push_back(i);
                    }
            }
  //          if(tmp_weight > eps && reserved.size() > 1)
   //             Logger(LOG_INFO, "score=%lf, vcount=%d, reservedsize=%d", tmp_weight, vcount, reserved.size());
        }
    }
    else {
            for(i = 0; i < partitionnumber; i++) {
            if(isvertexcount_)
                ivcount = stat_.GetVertexCount(i);
            else
                ivcount = stat_.GetEdgeCount(i);
            //    ivcount = stat_.GetVertexCount(i);
               // if(ivcount >= stat_.get_vertexcapacity()) continue;
                weight = GetWeight(i, wtype_);
			//	fprintf(stderr, "%lf\n", weight);
                tmp_weight = weight * intersection_count[i];
         /*      if(source == 29265|| source==156406) {
                   vnum_t inscount = intersection_count[i];
                   int size = reserved.size();
                   Logger(LOG_INFO, "score=%lf, weight=%lf, ivcount=%d, inscount=%lld", tmp_weight, weight, ivcount,inscount);
               }*/
               if(tmp_weight - max_weight > eps) {
                    max_weight = tmp_weight;
                    reserved.clear();
                    reserved.push_back(i);
                    vcount = ivcount;
                }
                else if(fabs(tmp_weight - max_weight) < eps) {
                  //  vnum_t ivcount = stat_.GetVertexCount(i);
                    /*if(ivcount < vcount) {
                        vcount = ivcount;
                        reserved.clear();
                        reserved.push_back(i);
                    }
                    else if(ivcount == vcount) {*/
                        reserved.push_back(i);
                    //}
                }
/*
               if(source == 29265 || source==156406) {
                   vnum_t inscount = intersection_count[i];
                   int size = reserved.size();
                   Logger(LOG_INFO, "score=%lf, vcount=%d, inscount=%lld, reservedsize=%d", tmp_weight, vcount,inscount, size);
                 //  printf("score=%lf, weight=%lf, vcount=%d, reservedsize=%d\n", tmp_weight, weight, vcount, size);
                  // printf("score=%lf, vcount=%d, reservedsize=%d\n", tmp_weight, vcount, size);
               }*/
            }
    }
   return RandomGetAPid(reserved);
}

pid_t
MinNonNeighborRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    pid_t idx, i;
    vnum_t vcount = 1<<29;
    double weight;
    double min_weight = 1e20, tmp_weight, eps=1e-5;
    int partitionnumber = stat_.get_partitionnumber(); 
    vector<Counter<vnum_t> > nn_count(partitionnumber, Counter<vnum_t>());
    vector<pid_t> reserved;
    
    stat_.GetIntersectionCount(num, targets, nn_count);
    
    for(i = 0; i < partitionnumber; i++) {
       vnum_t nn = stat_.GetVertexCount(i) - nn_count[i];
       ASSERT0(nn>=0);
       //if(nn) {
           weight = GetWeight(i, wtype_);
           tmp_weight = weight * nn;
           if(tmp_weight - min_weight < eps) {
               min_weight = tmp_weight;
               vcount = stat_.GetVertexCount(i);
               reserved.clear();
               reserved.push_back(i);
           }
           else if(fabs(tmp_weight - min_weight) < eps) {
               vnum_t ivcount = stat_.GetVertexCount(i);
               if(ivcount < vcount) {
                   vcount = ivcount;
                   reserved.clear();
                   reserved.push_back(i);
               }
               else if(ivcount == vcount)
                   reserved.push_back(i);
           }
      // }
    }

    return RandomGetAPid(reserved);
    //srand(time(NULL));
    //return reserved[rand() % reserved.size()];    
}

/***********************************
 * ******RandomizedGreedy***********
 * ********************************/
pid_t
RandomizedGreedyRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    return 0;
}

/*********************************
 * **********Triangles************
 * ******************************/
pid_t
TrianglesRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    return 0;
}

/*********************************
 * ********BalanceBig*************
 * ******************************/
pid_t
BalanceBigRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    if(num > degreethredhold_) {
        return BalancedRule(stat_, htype_, wtype_).MakeDecision(seq, source, num, targets);
    }
    else {
        return DeterministicGreedyRule(stat_, htype_, wtype_).MakeDecision(seq, source, num, targets);
    }
}

/********************************
 * ********PreferBig*************
 * ******************************/
pid_t
PreferBigRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    if(num >= degreethredhold_) {
        return BalancedRule(stat_, htype_, wtype_).MakeDecision(seq, source, num, targets);
    }
    else {
        buffer_.push_back(source);
        remain_++;
        if(remain_ >= buffsize_)
            return EmptyBuffer();
    }
    return HeuristicRule::NOT_DECIDED;
}

pid_t
PreferBigRule::EmptyBuffer() {
    //call the deterministic greedy for the low-degree node
    remain_ =0;
    buffer_.clear();
    return HeuristicRule::NOT_DECIDED;
}

/********************************
 * *******AvoidBig***************
 * *****************************/
pid_t
AvoidBigRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    if(num < degreethredhold_) {
        return BalancedRule(stat_, htype_, wtype_).MakeDecision(seq, source, num, targets);
    }
    else {
        buffer_.push_back(source);
        remain_++;
        if(remain_ >= buffsize_)
            return EmptyBuffer();
    }
    return HeuristicRule::NOT_DECIDED;
}

/*******************************
 * ******GreedyEvoCut***********
 * ****************************/
pid_t
GreedyEvoCutRule::MakeDecision(vnum_t seq, vid_t source, int num, vidarray& targets) {
    return 0;
}


