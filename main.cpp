#include <iostream>
#include <vector>
#include <thread>
#include "protected_queue.h"
#include "web_crawler.h"

int main(int argc, char* argv[]){
    if (argc < 7){
        return 0;
    }

    int max_threads = std::stoi(argv[3]);
    std::string filepath = argv[1];
    std::string index_filepath = argv[4];
    BlockingQueue protected_queue(filepath);
    ProtectedMap protected_map(index_filepath);
    std::atomic<bool> mainReady(false);
    std::vector<Thread*> threads;
    for (int i = 0; i < max_threads; i++){
        threads.push_back(new WebCrawler(protected_queue,
         protected_map, mainReady, argv[5], argv[2]));
    }

    for (int i = 0; i < max_threads; i++) {
        threads[i]->start();
    }

    std::this_thread::sleep_for(std::chrono::seconds(std::stoi(argv[6])));
    mainReady = true;

    for (int i = 0; i < max_threads; i++) {
        threads[i]->join();
        delete threads[i];
    }
    
    protected_queue.print();

    return 0;
}
