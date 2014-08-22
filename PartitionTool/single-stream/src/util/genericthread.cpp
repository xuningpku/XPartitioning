/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月11日 星期二 09时04分16秒
 */

#include <util/genericthread.h>

GenericThread::GenericThread(int id)
    :id_(id){
}

GenericThread::~GenericThread() {
}

void
GenericThread::Start() {
    pthread_create(&thread_, NULL, &ThreadEntry, this);
}

void 
GenericThread::Join() {
    pthread_join(thread_, NULL);
}

void*
GenericThread::ThreadEntry(void* args) {
    GenericThread* th = (GenericThread*) args;
    th->BeforeRun();
    th->Run();
    th->AfterRun();
}

