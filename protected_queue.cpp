#include "protected_queue.h"
#include "file_reader.h"
#include "sort_indices.h"
#include <utility>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

BlockingQueue::BlockingQueue(std::string& target_filepath){
    FileReader* file_reader = new FileReader(target_filepath);
    std::string url_string;
    while (!file_reader->read(url_string)){
        push(url_string);
    }
    delete file_reader;
}

//PRE: el string enviado tiene la forma de una URL.
//Inserta el url enviado al ultimo lugar de la cola.
void BlockingQueue::push(std::string url_string){
    std::unique_lock<std::mutex> lock(this->queue_mutex);
    this->url_s.push_back(new Url(url_string));
    this->cond_var.notify_all();
}

// Devuelve el primer url de la cola.
int BlockingQueue::pop(Url*& url_reference){
    std::unique_lock<std::mutex> lock(this->queue_mutex);
    while (this->url_s.empty()){
       this->cond_var.wait(lock);
    }
    url_reference = this->url_s.front();
    this->container.push_back(this->url_s.front());
    this->url_s.pop_front();
    return 0;
}

void BlockingQueue::print(){
    std::vector<std::string> container_state;
    std::vector<std::string> container_url;
    for (auto url : this->container){
        container_url.push_back(url->getUrl());
        container_state.push_back(url->getState());
    }
    const int indices_count = container_url.size();
    int* indices = new int[indices_count];
    int i = 0;
    for (; i < indices_count; i++){
        indices[i] = i;
    }
    std::sort(indices, indices + i, SortIndices(container_url));
    for (int indice = 0; indice < indices_count; indice++){
        std::cout << container_url.at(indices[indice]) << " -> "
                 << container_state.at(indices[indice]) << std::endl;
    }
    delete[] indices;
}

int BlockingQueue::getSize(){
    return this->url_s.size();
}


BlockingQueue::~BlockingQueue(){
    for (auto url : this->container){
        delete url;
    }
}
