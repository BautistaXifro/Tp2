#include "map.h"
#include "index_reader.h"
#include "pages_reader.h"

//PRE: Se asegura que el archivo es del estilo "url offset(hexa) size(hexa) \n" 
Map::Map(std::string& index){
    IndexReader* index_reader = new IndexReader(index);
    std::vector<std::string> url_s;
    std::vector<int> offset, size;
    index_reader->read(url_s, offset, size);
    int i = 0;
    for(std::string url : url_s){
        dtypes_t types;
        types.offset = offset.at(i);
        types.size = size.at(i);
        this->map.insert(std::pair<std::string, dtypes_t>(url, types));
        i++;
    }
    delete index_reader;
}


int Map::find(std::string url, int& offset, int& size){
    std::map<std::string, dtypes_t>::iterator iterator = 
            this->map.find(url);
    if (iterator != this->map.end()){
        offset = iterator->second.offset;
        size = iterator->second.size;
        return 0;
    }
    return -1;
}

Map::~Map(){}
