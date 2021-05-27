#include "protected_queue.h"
#include "file_reader.h"
#include "sort_indices.h"
#include "file_manager.h"
#include <utility>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <atomic>

ProtectedQueue::ProtectedQueue(){}

//PRE: el string enviado tiene la forma de una URL.
void ProtectedQueue::push(const std::string& url_string){
    std::unique_lock<std::mutex> lock(this->queue_mutex);
    Url url(url_string);
    this->url_s.emplace_back(std::move(url));
    this->cond_var.notify_all();
}

int ProtectedQueue::pop(Url& url, std::atomic<bool>& mainReady){
    std::unique_lock<std::mutex> lock(this->queue_mutex);
    while (this->url_s.empty() && !mainReady.load()){
       this->cond_var.wait(lock);
    }
    if (mainReady.load()) return 1;
    url = std::move(this->url_s.front());
    this->url_s.pop_front();
    return 0;
}

void ProtectedQueue::close(){
    this->cond_var.notify_all();
}

ProtectedQueue::~ProtectedQueue(){}
