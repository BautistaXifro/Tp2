#ifndef __FILE_READER_H__
#define __FILE_READER_H__
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileReader {
    private:
        std::ifstream file;
    public:
        FileReader(std::string& filepath);
        FileReader(FileReader&& other);
        FileReader(const FileReader& other) = delete;
        bool read(std::string& buffer);
        virtual ~FileReader();
};
#endif
