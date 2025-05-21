#ifndef DARWICH_MY_QUEUE_H
#define DARWICH_MY_QUEUE_H

#include <iostream>
#include "../../includes/linked_list_functions/linked_list_functions.h"
#include "../../includes/node/node.h"
#include <cassert>
template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator() {
           _ptr = nullptr; 
        }                  //default ctor
        Iterator(node<T>* p) { //Point Iterator to where
            _ptr = p;
        }        
        T operator*() {  //Not T& because we can't deference nodes and upset order      //dereference operator
            assert(_ptr != nullptr); 
            return _ptr->_item;
        }

        T *operator->() {                           //member access operator
            assert(_ptr != nullptr);
            return &_ptr->_item;
        }          

        bool is_null() {                        //true if _ptr is NULL
            return _ptr == NULL;
        }               

        friend bool operator!=(const Iterator &left,  //true if left != right
                           const Iterator &right) {
            return !(left._ptr == right._ptr);
        }

        friend bool operator==(const Iterator &left, //true if left == right
                           const Iterator &right) {
            return left._ptr == right._ptr;
        } 

        Iterator &operator++() {                //member operator:
            _ptr = _ptr ->_next;
            return *this;
        }                         
                                                    //  ++it; or
                                                    //  ++it = new_value
        friend Iterator operator++(Iterator &it, //friend operator: it++
                               int unused) {
            node<T>* _hold_ptr = it._ptr;
            it._ptr = it._ptr -> _next;
            return _hold_ptr;
        }     
 
    private:
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers(); 
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <class T>
Queue<T>::Queue() {
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T>& copyMe) {
    _rear = _copy_list(_front, copyMe._front); //Might have to use accessor method
    _size = copyMe.size();
}

template <class T>
Queue<T>::~Queue() {
    _clear_list(_front);
    _rear = nullptr;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS) {
    if(this == &RHS) {
        return *this;
    }

    _clear_list(_front);

    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    return *this;
}

template <class T>
bool Queue<T>::empty() {
    return _size == 0;
}

template <class T>
T Queue<T>::front() {
    return _front->_item;
}

template <class T>
T Queue<T>::back() {
    return _rear->_item;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const {
    return Iterator(_front);
} 

template <class T>
typename Queue<T>::Iterator Queue<T>::end() const {
    return Iterator(nullptr);
}

template <class T>
void Queue<T>::push(T item) {
    if(empty()) {
        node<T>* temp = _insert_head<T>(_front, item);
        _rear = temp;

    }
    else {
        _rear = _insert_after<T>(_front, _rear, item);
    }
    _size++;
}

template <class T>
T Queue<T>::pop() {
    assert(!empty() && _front != nullptr);
    _size--;
    if(_front == _rear) {
        _rear = nullptr;
    }
    return _delete_node(_front, _front);
}

template<typename TT>
ostream& operator<<(ostream& outs, const Queue<TT>& printMe) {
    _print_list(printMe._front);
    return outs;
}

#endif