#pragma once
#include "dictionary_interface.hpp"
#include <iostream> 
#include <utility>

template <typename K, typename V>

class openAddressing : public Dictionary <K, V> 
{
private: 
    unsigned int capacity; //pojemnosc tablicy 
    unsigned int size_;     // ilosc elementow w tablicy 

    // wzkaznik uzyty do tworzenia tablicy o zadanym rozmiarze
    std::pair <K, V>* table;

    // zmienna pomocnicza sluzaca do oznaczen wolnych miejsc w tablicy 
    int free = -1;

    // zmienna sluzaca jako stala do funkcji hashujacej (linear probing)
    int C = 1;

public: 
    // konstruktor, za pomocą niego definiujemy rozmiar tablicy
    // i inicjalizujemy poczatkowa ilosc elementow
    openAddressing(unsigned int cap): capacity{cap}, size_{0} 
    {
        // tworzenie tablicy o zadanym rozmiarze
        table = new std::pair<K, V> [capacity];
        // wypelnienianie jej kluczami symbolizujacymi wolne miejsca
        for (int i = 0; i < capacity; i++)
        {
            table[i].first = free;
        }
    } 

    // haszowanie klucza, wykorzystujace linear probing
    int hash (K key, int k)
    {
        return ((key % capacity) + k*C ) % capacity;       
    }

    void insert( K key,  V value) override 
    {
        if (size_ == capacity){
            std::cout << "Slownik jest juz zapelniony\n";
            return;
        }
        int k = 0; // ilosc sprawdzonych kubelkow
        int index;
        while(1)
        {
            // haszowanie
            index = hash(key, k);

            // sprawdzenie, czy wynik haszowania prowadzi
            // do wolnego miejsca w tablicy
            if (table[index].first == free) 
            {
                // dotaje wtedy zadana pare
                table[index] = std::make_pair(key, value);
                size_++;
                return;
            }

            // jesli element o zadanym kluczu istnieje, to nadpisuje sie wartosc
            else if (table[index].first == key){
                table[index].second = value;
                return;
            }

            // jesli prowadzi do zajetego, to zwieksza sie ilosc sprawdzanych
            // kubelkow o 1 i znowu haszuje
            k++;
        }
    }

    V find(K key) override 
    {
        int k = 0; 
        int index; 
        
        while (k < capacity) 
        {
            // klucz podany na wejsciu haszuje sie analogicznie jak przy dodawaniu
            index = hash(key, k);

            // sprawdzanie, czy wynik kaszowania prowadzi do docelowego miejsca
            if (table[index].first == key)
            { 
                return table[index].second;
            }

            // jesli obliczony indeks jest indeksem wolnego miejsca, to znaczy, ze podany klucz nie istnieje
            else if (table[index].first == free)
            {
                break;
            }

            // W przeciwnym razie dotarto do zajetego kubelka o kluczu innym niz zadany
            // Mogl byc on jednak dodany przy ktoryms kolejnym wywolaniu funkcji haszujacej
            // wiec zwieksza sie k i podejmuje sie kolejna probe
            k++;
        }
        
        std::cout << "Klucz nie istnieje\n";
        V val = -1;
        return val;
    }

    void remove(K key) override 
    {
        int k = 0;
        int index;
        
        while (k < capacity)
        {
            index = hash(key, k);
            if (table[index].first == key)
            {
                // jesli natrafiono na docelowy klucz, to oznacza sie miejsce, na ktory on wzkazuje na wolne
                table[index].first = free;  
                size_-- ;
                return;
            }

            else if (table[index].first == free) 
            {
                break;
            }

            // Zwiekszanie licznika sprawdzanych kubelkow, analogicznie do funkcji find()
            k++;
        }
        std::cout << "nie znaleziono klucza\n";

    }

    bool exists(K key) override 
    {
        int k = 0;
        int index;
        while (k < capacity) 
        {
            index = hash(key, k);
            
            // zwracanie prawdy przy znalezieniu
            if (table[index].first == key){
                return true;
            }

            // jesli wynik funkcji haszujacej wzkazuje na wolne miejsce,
            // to znaczy, ze klucz nie istnieje
            else if (table[index].first == free){
                return false;
            }
            k++;
        }
        return false;
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
        for (int i = 0; i < capacity; ++i) 
        {
            // wypisywanie wszystkich kluczy zajetych pol
            if (table[i].first != free)
            {
                std::cout << table[i].first << std::endl;
            }
        }
    }

    void values() override {
        for (int i = 0; i < capacity; i++) 
        {
            if (table[i].first != free) {
                // wypisuje wartosci, analogicznie do funkcji powyzej
                std::cout << table[i].second << std::endl;
            }
        }
    }

    // funkcja pomocnicza sluzaca do wyswietlania par klucz-wartosc
    void display() override
    {
        std::cout << "Zawartosc slownika\n";
        for (int i = 0; i < capacity; i++) 
        {
            std::cout << "indeks " << i << "| ";
            if (table[i].first != free) 
            {
                std::cout << "klucz: " << table[i].first <<
                 ", wartosc: " << table[i].second << std::endl;
            }
            else 
            {
                std::cout << "wolne miejsce\n";
            }
        }
        std::cout << std::endl;
    }

    // destruktor 
    ~openAddressing() override 
    {
        delete[] table;
    }
};
