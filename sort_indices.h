#ifndef __SORT_INDICES_H__
#define __SORT_INDICES_H__
#include <string>
#include <vector>

class SortIndices{
   private:
     std::vector<std::string> compare_vector;
   public:
     explicit SortIndices(std::vector<std::string>& vector):
                 compare_vector(vector){}
     bool operator()(int i, int j) const {return *(compare_vector.begin() + i) 
          < *(compare_vector.begin() + j);}
};
#endif
