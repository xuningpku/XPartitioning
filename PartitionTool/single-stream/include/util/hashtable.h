/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月13日 星期四 09时47分55秒
 */
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <map>
#include <iostream>
#include <util/logger.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

/*
 * TODO: Need a scalable and high-cocurrency structure.
 */
template<typename T_Key, typename T_Value>
class HashTable {
    /*
     * TODO: Assume T_Value is integer.
     */
    public:
        typedef typename map<T_Key, T_Value>::iterator HashIter;
        
        static const T_Value NOT_FOUND = -1;
        HashTable() {}
        ~HashTable() {}
        T_Value GetValue(T_Key key) {
            if(table_.find(key) != table_.end()) {
                return table_[key];
            }
            return NOT_FOUND;
        }
        void Insert(T_Key key, T_Value value) {
            if(table_.find(key) == table_.end()) {
                table_[key]=value;
            }
            else {
                Logger(LOG_WARNING,"Duplicated Insert key=%d value=%d!\n", key, value);
            }
        }

        void dump(FILE* fp) {
            if(fp == NULL) {
                for(HashIter it =  table_.begin(); it != table_.end(); it++) {
                    cout <<(*it).first <<" "<<(*it).second <<endl;
                }
            }
            else {
                for(HashIter it =  table_.begin(); it != table_.end(); it++) {
                    fprintf(fp, "%lld %lld\n", (*it).first, (*it).second);
                }
            }
        }

    private:
        map<T_Key, T_Value> table_;
};

#endif    // #ifndef __HASHTABLE_H__

