#include "web_crawler.h"
#include "parser.h"
#include <utility>

WebCrawler::WebCrawler(char* pages_filepath, char* index_filepath){
    this->pages_reader = new PagesReader(pages_filepath);
    std::string aux = index_filepath;
    this->map = new Map(aux);
}

WebCrawler::WebCrawler(WebCrawler&& other){
    this->pages_reader = other.pages_reader;
    this->map = other.map;

    other.pages_reader = nullptr;
    other.map = nullptr;
}

int WebCrawler::fetch(Url* url, char* allowed_domain, std::vector<std::string>& buffer){
    std::string allowed(allowed_domain);
    int offset, size;
    if (this->map->find(url->getUrl(), offset, size) < 0){
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
    delete map;
}