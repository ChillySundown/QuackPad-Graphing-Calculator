#ifndef DARWICH_09_06_ADD_ENTRY
#define DARWICH_09_06_ADD_ENTRY
#include "../includes/array_functions/array_functions.h"

using namespace std;

template<class T>
T* add_entry(T* a, T val, int& size, int& capacity); //Adds entry val to the end of the array //DO THIS FIRST

template<class T>
T* remove_entry(T* a, T val, int& size, int& capacity); //Removes entry val from the array DO THIS FIRST

template<class T>
T* insert_entry(T* a, T val, int i, int& size, int& capacity); //Inserts val at index i

template<class T>
T* erase_entry(T* a, int i, int& size, int& capacity); //Erases value stored at index i;

template<class T>
T* remove_last_entry(T* a, T& item, int& size, int& capacity);

template<class T>
T* add_entry(T* a, T val, int& size, int& capacity) {
    return insert_entry(a, val, size, size, capacity);
}

template<class T>
T* remove_entry(T* a, T val, int& size, int& capacity) {
    int i = search(a, size, val);
    if(i != -1) {
        return erase_entry(a, i, size, capacity);
    }
    else {
        return a;
    }
}

template<class T>
T* insert_entry(T* a, T val, int i, int& size, int& capacity) {
    if(size >= capacity)  {
        capacity *= 2; //Doubles capacity
        a = reallocate(a, size, capacity); //Allocates double the capacity and copies array over to the reallocated space
    }
    shift_right(a, size, i);
    T* add_pos = a + i;
    *add_pos = val;
    //Should I set add_pos to nullptr -- But pointer ceases to exist after function's end so its ok
    return a;
}

template<class T>
T* erase_entry(T* a, int i, int& size, int& capacity) {
    shift_left(a, size, i);
    if(size <= (capacity / 4) && size != 0) {
        capacity /= 2;
        a = reallocate(a, size, capacity);
    }
    return a;
}

template<class T>
T* remove_last_entry(T* a, T& item, int& size, int& capacity) {
    T* last_entry = (a + size) - 1;
    item = *last_entry;
    return erase_entry(a, size-1, size, capacity);
}

#endif 