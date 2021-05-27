#include "protected_map.h"
#include "index_reader.h"
#include "pages_reader.h"
#include <utility>
#include <vector>

//PRE: Se asegura que el archivo es del estilo "url offset(hexa) size(hexa) \n" 
ProtectedMap::ProtectedMap(){}

void ProtectedMap::insert(std::string& key,std::vector<int>& value){
    this->protected_map.insert(std::pair<std::string,
                 std::vector<int>>(key, value));
}

int ProtectedMap::find(std::string url, int& offset, int& size){
    std::unique_lock<std::mutex> lock(this->protected_map_mutex);
    std::map<std::string, std::vector<int>>::iterator iterator = 
            this->protected_map.find(url);
    if (iterator != this->protected_map.end()){
        offset = iterator->second.at(0);
        size = iterator->second.at(1);
        return 0;
    }
    return -1;
}

ProtectedMap::~ProtectedMap(){}
