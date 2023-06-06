#ifndef ASD_EASYSET_H
#define ASD_EASYSET_H

#include <unordered_set>

using namespace std;

template<class T> struct set_element {
    T data;

};

template<class T> class easyset_pool {
private:
    unordered_set<T*> pool;
};


#endif //ASD_EASYSET_H
