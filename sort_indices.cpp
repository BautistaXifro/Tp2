#include "sort_indices.h"
#include <utility>

SortIndices::SortIndices(SortIndices&& other){
    this->mparr = std::move(other.mparr);

    other.mparr.clear();
}
