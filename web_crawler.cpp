#include "web_crawler.h"
#include <utility>
#include <vector>
#include <iostream>


WebCrawler::WebCrawler(ProtectedQueue& bq, ProtectedMap& m,
    std::atomic<bool>& mr, Printer& p,
    const char* pages_filepath, const char* allowed_domain)
    : protected_queue(bq), protected_map(m), mainReady(mr), printer(p){
    this->allowed_domain = allowed_domain;
    this->pages_filepath = pages_filepath;
}

void WebCrawler::run(){
    while (!this->mainReady.load()){
        Url url;
        if (this->protected_queue.pop(url,
                     this->mainReady) == 1) break;
        std::vector<std::string> url_s;
        fetch(&url, url_s);
        for (auto url_string: url_s){
            this->protected_queue.push(url_string);
        }
        this->printer.almacenate(url);
    }
}

int WebCrawler::fetch(Url* url, std::vector<std::string>& buffer){
    int offset, size;
    if (this->protected_map.find(url->getUrl(), offset, size) < 0){
        url->dead();
        return 0;
    }
    PagesReader pages_reader(this->pages_filepath, this->allowed_domain);
    pages_reader.read(buffer, offset, size);
    url->explored();
    return 0;
}


WebCrawler::~WebCrawler(){}
