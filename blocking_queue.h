#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__
#include <list>
#include "url.h"
#include <vector>

class BlockingQueue{
    private:
        std::list<Url*> url_s;
    public:
        BlockingQueue(std::string& target_filepath);
        int pop(Url*& url_reference);
        void push(std::string url);
        int getSize();
        ~BlockingQueue();
};
#endif
