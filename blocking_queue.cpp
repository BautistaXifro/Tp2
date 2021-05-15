#include "blocking_queue.h"
#include "file_reader.h"
#include <utility>

BlockingQueue::BlockingQueue(std::string& target_filepath){
    FileReader* file_reader = new FileReader(target_filepath);
    std::string url_string;
    while(!file_reader->read(url_string)){
        push(url_string);
    }
    delete file_reader;
}

BlockingQueue::BlockingQueue(BlockingQueue&& other){
    this->url_s = std::move(other.url_s);
    
    other.url_s.clear();
}

//PRE: el string enviado tiene la forma de una URL.
//Inserta el url enviado al ultimo lugar de la cola.
void BlockingQueue::push(std::string url_string){;
    this->url_s.push_back(new Url(url_string));
}

// Devuelve el primer url de la cola.
int BlockingQueue::pop(Url*& url_reference){
    if(this->url_s.empty()){
        return -1;
    }
    url_reference = this->url_s.front();
    //OJO QUE NO SE ESTA LLAMANDO AL DESTRUCTOR DE URL
    this->url_s.pop_front();
    return 0;
}

int BlockingQueue::getSize(){
    return this->url_s.size();
}


BlockingQueue::~BlockingQueue(){}
