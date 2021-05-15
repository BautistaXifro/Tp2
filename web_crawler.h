#ifndef __WEB_CRAWLER_H__
#define __WEB_CRAWLER_H__
#include "map.h"
#include "pages_reader.h"
#include "url.h"
#include <string>

class WebCrawler{
    private:
        Map* map;
        PagesReader* pages_reader;
    public:
        WebCrawler(char* pages_filepath, char* index_filepath);
        WebCrawler(WebCrawler&& other);
        int fetch(Url* url, char* allowed_domain, std::vector<std::string>& buffer);
        ~WebCrawler();
};
#endif
