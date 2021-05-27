#include "printer.h"
#include "sort_indices.h"
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

Printer::Printer(){}

Printer::Printer(Printer&& other){
    std::move(other.container.begin(), other.container.end(),
             std::back_inserter(this->container));

    other.container.clear();
}

void Printer::print(){
    std::vector<std::string> container_state;
    std::vector<std::string> container_url;
    for (auto &url : this->container){
        container_url.push_back(url.getUrl());
        container_state.push_back(url.getState());
    }
    const int indices_count = container_url.size();
    int* indices = new int[indices_count]; 
    //mi variable indices_count depende de la cantidad de URLs que 
    //el web crawler haya encontrado es por esto que aloco memoria
    //en el heap ya que no conozco un posible maximo
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

void Printer::almacenate(Url& url){
    std::unique_lock<std::mutex> lock(this->printer_mutex);
    this->container.emplace_back(std::move(url));
}


Printer::~Printer(){}
