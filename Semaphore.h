
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>


class Semaphore {
public:
    Semaphore(int count);

    void acquire();

    void release();

private:
    int count;
    std::mutex mutex;
    std::condition_variable condition;
};




#endif

