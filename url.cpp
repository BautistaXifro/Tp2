#include "url.h"
#include <utility>

Url::Url(std::string& url){
    this->url = url;
    this->state = "ready";
}

Url& Url::operator=(Url&& other){
    if(this != &other){
        this->url.clear();

        this->url = std::move(other.url);
        this->state = std::move(other.state);

        other.state.clear();
        other.url.clear();
        other.url = nullptr;
    }
}

Url::Url(Url&& other){
    this->url = std::move(other.url);
    this->state = std::move(other.state);

    other.state.clear();
    other.url.clear();
    other.url = nullptr;
}

void Url::dead(){
    this->state = "dead";
}

void Url::explored(){
    this->state = "explored";
}

std::string Url::getState(){
    return this->state;
}

std::string Url::getUrl(){
    return this->url;
}

Url::~Url(){
    this->url.clear();
    this->state.clear();
    delete this;
}