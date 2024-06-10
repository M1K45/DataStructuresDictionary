#pragma once
#include <iostream>

template <typename K, typename V>
class Dictionary {
 public:
    // funkcje slownika
    virtual void insert(K key, V value) = 0;
    virtual V find(K key) = 0;
    virtual void remove(K key) = 0;
    virtual bool exists(K key) = 0;
    virtual unsigned int size() = 0;
    virtual bool empty() = 0;
    virtual void keys() = 0;
    virtual void values() = 0;

    // funkcja pomocnicza, wyswietlajaca slownik 
    virtual void display() = 0;
    
    virtual ~Dictionary() {};
};