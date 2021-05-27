#ifndef __PROTECTED_protected_map_H__
#define __PROTECTED_protected_map_H__
#include <map>
#include <string>
#include <mutex>
#include <vector>

class ProtectedMap{
    private:
        std::map<std::string, std::vector<int>> protected_map;
        std::mutex protected_map_mutex;
    public:
        explicit ProtectedMap();
        ProtectedMap(ProtectedMap&& other) = delete;
        //opte por no hacer movible esta clase ya que tiene como
        //atributo un mutex y este no se debe mover
        ProtectedMap(const ProtectedMap& other) = delete;
        void insert(std::string& key,std::vector<int>& value);
        int find(std::string url, int& offset, int& size);
        ~ProtectedMap();
};
#endif
