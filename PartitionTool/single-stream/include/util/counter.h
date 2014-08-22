/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月13日 星期四 09时54分12秒
 */
#ifndef __COUNTER_H__
#define __COUNTER_H__

/*
 * TODO: Now it counts 32-bits Teger.
 * float and double has different implementation.
 */
template<typename T>
class Counter {
    public:
        Counter():counter_(0) {}
        /*return new value*/
        T inc() { counter_++; return counter_; }
        T dec() { counter_--; return counter_; }
        T inc(const T val) { counter_ += val; return counter_; }
        T dec(const T val) { counter_ -= val; return counter_; }

        T operator++() { return inc(); }
        T operator--() { return dec(); }
        T operator+=(const T val) { return inc(val); }
        T operator-=(const T val) { return dec(val); }
       
        /*return old value*/
        T operator++(int) { T tmp = counter_++; return tmp; }
        T operator--(int) { T tmp = counter_--; return tmp; }

        /*cast operator*/
        operator T() const { return counter_; }

    private:
        volatile T counter_;
};

#endif    // #ifndef __COUNTER_H__

