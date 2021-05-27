#include <iostream>
#include <vector>
#include <thread>
#include "protected_queue.h"
#include "web_crawler.h"
#include "file_manager.h"
#include "printer.h"
int main(int argc, char* argv[]){
    if (argc < 7){
        return 0;
    }

    int max_threads = std::stoi(argv[3]);
    FileManager file_manager(argv[1], argv[4]);
    ProtectedQueue protected_queue;
    ProtectedMap protected_map;
    file_manager.fill(&protected_queue);
    file_manager.fill(&protected_map);
    Printer printer;
    std::atomic<bool> mainReady(false);
    std::vector<Thread*> threads;
    
    for (int i = 0; i < max_threads; i++){
        threads.push_back(new WebCrawler(protected_queue,
         protected_map, mainReady, printer, argv[5], argv[2]));
    }

    for (int i = 0; i < max_threads; i++) {
        threads[i]->start();
    }

    std::this_thread::sleep_for(std::chrono::seconds(std::stoi(argv[6])));
    mainReady = true;
    protected_queue.close();

    for (int i = 0; i < max_threads; i++) {
        threads[i]->join();
        delete threads[i];
    }
    
    printer.print();

    return 0;
}
