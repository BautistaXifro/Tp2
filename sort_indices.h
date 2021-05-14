#ifndef __SORT_INDICES_H__
#define __SORT_INDICES_H__
#include <string>
#include <vector>

class SortIndices{
   private:
     std::vector<std::string> mparr;
   public:
     SortIndices(std::vector<std::string> parr): mparr(parr){}
     bool operator()(int i, int j) const {return *(mparr.begin() + i) < *(mparr.begin() + j);}
};
#endif
