/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月19日 星期三 00时01分05秒
 */
#ifndef __NODECONFIG_H__
#define __NODECONFIG_H__

#include <core/type.h>
#include <sstream>
#include <map>

using namespace std;

class NodeConfig {
    public:
        NodeConfig() {};
        ~NodeConfig() {};

        void AddBandWidth(pid_t id, double bw) {
            if( bandwidth_.find(id) != bandwidth_.end() ){
                Logger(LOG_WARNING, "Duplicated Addition. And It is treated as update.");
            }
            bandwidth_[id] = bw;
        }
        
        void set_cpucost(double cc) { cpuspeed_ = cc; }
        double get_cpucost() { return cpuspeed_; }
        double get_bandwidth(pid_t i) { 
            if(bandwidth_.find(i) == bandwidth_.end())
                return 0.0;
            return bandwidth_[i]; 
        }
       
        void set_capacity(double vc) { capacity_=vc; }
        double get_capacity() { return capacity_;}

        string toString() {
            stringstream oss;
            oss <<"capacity: "<<capacity_;
            oss <<",cpucost: "<<cpuspeed_<<",iocost: ";
            map<pid_t, double>::iterator it;
            for(it = bandwidth_.begin(); it != bandwidth_.end(); it++) {
                oss <<"("<<it->first <<","<<it->second<<") ";
            }
            return oss.str();
        }

    private:
        //single node capability
        double cpuspeed_;
        double capacity_;
        //network IO
        map<pid_t, double> bandwidth_;//the large is worser.
};

#endif    // #ifndef __NODECONFIG_H__

