#ifndef __MAP_H__
#define __MAP_H__
#include <map>
#include <string>

typedef struct dtypes{
    int offset;
    int size;
}dtypes_t;

class Map{
    private:
        std::map<std::string, dtypes_t> map;
    public:
        Map(std::string& index);
        Map(Map&& other);
        int find(std::string url, int& offset, int& size);
        ~Map();
};
#endif
