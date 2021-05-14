#include <iostream>
#include <vector>
#include <algorithm>
#include "blocking_queue.h"
#include "web_crawler.h"
#include "sort_indices.h"

int main(int argc, char* argv[]){
    //argv[1] = TARGET
    //argv[2] = ALLOWED
    //argv[3] = INDEX
    //argv[4] = PAGES

    std::string filepath = argv[1];
    BlockingQueue* blocking_queue = new BlockingQueue(filepath);
    WebCrawler* web_crawler = new WebCrawler(argv[4], argv[3]);
    
    Url* url_reference;
    std::vector<std::string> container_url;
    std::vector<std::string> container_state;
    while (blocking_queue->pop(url_reference) == 0){
        std::vector<std::string> url_s;
        web_crawler->fetch(url_reference, argv[2], url_s);
        for (auto url_string: url_s){
            blocking_queue->push(url_string);
        }
        container_url.push_back(url_reference->getUrl());
        container_state.push_back(url_reference->getState());
        delete url_reference;
    }
    int indices[container_url.size()];
    int i = 0;
    for (; i < container_url.size(); i++){
        indices[i] = i;
    }
    std::sort(indices, indices+i, SortIndices(container_url));
    for (auto indice : indices){
        std::cout << container_url.at(indice) << " -> " << container_state.at(indice) << std::endl;
    }
    delete blocking_queue;
    delete web_crawler;
    return 0;
}
