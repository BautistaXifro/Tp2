#include <string>
#include "pages_reader.h"
#include "parser.h"
#include <vector>
#include <iostream>
int main(int argc, char* argv[]){
    std::string filepath = argv[1];

    std::vector<std::string> url_s;
    std::string allowed = argv[2];

    Parser* parser = new Parser(allowed);
    PagesReader* pages_reader = new PagesReader(filepath);

    pages_reader->read(url_s, 0, 12698, *parser);

    for(std::string url : url_s){
        std::cout << url << std::endl;
    }
    return 0;
}