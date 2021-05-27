#include "pages_reader.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <string>

PagesReader::PagesReader(const std::string& filepath,
             const std::string& allowed_domain){
    this->filepath = filepath;
    this->allowed_domain = allowed_domain;
}

PagesReader::PagesReader(PagesReader&& other){
    this->filepath = std::move(other.filepath);
    this->allowed_domain = std::move(other.allowed_domain);

    other.filepath.clear();
    other.allowed_domain.clear();
}

int PagesReader::read(std::vector<std::string>& url_s, int offset,
                         int size){
    std::ifstream pages_file(this->filepath);
    if (!pages_file.is_open()){
        std::cout << "Error al abrir el archivo "
             << filepath << std::endl;
        return -1;
    }
    int finish = 0;
    pages_file.seekg(offset);
    while (finish < size){
        std::string buffer;
        Parser parser(this->allowed_domain);
        getline(pages_file, buffer);
        if (pages_file.eof()) break;
        finish += buffer.length();
        parser.filterHtmlLine(buffer, url_s);
        if (url_s.size() == 0) continue;
        for (auto it = url_s.begin(); it != url_s.end(); ) {
            if (parser.parseUrl(*it) < 0) {
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
