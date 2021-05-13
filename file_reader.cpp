#include "file_reader.h"
#include "parser.h"


FileReader::FileReader(){}


FileReader::FileReader(std::string& filepath){
    this->file.open(filepath, std::fstream::in);
     if (!file.is_open()) {
        std::cout << "Error al abrir el archivo "
             << filepath << std::endl;
    }
}

bool FileReader::read(std::string& buffer){
    getline(this->file, buffer);
    if(this->file.eof()){
        return true;
    }return false;
}

FileReader::~FileReader(){
    this->file.close();
    delete this;
}
