#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__
#include <list>
#include <mutex>
#include <condition_variable>
#include <string>
#include "url.h"

class ProtectedQueue{
    private:
        std::list<Url> url_s;
        std::list<Url> container;
        std::mutex queue_mutex;
        std::condition_variable cond_var;
    public:
        ProtectedQueue();
        ProtectedQueue(ProtectedQueue&& other) = delete;
        //opte por no hacer movible esta clase ya que tiene como
        //atributo un mutex y un condition_variable
        //ambos no se deben mover
        ProtectedQueue(const ProtectedQueue& other) = delete;
        int pop(Url& url, std::atomic<bool>& mainReady);
        void close();
        void push(const std::string& url);
        void print();
        int getSize();
        ~ProtectedQueue();
};
#endif
