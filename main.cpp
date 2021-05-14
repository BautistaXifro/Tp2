#include <iostream>
#include <vector>
#include <list>
#include "blocking_queue.h"
#include "web_crawler.h"

int main(int argc, char* argv[]){
    //argv[1] = TARGET
    //argv[2] = ALLOWED
    //argv[3] = INDEX
    //argv[4] = PAGES

    std::string filepath = argv[1];
    BlockingQueue* blocking_queue = new BlockingQueue(filepath);
    WebCrawler* web_crawler = new WebCrawler(argv[4], argv[3]);
    
    Url* url_reference;
    std::list<std::string> container;
    while(blocking_queue->pop(url_reference) == 0){    
        std::vector<std::string> url_s;
        web_crawler->fetch(url_reference, argv[2], url_s);
        for(auto url_string: url_s){
            blocking_queue->push(url_string);
        }
        container.push_back()
        std::cout << url_reference->getUrl() << " -> " << url_reference->getState() << std::endl;
        delete url_reference;
    }
    delete blocking_queue;
    delete web_crawler;
    return 0;
}
