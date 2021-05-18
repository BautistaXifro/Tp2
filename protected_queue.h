#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__
#include <list>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <queue>
#include "url.h"

class BlockingQueue{
    private:
        std::queue<Url*> url_s;
        std::list<Url*> container;
        std::mutex queue_mutex;
        std::condition_variable cond_var;
    public:
        explicit BlockingQueue(std::string& target_filepath);
        BlockingQueue(BlockingQueue&& other) = delete;
        //opte por no hacer movible esta clase ya que tiene como
        //atributo un mutex y un condition_variable
        //ambos no se deben mover
        BlockingQueue(const BlockingQueue& other) = delete;
        int pop(Url*& url_reference);
        void push(std::string url);
        void print();
        int getSize();
        ~BlockingQueue();
};
#endif
