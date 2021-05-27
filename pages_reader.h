#ifndef __PAGES_READER_H__
#define __PAGES_READER_H__
#include "parser.h"
#include <vector>
#include <string>
class PagesReader{
    private:
        std::string filepath;
        std::string allowed_domain;
    
    public:
        explicit PagesReader(const std::string& filepath,
                     const std::string& allowed_domain);
        PagesReader(PagesReader&& other);
        PagesReader(const PagesReader& other) = delete;
        int read(std::vector<std::string>& url_s,
             int offset, int size);
        ~PagesReader();
};
#endif
