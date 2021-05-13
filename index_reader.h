#ifndef __INDEX_READER_H__
#define __INDEX_READER_H__
#include "file_reader.h"

class IndexReader : public FileReader{
    public:
        IndexReader(std::string& filepath):FileReader(filepath){};
        void read(std::vector<std::string>& url, std::vector<int>& offset,
             std::vector<int>& size);
        ~IndexReader();
};
#endif
