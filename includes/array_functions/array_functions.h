#ifndef DARWICH__ARRAY_FUNCTIONS_H__
#define DARWICH__ARRAY_FUNCTIONS_H__

#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

using namespace std;

const int MINIMUM_CAPACITY = 3;

template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY);      //allocate 'capacity' 
                                                  //      elements. 
                                                 //  return array

template<class T>
T* reallocate(T* a, int size, int capacity);    //take array, resize it 
                                                //  return new array. 
                                                //  delete old array

template <class T>
void print(T* a, unsigned int how_many, ostream& outs = cout);  //print array

template<class T>
void print_array(T* a, int size, int capacity = 10, ostream& outs = cout);    

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy);  //copy from src to dest

template <class T>
T* copy_array(const T *src, int size);                  //return a 
                                                        //  copy of src

template <class T>
int search(T* a, int size, const T& find_me);

template<class T>
T* search_entry(T* a, int size, const T& find_me);      //search for 'find_me' address

template <class T>
void shift_left(T* a, int& size, int shift_here);       //shift left @ pos:
                                                        //    erases @ pos
template <class T>
void shift_left(T* a, int& size, T* shift_here);
                                                        
template <class T>
void shift_right(T *a, int &size, int shift_here);      //shift right: 
                                                        //      make a hole
template <class T>
void shift_right(T *a, int &size, T* shift_here);

template <class T>
string array_string(const T *a, int size);              //return array 
                                                        //  as a string
int array_size(int* arr); 

template<class T>
void array_init(const T* a , int size, T init_val = T());

template<class T>
T* allocate(int capacity) {
    T* p = new T[capacity];
    return p;
}
template<class T>
T* reallocate(T* a, int size, int capacity) { //Allocates array with new capacity, then copies the old array over
    T* p = allocate<T>(capacity); 
    copy_array(p, a, size);
    delete[] a;
    a = nullptr;
    return p;
}

template <typename T>
void print(T* a, unsigned int how_many, int capacity, ostream& outs) {
    cout << "  ";
    outs << "[";
    T* end_pos = a + how_many;
    T* walker = a;
    // if(*walker == '\0') {
    //     outs << "This array is empty" << endl;
    //     walker = end_pos;
    // }
    for(; walker != end_pos; walker = walker + 1) {
        outs << *walker;
        if(walker + 1 != end_pos) 
            outs << setw(8);
    }
    outs << "]";
}
 
template<class T>
void print_array(T* a, int size, int capacity, ostream& outs) {    //prints 
            outs << "(" << size << "/" << capacity << ")";
            print(a, size, capacity, outs);
            cout << endl;
}                                           

template<class T>
T* search_entry(T* a, int size, const T& find_me) {
    T* walker = a;
    T* end_arr = a + size;
    for(; walker != end_arr; walker = walker + 1) {
        if(*walker == find_me)
            return walker;
    }
    return nullptr;
}


template <class T>
int search(T* a, int size, const T& find_me) {          //search for 'find_me' index 
    int i = 0;                                          //Just use search_entry() and subtract the size from search_entry()
    T* walker = a;
    T* find_me_location = search_entry(a, size, find_me);
    if(find_me_location != nullptr)
        return find_me_location - a;
    else
        return -1;
}         

template <class T>
void shift_left(T* a, int& size, T* shift_here) {
    T* end_of_arr = a + size;
    T* walker = shift_here + 1;
    while(walker != end_of_arr && size > 0) {
        *shift_here = *walker;
        shift_here += 1;
        walker += 1;
    }
    if(size > 0)
        size--;
}

template <class T>
void shift_left(T* a, int& size, int shift_here) {
    T* address = a + shift_here;
    shift_left(a, size, address);
}


template <class T>
void shift_right(T *a, int &size, int shift_here) {
    T* address = a + shift_here;
    shift_right(a, size, address);
}

template <class T>
void shift_right(T *a, int &size, T* shift_here) {
    T* at_right = a + size;
    T* at_left = at_right - 1; //What about empty arrays?
    while(at_right != shift_here && size > 0) {
        *at_right = *at_left;
        at_right -= 1;
        at_left -= 1;
    }
    size++;
}

int array_size(int* arr) {
    int* w = arr;
    int n = 0;
    while(*w != -1) {
        n++;
        w += 1;
    }
    return n;
}

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy) {
    T* dest_walker = dest;
    const T* src_walker = src;
    while(many_to_copy > 0) {
        *dest_walker = *src_walker; //Sets the value at dest to the value at src
        dest_walker = dest_walker + 1; //Increments dest - How do we prevent out of bounds for pointers?
        src_walker = src_walker + 1; 
        many_to_copy--; //Decreases the amount we have to copy
    }
}

template <class T>
T* copy_array(const T *src, int size) {
    T* arr = allocate<T>(size);//Can we use [] when making a dynamic array
    copy_array(arr, src, size);
    return arr; //Returns pointer to new array
}

template <class T>
string array_string(const T *a, int size) {
    const T* walker = a;
    string array_str = "[";
    for(int i = 0; i < size; i++) {
        array_str += to_string(*walker) + " ";
        walker += 1;
    }
    return array_str + "]" + "[" + to_string(size) + "]";
}

template<class T>
void array_init(T* a , int size, T init_val) {
    T* w = a;
    for(; w != a + size; w = w + 1) {
        *w = init_val;
    }
}
#endif 
