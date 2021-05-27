#ifndef __WEB_CRAWLER_H__
#define __WEB_CRAWLER_H__
#include "protected_map.h"
#include "pages_reader.h"
#include "url.h"
#include "thread.h"
#include "parser.h"
#include "protected_queue.h"
#include "printer.h"
#include <string>
#include <atomic>
#include <vector>

class WebCrawler : public Thread{
    private:
        ProtectedQueue& protected_queue;
        ProtectedMap& protected_map;
        std::atomic<bool>& mainReady;
        Printer& printer;
        std::string allowed_domain;
        std::string pages_filepath;
    public:
        WebCrawler(ProtectedQueue& protected_queue,
         ProtectedMap& protected_map, std::atomic<bool>& mainReady,
            Printer& printer, char*& pages_filepath, char*& allowed_domain);
        WebCrawler(WebCrawler&& other) = delete;
        WebCrawler(const WebCrawler& other) = delete;
        int fetch(Url* url, std::vector<std::string>& buffer);
        void run() override;
        ~WebCrawler();
};
#endif
