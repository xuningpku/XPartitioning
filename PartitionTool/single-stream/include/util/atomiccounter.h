/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月13日 星期四 09时54分12秒
 */
#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <unistd.h>

/*
 * TODO: Now it counts 32-bits integer.
 * float and double has different implementation.
 */
class AtomicCounter {
    public:
        AtomicCounter() { counter_ = 0; }
        /*return new value*/
        int inc() { __sync_add_and_fetch(&counter_, 1); }
        int dec() { __sync_sub_and_fetch(&counter_, 1); }
        int inc(const int val) { __sync_add_and_fetch(&counter_, val); }
        int dec(const int val) { __sync_sub_and_fetch(&counter_, val); }
        int operator++() { return inc(); }
        int operator--() { return dec(); }
        int operator+=(const int val) { return inc(val); }
        int operator-=(const int val) { return dec(val); }
        
        /*return old value*/
        int inc_ret_last() { __sync_fetch_and_add(&counter_, 1); }
        int dec_ret_last() { __sync_fetch_and_sub(&counter_, 1); }
        int inc_ret_last(const int val) { __sync_fetch_and_add(&counter_, val); }
        int dec_ret_last(const int val) { __sync_fetch_and_sub(&counter_, val); }

        int operator++(int) { return inc_ret_last(); }
        int operator--(int) { return dec_ret_last(); }

        /*cast operator*/
        operator int() const { return counter_; }
        int swap(const int val) { return __sync_lock_test_and_set(&counter_, val); }

    private:
        volatile int counter_;
};

#endif    // #ifndef __COUNTER_H__

