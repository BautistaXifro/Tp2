#ifndef __INDEX_READER_H__
#define __INDEX_READER_H__
#include "file_reader.h"
#include <utility>
#include <string>
#include <vector>

class IndexReader : public FileReader{
    public:
        explicit IndexReader(std::string& filepath):FileReader(filepath){}
        IndexReader(const IndexReader& other) = delete;
        IndexReader(IndexReader&& other):FileReader(std::move(other)){}
        void read(std::vector<std::string>& url, std::vector<int>& offset,
             std::vector<int>& size);
        ~IndexReader();
};
#endif
