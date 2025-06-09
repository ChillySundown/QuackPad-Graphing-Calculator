#ifndef DARWICH_VECTOR_CLASS
#define DARWICH_VECTOR_CLASS

#pragma once
#include <iostream>
#include <iomanip>
#include "add_entry.h" //Double check these paths!
#include "../includes/array_functions/array_functions.h"

template <class T>
class Vector{
    public:

        Vector(int capacity = 100);
        Vector(T *arr, int size);
        // big three:
        
        Vector(const Vector& v); //COPY CONSTRUCTOR
        void operator=(const Vector& rhs); //Assignment constructor;
        ~Vector(); //Destructor


        //member access functions:
        T& operator [](int index);
        const T& operator [](int index) const;

        T& at(int index);              //return reference to item at position index
        const T& at(int index) const;  //return a const item at position index

        T& front();                         //return item at position 0.
        T& back();                          //return item at the last position


        //Push and Pop functions:
        Vector& operator +=(const T& item); //push_back
        void push_back(const T& item);      //append to the end
        T pop_back();                       //remove last item and return it


        //Insert and Erase:
        void insert(int insert_here, const T& insert_this); //insert at pos
        void erase(int erase_this_index);        //erase item at position
        int index_of(const T& item);             //search for item. retur index.

        //size and capacity:
        void set_size(int size);              //enlarge the vector to this size
        void set_capacity(int capacity);      //allocate this space
        int size() const {return _how_many;}  //return _size
        int capacity() const {return _capacity;} //return _capacity

        bool empty() const;                    //return true if vector is empty

        //OUTPUT:
        template <class U>
        friend ostream& operator <<(ostream& outs, const Vector<U>& _a);
    private:
        T* _vector;
        int _capacity;
        int _how_many;
};
#endif

template<class T>
Vector<T>::Vector(int capacity) {
    _vector = allocate<T>(capacity);
    _capacity = capacity;
    _how_many = 0;
}

template<class T>
Vector<T>::Vector(T* arr, int size) {
    _vector = copy_array<T>(arr, size);
    _how_many = size;
    _capacity = size;
}

template<class T>
Vector<T>::Vector(const Vector& v) { //COPY CONSTRUCTOR
    _capacity = v._capacity;
    _how_many = v._how_many;
    _vector = copy_array<T>(v._vector, v._how_many);
}

template <class T>
void Vector<T>::operator=(const Vector<T>& rhs) {
    if(this == &rhs) {
        return;
    }

    delete[] _vector; //Cleans up dynamic variable

    _capacity = rhs._capacity;
    _how_many = rhs._how_many;
    _vector = copy_array<T>(rhs._vector, rhs._how_many);

}

template <class T>
Vector<T>::~Vector() {
    delete[] _vector;
    _vector = nullptr;
}

template<class T>
T& Vector<T>::operator [](int index) {
    T* spot = _vector + index;
    return *spot;
}

template<class T>
const T& Vector<T>::operator [](int index) const{
    T* spot = _vector + index; //Do we really need to return a const variable?
    return *spot;
}

template<class T>
T& Vector<T>::at(int index) {              //return reference to item at position index
    T* w = _vector + index;
    return *w;
}

template<class T>
const T& Vector<T>::at(int index) const { //return a const item at position index
    T* w = _vector + index; //Should I add a const to this variable?
    return *w;
}

template<class T>
T& Vector<T>::front() {                        //return item at position 0.
    return *_vector;
}

template<class T>
T& Vector<T>::back() {                          //return item at the last position
    T* end_of_arr = _vector + _how_many - 1;
    return *end_of_arr; 
}

template<class T>
Vector<T>& Vector<T>::operator +=(const T& item) { //push_back
        if(_how_many == _capacity) {
            _capacity *= 2;
            _vector = reallocate<T>(_vector, _how_many, _capacity);
        }
        else if(_how_many < _capacity / 2) {
            _capacity /= 2;
            _vector = reallocate<T>(_vector, _how_many, _capacity);
        }
        add_entry(_vector, item, _how_many, _capacity);
        return *this;
}

template<class T>
void Vector<T>::push_back(const T& item) {    //append to the end
    add_entry(_vector, item, _how_many, _capacity);
}

template<class T>
T Vector<T>::pop_back() {                     //remove last item and return it
    T lastItem = T();
    _vector = remove_last_entry(_vector, lastItem, _how_many, _capacity);
    return lastItem;
}

template<class T>
void Vector<T>::insert(int insert_here, const T& insert_this) { //insert at pos
    _vector = insert_entry(_vector, insert_this, insert_here, _how_many, _capacity);
}

template<class T>
void Vector<T>::erase(int erase_this_index) { 
    _vector = erase_entry(_vector, erase_this_index, _how_many, _capacity);   //erase item at position
}

template<class T>
int Vector<T>::index_of(const T& item) {           //search for item. retur index.
    return search(_vector, _how_many, item);
}

template<class T>
void Vector<T>::set_size(int size) {              //enlarge the vector to this size
    _how_many = size;
}

template<class T>
void Vector<T>::set_capacity(int capacity) {      //allocate this space
    _capacity = capacity;
}

template<class T>
bool Vector<T>::empty() const {
    return _how_many == 0;
}

template <class U>
ostream& operator <<(ostream& outs, const Vector<U>& _a) {
    print<U>(_a._vector, _a._how_many, _a._capacity, outs); 
    return outs;
}