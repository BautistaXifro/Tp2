#include "file_manager.h"
#include <list>
#include <string>
#include <utility>

FileManager::FileManager(char*& target_filepath, char*& index_filepath){
    this->target_filepath = target_filepath;
    this->index_filepath = index_filepath;
}

FileManager::FileManager(FileManager&& other){
    this->target_filepath = std::move(other.target_filepath);
    this->index_filepath = std::move(other.index_filepath);

    other.target_filepath.clear();
    other.index_filepath.clear();
}

void FileManager::fill(ProtectedQueue* queue){
    FileReader file_reader(this->target_filepath);
    std::string url_string;
    while (!file_reader.read(url_string)){
        queue->push(url_string);
    }
}

void FileManager::fill(ProtectedMap* map){
    IndexReader index_reader(this->index_filepath);
    std::vector<std::string> url_s;
    std::vector<int> offset, size;
    index_reader.read(url_s, offset, size);
    int i = 0;
    for (std::string url : url_s){
        std::vector<int> offsetSize;
        offsetSize.push_back(offset.at(i));
        offsetSize.push_back(size.at(i));
        map->insert(url, offsetSize);
        i++;
    }
}

FileManager::~FileManager(){}
