/*
 * genetic thread which warpper the pthread
 * Author: Shao Yingxia
 * Create Date: 2012年12月11日 星期二 08时57分39秒
 */
#ifndef __GTHREAD_H__
#define __GTHREAD_H__

#include <pthread.h>

class GenericThread {
    public:
        GenericThread(int id);
        ~GenericThread();
        void Start();
        void Join();
        virtual void BeforeRun() = 0;
        virtual void Run() = 0;
        virtual void AfterRun() = 0;

        int get_id() { return id_; }
        pthread_t get_thread() { return thread_; }
    private:
        static void*  ThreadEntry(void* args);
    private:
        pthread_t thread_;
        int id_;
	};

#endif    // #ifndef __GTHREAD_H__

