#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__
#include <list>
#include "url.h"
#include <vector>

class BlockingQueue{
    private:
        std::list<Url> url_s;
    public:
        BlockingQueue(std::string& filepath);
        int pop(std::vector<Url>& buffer);
        void push(Url&& url);
        int getSize();
        ~BlockingQueue();
};
#endif
