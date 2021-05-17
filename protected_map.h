#ifndef __PROTECTED_protected_map_H__
#define __PROTECTED_protected_map_H__
#include <map>
#include <string>
#include <mutex>

typedef struct dtypes{
    int offset;
    int size;
}dtypes_t;

class ProtectedMap{
    private:
        std::map<std::string, dtypes_t> protected_map;
        std::mutex protected_map_mutex;
    public:
        explicit ProtectedMap(std::string& index);
        ProtectedMap(ProtectedMap&& other) = delete;
        ProtectedMap(const ProtectedMap& other) = delete;
        int find(std::string url, int& offset, int& size);
        ~ProtectedMap();
};
#endif
