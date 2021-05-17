#include "protected_map.h"
#include "index_reader.h"
#include "pages_reader.h"
#include <utility>

//PRE: Se asegura que el archivo es del estilo "url offset(hexa) size(hexa) \n" 
ProtectedMap::ProtectedMap(std::string& index){
    IndexReader* index_reader = new IndexReader(index);
    std::vector<std::string> url_s;
    std::vector<int> offset, size;
    index_reader->read(url_s, offset, size);
    int i = 0;
    for(std::string url : url_s){
        dtypes_t types;
        types.offset = offset.at(i);
        types.size = size.at(i);
        this->protected_map.insert(std::pair<std::string, dtypes_t>(url, types));
        i++;
    }
    delete index_reader;
}

int ProtectedMap::find(std::string url, int& offset, int& size){
    std::unique_lock<std::mutex> lock(this->protected_map_mutex);
    std::map<std::string, dtypes_t>::iterator iterator = 
            this->protected_map.find(url);
    if (iterator != this->protected_map.end()){
        offset = iterator->second.offset;
        size = iterator->second.size;
        return 0;
    }
    return -1;
}

ProtectedMap::~ProtectedMap(){}