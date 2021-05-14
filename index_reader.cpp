#include "index_reader.h"
#define INDEX_PARAMETERS 3

static void filter_line(std::string& line, std::string* data, int length);

void IndexReader::read(std::vector<std::string>& url, std::vector<int>& offset,
             std::vector<int>& size){
    std::string line;
    while (!FileReader::read(line)){
        std::string data[INDEX_PARAMETERS];
        filter_line(line, data, INDEX_PARAMETERS);
        url.push_back(data[0]);
        offset.push_back(std::stoi(data[1], nullptr, 16));
        size.push_back(std::stoi(data[2], nullptr, 16));
    }
}

static void filter_line(std::string& line, std::string* data, int length){
    for (int i = 0; i < length; i++){
        char buffer[255];
        std::size_t found_space = line.find(" ");
        std::size_t length = line.copy(buffer, found_space, 0);
        buffer[length] = '\0';
        data[i] = buffer;
        line.erase(0, found_space);
        found_space = line.find("0");
        line.erase(0, found_space);
    }
}

IndexReader::~IndexReader(){}
