#ifndef DARWICH_MY_STACK_H
#define DARWICH_MY_STACK_H

#include <iostream>
#include "../../includes/linked_list_functions/linked_list_functions.h"
#include "../../includes/node/node.h"

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                //default ctor
        Iterator(node<T>* p){_ptr =p;}          //Point Iterator to where
        T operator*() {  //Not T& because we can't deference nodes and upset order      //dereference operator
            assert(_ptr); 
            return _ptr->_item;
        }

        T *operator->() {                           //member access operator
            assert(_ptr);
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
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, 
                                        const Stack<TT>& printMe);

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};


template <class T>
Stack<T>::Stack() {
    _top = nullptr;
    _size = 0;
}

template <class T>
Stack<T>::Stack(const Stack<T>& copyMe) {
    _top = _copy_list<T>(copyMe._top);
    _size = copyMe._size;
}

template <class T>
Stack<T>::~Stack() {
    _clear_list(_top);
    _top = nullptr;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS) {
    if(this == &RHS) {
        return *this;
    }

    _clear_list(_top);

    _top = _copy_list(RHS._top);
    _size = RHS._size;
    return *this;
}

template <class T>
T Stack<T>::top() {
    return _top->_item;
}

template <class T>
bool Stack<T>::empty() {
    return _size == 0;
}

template <class T>
void Stack<T>::push(T item) {
    _top = _insert_head<T>(_top, item);
    _size++;
}

template <class T>
T Stack<T>::pop() {
    assert(!empty() && _top != nullptr);
    _size--;
    return _delete_node(_top, _top);
    
}

template <class T>
typename Stack<T>::Iterator Stack<T>::begin() const {
    return Iterator(_top);
}

template <class T>
typename Stack<T>::Iterator Stack<T>::end() const {
    return Iterator(nullptr);
}  

template <class TT>
ostream& operator<<(ostream& outs, 
    const Stack<TT>& printMe) {
        _print_list(printMe._top);
        return outs;
}
#endif

