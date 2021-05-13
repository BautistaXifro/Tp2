#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "file_reader.h"
#include "blockingQueue.h"

int main(int argc, char* argv[]){
    std::string aux = argv[1];
    BlockingQueue* blockingQueue = new BlockingQueue(aux);
    std::string aux2 = blockingQueue->pop();

    while(blockingQueue->getSize() > 0){
        std::cout << blockingQueue->getSize() << std::endl;
    }

    std::cout << aux2 << std::endl;
}