#include "blocking_queue.h"
#include "file_reader.h"
#include <utility>

BlockingQueue::BlockingQueue(std::string& filepath){
    FileReader* file_reader = new FileReader(filepath);
    std::string url_string;
    while(!file_reader->read(url_string)){
        push(Url(url_string));
    }
}

//PRE: el string enviado tiene la forma de una URL.
//Inserta el url enviado al ultimo lugar de la cola.
void BlockingQueue::push(Url&& url){
    //Url url_moved(std::move(url));
    this->url_s.emplace_back(std::move(url));
}

// Devuelve el primer url de la cola.
int BlockingQueue::pop(std::vector<Url>& buffer){
    if(this->url_s.empty()){
        return -1;
    }
    auto it = buffer.begin();
    buffer.insert(it, std::move(this->url_s.front()));
    this->url_s.pop_front();
    return 0;
}

int BlockingQueue::getSize(){
    return this->url_s.size();
}


BlockingQueue::~BlockingQueue(){
    this->url_s.~list();
    delete this;
}
