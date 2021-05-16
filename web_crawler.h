#ifndef __WEB_CRAWLER_H__
#define __WEB_CRAWLER_H__
#include "protected_map.h"
#include "pages_reader.h"
#include "url.h"
#include "thread.h"
#include "protected_queue.h"
#include <string>

class WebCrawler : public Thread{
    private:
        BlockingQueue& protected_queue;
        ProtectedMap& protected_map;
        PagesReader* pages_reader;
        char* pages_filepath;
        char* allowed_domain;
    public:
        WebCrawler(char* pages_filepath, char* index_filepath);
        WebCrawler(BlockingQueue& protected_queue, ProtectedMap& protected_map,
                 char* pages_filepath, char* allowed_domain);
        WebCrawler(WebCrawler&& other);
        int fetch(Url* url, std::vector<std::string>& buffer);
        void run();
        ~WebCrawler();
};
#endif
