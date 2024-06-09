#pragma once
#include "dictionary_interface.hpp"
#include <iostream> 
#include <utility>
#include "list.hpp"

template <typename K, typename V>
class separateChain: public Dictionary <K, V> 
{
private: 
    unsigned int capacity_; //pojemnosc tablicy 
    unsigned int size_;     // ilosc elementow w tablicy 

    // // wzkaznik uzyty do tworzenia tablicy o zadanym rozmiarze
    List <K, V>* table;


    int hash (K key){
        return key % capacity_;
    }

public: 
    // konstruktor, za pomocą niego okreslamy rozmiar tablicy
    separateChain(unsigned int cap): capacity_{cap}, size_{0} 
    {
        // tworzenie tablicy, przechowujacej listy, o zadanym rozmiarze
        table = new List<K, V> [capacity_];
    } 

    void insert(K key, V value) override
    {
        // haszowanie klucza na indeks tablicy
        int index = hash (key);

        // Jesli nadpisano wartosc to dzialanie funkcji dobiega konca
        if (table[index].overwrite(key, value))
        {
            return;
        }

        // w przeciwnym razie para jest dodawana na koniec listy 
        else 
        {
        table[index].addEnd(key, value);
        size_ ++;
        }

    }

    V find(K key) override
    {
        // obliczanie indeksu, w ktorym moze byc wartosc
        int index = hash(key);
        // przeszukiwanie listy w poszukiwnaiu wartosci przypisanej do klucza
        // wartosc -1 oznacza brak elementu
        return table[index].findValue(key);
    }

    void remove(K key) override
    {
        int index = hash(key);
        // std::cout << "indeks tablicy, w ktorej moze byc element do usuniecia: " << index << std::endl;
        if (table[index].removeByKey(key)) {
            std::cout << "usunieto\n";
            size_ --;
        }
        // size_ --;
    }

     bool exists(K key) override
     {  
        int index = hash(key);
        return table[index].find(key);

     }
     unsigned int size() override
     {
        return size_;
     }
     bool empty() override
     {
        if (size_ == 0) return true;
        else return false;
     }
     void keys() override
     {
        for(int i =0; i < capacity_; i ++){
            // jesli lista ma jakiekolwiek elementy, to wypisuje sie ich klucze
            if (table[i].size() != 0){
                table[i].displayKeys();
            }
        }
     }
     void values() override
     {
        for(int i =0; i < capacity_; i ++){
            // jesli lista ma jakiekolwiek elementy, to wypisuje sie ich wartosci
            if (table[i].size() != 0){
                table[i].displayValues();
            }
        }
     }

    // funkcja pomocnicza, wyswietlajaca slownik 
    void display() override{
        for (int i=0; i < capacity_; i++){
            if (table[i].size() != 0){
                std::cout << "lista na indeksie " << i << ":\n";
                table[i].display();
            }
            else std::cout << "na indeksie " << i << " jest pusta lista\n";
        }
    }
    
    

    // destruktor 
    ~separateChain() override 
    {
        delete[] table;
    }
};


