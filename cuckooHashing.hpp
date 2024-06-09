#pragma once 
#include "dictionary_interface.hpp"
#include <iostream> 
#include <utility>
#include <cstdlib>
#include <cstring>
#include <string>
template <typename K, typename V>
class cuckooHashing: public Dictionary <K, V> 
{
private: 
    // pojemnosc przypadajaca na jedna tablice
    unsigned int capacity_;

    //laczna ilosc elementow w obu tablicach
    unsigned int size_;
    
    // wzkaznik uzyty do tworzenia tablicy o zadanym rozmiarze
    std::pair <K, V>* table_1, * table_2;

    // zmienna pomocnicza sluzaca do oznaczen wolnych miejsc w tablicy 
    int free = -1;

    // zmienna, ktora bedziemy zmieniac w celu zmiany funkcji haszujacej
    int changeHash = 3;

    // licznik krokow wstawiania
    int counter = 0;

    int licznikRekurencji =0;


public: 
    cuckooHashing(unsigned int cap): capacity_{cap}, size_{0}
    {
        table_1 = new std::pair<K, V> [capacity_];
        table_2 = new std::pair<K, V> [capacity_];

        for (int i=0; i < capacity_; i++)
        {
            table_1[i].first = free;
            table_2[i].first = free;
        }
    }

    int hash_1 (K key)
    {
        return (key * (key + changeHash)) % capacity_;
    }

    int hash_2 (K key)
    {
        return (key * changeHash) % capacity_;
    }

    // bool insertHelper(K key, V value, int count)
    // {
    //     // sprawdzenie, czy wystepuje cykl
    //     if (count > insertionCounter) {
    //         ("Cycle detected");
    //     }

    //     int index1 = hash_1(key);

    //     if (table1[index1].first == EMPTY_KEY
    //      || table1[index1].first == key) {
    //         table1[index1] = std::make_pair(key, value);
    //         return true;
    //     }

    //     std::pair<K, V> temp = std::make_pair(key, value);
    //     std::swap(table1[index1], temp);

    //     size_t index2 = hash2(temp.first);

    //     if (table_2[index2].first == EMPTY_KEY
    //      || table_2[index2].first == temp.first) {
    //         table2[index2] = temp;
    //         return true;
    //     }

    //     std::swap(table2[index2], temp);

    //     return insertHelper(temp.first, temp.second, count + 1);
    // }

    // tworzenie nowych funkcji i uzupełnianie nimi tablicy
    void rehash()
    {
        // inkrementacja zmiennej uzywanej w funkcjach haszujacych
        // w celu zmiany funkcji haszujacej

        std::cout << "rehaszowano to " << changeHash -2 << " razy\n";
        changeHash ++;

        // tworzenie tablic pomocniczych
        std::pair <K, V>* tempTable_1, * tempTable_2;

        tempTable_1 = new std::pair<K, V> [capacity_];
        tempTable_2 = new std::pair<K, V> [capacity_];

        // std::memcpy(tempTable_1, table_1, sizeof(int) * 2 * (size_) );
        // std::memcpy(tempTable_2, table_2, sizeof(int) * 2 * (size_) );
        // kopiowanie recznie elementow 
        for (int i=0; i < capacity_; i++)
        {
            tempTable_1[i].first = table_1[i].first;
            tempTable_1[i].second = table_1[i].second;

            tempTable_2[i].first = table_2[i].first;
            tempTable_2[i].second = table_2[i].second;
        } 


        


        // czyszczenie tablicy glownej
        for (int i=0; i < capacity_; i++)
        {
            table_1[i].first = free;
            table_2[i].first = free;
        }

        std::cout << "tablica jest pusta\n";

                // reset licznika 
        counter = 0;
        std::cout << "wartosc licznika: " << counter << "/ 4 "<< std::endl;

        // wstawianie klucz - wartosc z tablic pomocniczych
        for (int i=0; i < capacity_; i++)
        {
            if (tempTable_1[i].first != free)
            {
                std::cout << "klucz dodawany w ramach rehashu (ze starej tablicy 1): " << tempTable_1[i].first << std:: endl;
                insert(tempTable_1[i].first, tempTable_1[i].second);
            }
            if (tempTable_2[i].first != free)
            {
                std::cout << "klucz dodawany w ramach rehashu (ze starej tablicy 2): " << tempTable_2[i].first << std:: endl;
                insert(tempTable_2[i].first, tempTable_2[i].second);
            }
        }

        

        // usuwanie tablic pomocniczych 
        delete[] tempTable_1;
        delete[] tempTable_2;
    
    }

    // logika haszowania kukulczego
    void cuckoo (K key, V value, int cnt, int numTab)
    {  std::cout << "wywolanie funkcji cuckoo nr. " << licznikRekurencji << std::endl;
        if (cnt > 4){ 
            std::cout << "=============wystapil cykl===============\n";
            rehash();
            return;
        }
        
        if (numTab == 2)
        {
            int index_1 = hash_1(key);

            std::cout << "przenosimy pare(" << table_1[index_1].first << "  " << table_1[index_1].second << "), ktora zajmuje pole do tablicy 2\n";  


           
            // jesli juz jest tam element to oblicza sie jego indeks w drugiej tablicy
            // i przenosi sie go do niej
            int cuckooIndex = hash_2(table_1[index_1].first);
            std:: cout << "docelowy indeks w tablicy " << 2 << " dla (" <<table_1[index_1].first<< "  " << table_1[index_1].second << "): " << cuckooIndex << std::endl;


            // sprawdzanie, czy cos jest w drugiej tablicy
            if (table_2[cuckooIndex].first != free){
                std::cout << "znowu ta ... kukulka\n";

                // jesli tak, to rekurencja
                counter ++;
                std::cout << "wartosc licznika: " << counter << " / 4" << std::endl;

                cuckoo (table_2[cuckooIndex].first, table_2[cuckooIndex].second, counter, 1);
            } 


            if (counter <= 4)
            {
            table_2[cuckooIndex] = table_1[index_1];

            // a w jego miejsce wstawia sie nowy element
            table_1[index_1] = std::make_pair(key, value);
            
                 std::cout << "wywolanie funkcji cuckoo nr. " << licznikRekurencji << std::endl;

            licznikRekurencji ++;

            std::cout << "wstawiono pare (" << key << "  " << value << ") do tablicy 1 na indeks: " << index_1 << std::endl;

            // size_ ++;

            return;
            
            }
            else return;

        }

        if (numTab == 1)
        {
            int index_2 = hash_2(key);

            std::cout << "przenosimy pare(" << table_2[index_2].first << "  " << table_2[index_2].second << "), ktora zajmuje pole do tablicy 1\n";  

            // std::cout << "przenosimy pare, ktora zajmuje pole do tablicy 1\n";  


            
            // jesli juz jest tam element to oblicza sie jego indeks w drugiej tablicy
            // i przenosi sie go do niej
            int cuckooIndex = hash_1(table_2[index_2].first);
            std:: cout << "docelowy indeks w tablicy " << 1 << "dla (" << key << "  " << value << "): " << cuckooIndex << std::endl;

            // sprawdzanie, czy cos jest w drugiej tablicy
            if (table_1[cuckooIndex].first != free){
                std::cout << "znowu ta ... kukulka\n";

                // jesli tak, to rekurencja
                counter ++;
                std::cout << "wartosc licznika: " << counter << " / 4" <<std::endl;

                cuckoo (table_1[cuckooIndex].first, table_1[cuckooIndex].second, counter, 2);
            } 

            if (counter <= 4)
            {
            table_1[cuckooIndex] = table_2[index_2];

            // a w jego miejsce wstawia sie nowy element


            table_2[index_2] = std::make_pair(key, value);
            
            std::cout << "wywolanie funkcji cuckoo nr. " << licznikRekurencji << std::endl;
            licznikRekurencji ++;

            std::cout << "wstawiono pare (" << key << "  " << value << ") do tablicy 2 na indeks: " << index_2 << std::endl;

            // size_ ++;
            
            }


        return;
        }
        

    }


    void insert (K key, V value) override
    {
        int index_1, index_2; 
        std::cout << "rozpoczynam dodawanie pary (" << key << "  " << value << ")\n";
        // while (1)
        // {
            // haszowanie pierwsza funkcja
             index_1 = hash_1(key);
            // int index_2 = hash_2(key);


            // sprawdzenie, czy wynik haszowania prowadzi
            // do wolnego miejsca w pierwszej tablicy
            if (table_1[index_1].first == free) 
            {
                table_1[index_1] = std::make_pair(key, value);
                std::cout << "wstawiono pare (" << key << "  " << value << ") do tablicy 1 na indeks: " << index_1  << "bez potrzeby cuckoo\n"<< std::endl;
                size_++;
                return;
            }

           
            else
            {   
                std::cout << "potrzeba cuckoo, para (" << table_1[index_1].first << "  " << table_1[index_1].second << ") zostanie przeniesiona\n";
                cuckoo(key, value, counter, 2);
                return;
            }


            
        // }
                
    }

    V find (K key) override 
    {
       int index_1 = hash_1(key);
       int index_2 = hash_2(key);

       if (table_1[index_1].first == key)
        { 
            return table_1[index_1].second;
        }

        else if (table_2[index_2].first == key)
        { 
            return table_2[index_2].second;
        }

        std::cout << "Klucz nie istnieje\n";
        V val = -1;
        return val;


    }

    void remove(K key) override 
    {
       int index_1 = hash_1(key);
       int index_2 = hash_2(key);
        
        
        if (table_1[index_1].first == key)
        { 
            table_1[index_1].first = free;
            size_ --; 
            return;
        }

        else if (table_2[index_2].first == key)
        { 
            table_1[index_1].first = free;
            size_ --; 
            return;
        }

        std::cout << "Klucz nie istnieje\n";
    }

    bool exists(K key) override 
    {
       int index_1 = hash_1(key);
       int index_2 = hash_2(key);
        
        
        if (table_1[index_1].first == key)
        { 
            return true;
        }

        else if (table_2[index_2].first == key)
        { 
            return true;
        }

        else return false;
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
        for (int i = 0; i < capacity_; i++) 
        {
            // wypisywanie wszystkich kluczy zajetych pol
            if (table_1[i].first != free)
            {
                std::cout << table_1[i].first << std::endl;
            }
            if (table_2[i].first != free)
            {
                std::cout << table_2[i].first << std::endl;
            }
        }
    }

    void values() override {
        for (int i = 0; i < capacity_; i++) 
        {
            // wypisywanie wszystkich kluczy zajetych pol
            if (table_1[i].first != free)
            {
                std::cout << table_1[i].second << std::endl;
            }
            if (table_2[i].first != free)
            {
                std::cout << table_2[i].second << std::endl;
            }
        }
    }
    
    void display() override
    {
        std::cout << "===================================\n";
        std::cout << "Tablica 1\n";
        for (int i = 0; i < capacity_; i++) 
        {
            std::cout << "indeks " << i << "| ";
            if (table_1[i].first != free) 
            {
                std::cout << "klucz: " << table_1[i].first <<
                 ", wartosc: " << table_1[i].second << std::endl;
            }
            else 
            {
                std::cout << "wolne miejsce\n";
            }
        }
        std::cout << std::endl;

        std::cout << "Tablica 2\n";
        for (int i = 0; i < capacity_; i++) 
        {
            std::cout << "indeks " << i << "| ";
            if (table_2[i].first != free) 
            {
                std::cout << "klucz: " << table_2[i].first <<
                 ", wartosc: " << table_2[i].second << std::endl;
            }
            else 
            {
                std::cout << "wolne miejsce\n";
            }
        }
        std::cout << std::endl;
    }

    ~cuckooHashing() override 
    {
        delete[] table_1;
        delete[] table_2;
    }
};