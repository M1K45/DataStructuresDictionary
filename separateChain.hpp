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

    // wzkaznik uzyty do tworzenia tablicy list
    List <K, V>* table;

    // funkcja haszujaca
    int hash (K key){
        return key % capacity_;
    }

public: 
    // konstruktor, za pomocą niego okreslamy rozmiar tablicy i inicjalizujemy
    // poczatkowa ilosc elementow
    separateChain(unsigned int cap): capacity_{cap}, size_{0} 
    {
        // tworzenie tablicy, przechowujacej listy o zadanym rozmiarze
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
        // obliczanie indeksu kubelka, w ktorym moze byc wartosc
        int index = hash(key);
        // przeszukiwanie listy w poszukiwnaiu wartosci przypisanej do klucza
        // wartosc -1 oznacza brak elementu w kubelku
        return table[index].findValue(key);
    }

    void remove(K key) override
    {
        // haszowanie klucza
        int index = hash(key);

        //usuwanie (przy pomocy pomocniczej metody listy)
        if (table[index].removeByKey(key)) {
            
            size_ --;
        }
        
    }

     bool exists(K key) override
     {  
        // haszowanie klucza 
        int index = hash(key);
        // przeszukiwanie listy, przy pomocy jej pomocniczej metody
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
            // jesli lista ma jakiekolwiek elementy, to wypisuje sie ich klucze pomocnicza funkcja listy
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


