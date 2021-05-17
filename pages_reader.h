#ifndef __PAGES_READER_H__
#define __PAGES_READER_H__
#include "parser.h"
#include <vector>
class PagesReader{
    private:
        std::string filepath;
    
    public:
        PagesReader(char* filepath);
        PagesReader(PagesReader&& other);
        PagesReader(const PagesReader& other) = delete;
        int read(std::vector<std::string>& url_s, int offset, int size, Parser*& parser);
        ~PagesReader();
};
#endif
