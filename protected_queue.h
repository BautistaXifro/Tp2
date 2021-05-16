#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__
#include <list>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "url.h"

class BlockingQueue{
    private:
        std::list<Url*> url_s;
        std::list<Url*> container;
        std::mutex queue_mutex;
        std::condition_variable cond_var;
    public:
        BlockingQueue(std::string& target_filepath);
        BlockingQueue(BlockingQueue&& other);
        void start(Url*& url_reference);
        int pop(Url*& url_reference);
        void push(std::string url);
        void print();
        int getSize();
        ~BlockingQueue();
};
#endif
