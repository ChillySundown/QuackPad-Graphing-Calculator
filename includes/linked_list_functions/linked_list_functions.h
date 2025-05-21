#ifndef DARWICH_LINKED_LIST_FUNCTIONS_H
#define DARWICH_LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../../includes/node/node.h"

using namespace std;

//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(const node<ITEM_TYPE>* head);

//recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                                ITEM_TYPE key);

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                                const ITEM_TYPE insert_this);

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                 node<ITEM_TYPE> *after_this,
                                 const ITEM_TYPE insert_this);

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                  node<ITEM_TYPE>* before_this,
                                  ITEM_TYPE insert_this);

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                  node<ITEM_TYPE>* prev_to_this);

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                         node<ITEM_TYPE>* delete_this);

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

    //duplicate list and return the last node of the copy
    template <typename T>
    node<T> *_copy_list(node<T>* &dest, node<T> *src);


    //delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head);

    //_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    //      Sorted List Routines. order: 0: ascending, order: other: descending
    //                              Assume a Sorted List
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                  ITEM_TYPE item,
                                  bool ascending=true);

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending=true);
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);            //never use this function.

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src);



//---------------
//BEGINNNING OF FUNCTION IMPLEMENTATION
//---------------
template <typename ITEM_TYPE>
void _print_list(const node<ITEM_TYPE>* head) {
    const node<ITEM_TYPE>* w = head;
    while(w != nullptr) {
        cout << *w;
        w = w->_next;
    }
    cout << "|||" << endl;

}

template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head) {
    const node<ITEM_TYPE>* w = head;
    while(w != nullptr) {
        _print_list_backwards(w->_next);
    }    
    if(w == nullptr) {
        cout << "|||";
    }
    else {
        cout << *w;
    }
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, const ITEM_TYPE insert_this) {
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this, head);
    head = temp;
    return temp;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key) {
    node<ITEM_TYPE>* w = head;
    while(w != nullptr) {
        if(w -> _item == key) { //Checks to see if the item held the current node is the target value
            return w;
        }
        w = w -> _next;
    }
    return nullptr;
}

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this) {
    if(head == prev_to_this) {
        return nullptr;
    }
    node<ITEM_TYPE>* w = head;
    while(w != nullptr) {
        if(w -> _next == prev_to_this) {
            return w;
        }
        w = w->_next;
    }
    assert(false);
}

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* after_this, const ITEM_TYPE insert_this) {
    if(after_this == nullptr) { //We can't insert after nullptr because that symbolizes the end of the list
        return nullptr;
    }
    node<ITEM_TYPE>* insert = new node<ITEM_TYPE>(insert_this, after_this->_next);
    after_this->_next = insert;
    return insert;
}

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this) {
    if(head == before_this) {
        return _insert_head(head, insert_this);
    }
    else {
        node<ITEM_TYPE>* prev = _previous_node<ITEM_TYPE>(head, before_this);
        return _insert_after(head, prev, insert_this);
    }
}

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this) {
    ITEM_TYPE temp = delete_this->_item;
    if(head == delete_this) {
        head = head->_next;
    }
    else {
        _previous_node(head, delete_this)->_next = delete_this->_next;
    }

    delete delete_this;
    delete_this = nullptr;
    return temp;
}

//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head) {
    node<ITEM_TYPE>* w = head;
    while(w != nullptr) {
        _delete_node(head, w);
        w = head;
    }
    head = nullptr;
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos) {
    node<ITEM_TYPE>* w = head;
    for(int k = 0; k < pos; k++) {
        w = w->_next;
    }
    return w->_item;
}

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head) {
    if(head == nullptr) {
        return nullptr;
    }
    node<ITEM_TYPE>* cHead = new node<ITEM_TYPE>(head ->_item);
    node<ITEM_TYPE>* w1 = head -> _next;
    node<ITEM_TYPE>* w2 = cHead;
    while(w1 != nullptr) {
        _insert_after<ITEM_TYPE>(cHead, w2, w1->_item);
        w1 = w1->_next;
        w2 = w2->_next;
    }
    return cHead;
}

//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head) {
    return _previous_node<ITEM_TYPE>(head, nullptr);
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src) {
   dest = _copy_list<T>(src);
   node<T>* w = dest;
   while(w->_next != nullptr) {
        w = w->_next;
   }
   return w;
}

#endif