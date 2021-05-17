#include "web_crawler.h"
#include <utility>


WebCrawler::WebCrawler(BlockingQueue& bq, ProtectedMap& m, std::atomic<bool>& mr, char* pages_filepath,
             char* allowed_domain) : protected_queue(bq), protected_map(m), mainReady(mr){
    this->pages_reader = new PagesReader(pages_filepath);
    std::string allowed(allowed_domain);
    this->parser = new Parser(allowed);
}

void WebCrawler::run(){
    Url* url_reference;
    std::vector<std::string> container_url;
    std::vector<std::string> container_state;
    while(!this->mainReady.load()){
        while (protected_queue.getSize() > 0){
            this->protected_queue.pop(url_reference);
            std::vector<std::string> url_s;
            fetch(url_reference, url_s);
            for (auto url_string: url_s){
                this->protected_queue.push(url_string);
            }
            container_url.push_back(url_reference->getUrl());
            container_state.push_back(url_reference->getState());
        }
    }
}

int WebCrawler::fetch(Url* url, std::vector<std::string>& buffer){
    int offset, size;
    if (this->protected_map.find(url->getUrl(), offset, size) < 0){
        url->dead();
        return 0;
    }
    this->pages_reader->read(buffer, offset, size, this->parser);
    url->explored();
    return 0;
}


WebCrawler::~WebCrawler(){
    delete pages_reader;
    delete parser;
}