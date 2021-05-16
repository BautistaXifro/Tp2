#include "web_crawler.h"
#include "parser.h"
#include <utility>

WebCrawler::WebCrawler(BlockingQueue& bq, ProtectedMap& m, char* pages_filepath,
             char* allowed_domain) : protected_queue(bq), protected_map(m){
    this->pages_reader = new PagesReader(pages_filepath);
    this->allowed_domain = allowed_domain;
}

/*WebCrawler::WebCrawler(WebCrawler&& other){
    this->pages_reader = other.pages_reader;
    this->protected_map = std::move(other.protected_map);
    this->protected_queue = std::move(other.protected_queue);

    other.pages_reader = nullptr;
    other.protected_map.clear();
    other.protected_queue.clear();
}*/

void WebCrawler::run(){
    Url* url_reference;
    std::vector<std::string> container_url;
    std::vector<std::string> container_state;
    //esta condicion no creo que sea correcta pero para empezar sirve
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

int WebCrawler::fetch(Url* url, std::vector<std::string>& buffer){
    std::string allowed(this->allowed_domain);
    int offset, size;
    if (this->protected_map.find(url->getUrl(), offset, size) < 0){
        url->dead();
        return 0;
    }
    Parser* parser = new Parser(allowed);
    this->pages_reader->read(buffer, offset, size, parser);
    url->explored();
    delete parser;
    return 0;
}


WebCrawler::~WebCrawler(){
    delete pages_reader;
}