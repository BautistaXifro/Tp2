#include "pages_reader.h"
#include <fstream>
#include <iostream>
#include <utility>

PagesReader::PagesReader(char* filepath){
    this->filepath = filepath;
}

PagesReader::PagesReader(PagesReader&& other){
    this->filepath = std::move(other.filepath);

    other.filepath.clear();
}

int PagesReader::read(std::vector<std::string>& url_s, int offset,
                         int size, Parser*& parser){
    std::ifstream pages_file(this->filepath);
    if(!pages_file.is_open()){
        std::cout << "Error al abrir el archivo "
             << filepath << std::endl;
        return -1;
    }
    int finish = 0;
    pages_file.seekg(offset);
    while (finish < size){
        std::string buffer;
        getline(pages_file, buffer);
        if (pages_file.eof()) break;
        finish += buffer.length();
        parser->filterHtmlLine(buffer, url_s);
        if (url_s.size() == 0) continue;
        for (auto it = url_s.begin(); it != url_s.end(); ) {
            if (parser->parseUrl(*it) < 0) {
                it = url_s.erase(it);
            } else {
                ++it;
            }
        }
    }    
    pages_file.close();
    return 0;
}

PagesReader::~PagesReader(){}
