#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "blocking_queue.h"
#include "map.h"

int main(int argc, char* argv[]){
    //esto es para leer el hexadecimal
    //int prueba = std::stoi(argv[1], nullptr, 16);;
    //std::cout << prueba << "\n";

    std::string filepath = argv[1];
    std::string allowed = argv[2];
    std::string index =  argv[3];
    std::string url_string;
    std::string prueba_index;
    Parser* parser = new Parser(allowed);
    BlockingQueue* blockingQueue = new BlockingQueue(filepath);
    Map* map = new Map(index);

    std::vector<Url> url_s;
    if (blockingQueue->getSize() > 0){
        blockingQueue->pop(url_s);
    }


    int offset, size;
    map->fetch(url_s[0].getUrl(), offset, size);

    std::cout << offset << std::endl;
    std::cout << size << std::endl;

    std::cout << url_s[0].getUrl() << std::endl;

    if (parser->parseUrl(url_s[0].getUrl()) == 0){
        std::cout << "URL OK\n";
        url_s[0].explored();
    }else{
        std::cout << "URL BAD\n";
        url_s[0].dead();
    }

    std::cout << url_s[0].getState() << std::endl;
    return 0;
}
