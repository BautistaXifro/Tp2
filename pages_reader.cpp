#include "pages_reader.h"
#include <fstream>
#include <iostream>

PagesReader::PagesReader(std::string& filepath){
    this->filepath = filepath;
}

/*bool PagesReader::read() override{
    cout << "Este es un metodo de FileReader, PagesReader tiene el metodo
            read(vector<string>&, int, int)";
    return false;
}*/

int PagesReader::read(std::vector<std::string>& url_s, int offset, int size, Parser& parser){
    std::ifstream pages_file(this->filepath);
    if(!pages_file.is_open()){
        std::cout << "Error al abrir el archivo "
             << filepath << std::endl;
        return -1;
    }
    int start = 0;
    while(start < size){
        std::string buffer;
        getline(pages_file, buffer);
        if (pages_file.eof()) break;
        if ((start += buffer.length()) < offset) continue;
        parser.filter_html_line(buffer);
        if (buffer.length() == 0) continue;
        if (parser.parseUrl(buffer) < 0) continue;
        auto it = url_s.begin();
        it = url_s.insert(it, buffer);
    }
    pages_file.close();
    return 0;
}

PagesReader::~PagesReader(){
    this->filepath.clear();
    delete this;
}