#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__
#include <string>
#include <fstream>
#include <list>
#include "file_reader.h"
#include "index_reader.h"
#include "protected_queue.h"
#include "protected_map.h"


class FileManager{
    private:
        std::string target_filepath;
        std::string index_filepath;

    public:
        explicit FileManager(const char* target_filepath,
         const char* index_filepath);
        FileManager(FileManager&& other);
        FileManager(const FileManager& other) = delete;
        void fill(ProtectedMap* map);
        void fill(ProtectedQueue* queue);
        ~FileManager();
};
#endif
