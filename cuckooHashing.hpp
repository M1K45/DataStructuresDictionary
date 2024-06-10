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
    unsigned int capacity_;     // pojemnosc przypadajaca na jedna tablice
    unsigned int size_;         //laczna ilosc elementow w obu tablicach

    // wzkazniki uzyty do tworzenia tablic
    std::pair <K, V>* table_1, * table_2;

    // zmienna pomocnicza sluzaca do oznaczen wolnych miejsc w tablicy 
    int free = -1;

    // zmienna, ktora bedziemy zmieniac w celu zmiany funkcji haszujacej
    // przy wystapieniu cyklu
    int changeHash = 3;

    // licznik krokow wstawiania wraz z ich limitem
    // (po jego przekroczeniu program poznaje, czy jest cykl)
    int counter = 0;
    int limit;

    // flaga podnoszona, kiedy wystapil cykl, zapobiega wykonywaniu rekurencyjnym funkcji cuckoo()
    // wywolywanych przed cyklem

    bool ifCycle = false;
    // int licznikRekurencji =0;

public: 
    cuckooHashing(unsigned int cap): capacity_{cap}, size_{0}
    {
        // tworzenie dwoch tablic: podstawowa i alternatywna
        table_1 = new std::pair<K, V> [capacity_];
        table_2 = new std::pair<K, V> [capacity_];

        // poczatkowo oznacza sie wszystkie indeksy jako puste
        for (int i=0; i < capacity_; i++)
        {
            table_1[i].first = free;
            table_2[i].first = free;
        }

        // inicjalizaja limitu wstawiania
        limit = capacity_ + 4;
    }

    // funkcje haszujace
    int hash_1 (K key)
    {
        return (key + changeHash) % capacity_;
    }

    int hash_2 (K key)
    {
        return (key * changeHash) % capacity_;
    }

    // rehaszowanie (po nastapieniu cyklu)
    void rehash(K newKey, V newValue)
    {
        // inkrementacja zmiennej uzywanej w funkcjach haszujacych
        // w celu zmiany funkcji haszujacej
        // std::cout << "rehaszowano to " << changeHash -2 << " razy\n";
        changeHash ++;

        // tworzenie tablic pomocniczych
        std::pair <K, V>* tempTable_1, * tempTable_2;
        tempTable_1 = new std::pair<K, V> [capacity_];
        tempTable_2 = new std::pair<K, V> [capacity_];

        // kopiowanie elementow 
        for (int i=0; i < capacity_; i++)
        {
            tempTable_1[i].first = table_1[i].first;
            tempTable_1[i].second = table_1[i].second;

            tempTable_2[i].first = table_2[i].first;
            tempTable_2[i].second = table_2[i].second;
        } 


        // czyszczenie oryginalnych tablic
        for (int i=0; i < capacity_; i++)
        {
            table_1[i].first = free;
            table_2[i].first = free;
        }

        // tablice sa teraz puste zmienna przechowujaca ich laczny rozmiar wynosi zero
        size_ = 0;

        // std::cout << "tablica jest pusta\n";

        // reset licznika  
        counter = 0;
        // std::cout << "wartosc licznika: " << counter << "/ 4 "<< std::endl;

        std::cout << "-- dodawnaie w ramach rehaszu --\n";
        // wstawianie par z tablic pomocniczych
        for (int i=0; i < capacity_; i++)
        {
            // jesli element w tablicy pomocniczej nie jest puste, to dadaje sie pare w niej przechowywana
            // do tablicy glownej
            if (tempTable_1[i].first != free)
            {
                // std::cout << "klucz dodawany w ramach rehashu (ze starej tablicy 1): " << tempTable_1[i].first << std:: endl;
                insert(tempTable_1[i].first, tempTable_1[i].second);
            }
            if (tempTable_2[i].first != free)
            {
                // std::cout << "klucz dodawany w ramach rehashu (ze starej tablicy 2): " << tempTable_2[i].first << std:: endl;
                insert(tempTable_2[i].first, tempTable_2[i].second);
            }
        }
        std::cout << "-- koniec dodawania w ramach rehaszu --\n";

        insert(newKey, newValue);


        // usuwanie tablic pomocniczych 
        delete[] tempTable_1;
        delete[] tempTable_2;

        
        // podnoszenie flagi w celu unikniecia ponownych rekurencji
        ifCycle = true;
    
    }

    // logika haszowania kukulczego
    // na wejciu poza kluczem i wartoscia podaje sie:
    // > ilosc wykonan funkcji cuckoo() w ramach jednego insert()
    // > numer tablicy (1 dla glownej, 2 dla alternatywnej), do ktorej przenosi sie element 
    //   po wykonaniu funkcji insert
    void cuckoo (K key, V value, int cnt, int numTab, K newKey, V newValue)
    {
        // sprawdzenie wystapienia cyklu
        std::cout << "wywolanie funkcji cuckoo nr. " << cnt << std::endl;
        if (cnt > limit){ 
            std::cout << "=============wystapil cykl===============\n";
            rehash(newKey, newValue);
            return;
        }

        // jesli przeniesienie ma byc do tablicy alternatywnej        
        if (numTab == 2)
        {
            // indeks klucza dla tablicy glownej - ten sam indeks ma klucz,
            // ktory chcemy przeniesc 
            int index_1 = hash_1(key);

            // std::cout << "przenosimy pare(" << table_1[index_1].first << "  " << table_1[index_1].second << "), ktora zajmuje pole do tablicy 2\n";  


            // indeks tablicy alternatywnej dla przenaszanego elementu
            int cuckooIndex = hash_2(table_1[index_1].first);

            // std:: cout << "docelowy indeks w tablicy " << 2 << " dla (" <<table_1[index_1].first<< "  " << table_1[index_1].second << "): " << cuckooIndex << std::endl;

            // jesli jej indeksie też znajduje sie jakis element
            // sprawdzanie, czy cos jest w drugiej tablicy
            if (table_2[cuckooIndex].first != free){
                // std::cout << "znowu ta ... kukulka\n";

                // jesli tak, to rekurencja

                // zwieksza sie licznik wywolan przeniesienia
                counter ++;
                // std::cout << "wartosc licznika: " << counter << " / 4" << std::endl;

                // i wykonuje sie ta sama funkcje rekurencyjnie dla zastanego elementu
                cuckoo (table_2[cuckooIndex].first, table_2[cuckooIndex].second, counter, 1, newKey, newValue);
                // return;
            } 

            // jesli flaga nie jest podniesiona to nie wystapil cykl - mozna dokonczyc wykonywanie funkcji
            if (!ifCycle)
            {
            table_2[cuckooIndex] = table_1[index_1];

            // a w jego miejsce wstawia sie nowy element
            table_1[index_1] = std::make_pair(key, value);
            
                //  std::cout << "wywolanie funkcji cuckoo nr. " << licznikRekurencji << std::endl;

            // licznikRekurencji ++;

            // std::cout << "wstawiono pare (" << key << "  " << value << ") do tablicy 1 na indeks: " << index_1 << std::endl;           
            size_ ++;
            std::cout << "rozmiar po dodaniu z cuckoo: " <<  size_ << std::endl;


            return;
            
            }
            else return;

        }

        if (numTab == 1)
        {
            int index_2 = hash_2(key);

            // std::cout << "przenosimy pare(" << table_2[index_2].first << "  " << table_2[index_2].second << "), ktora zajmuje pole do tablicy 1\n";  

            // std::cout << "przenosimy pare, ktora zajmuje pole do tablicy 1\n";  


            
            // jesli juz jest tam element to oblicza sie jego indeks w drugiej tablicy
            // i przenosi sie go do niej
            int cuckooIndex = hash_1(table_2[index_2].first);
            // std:: cout << "docelowy indeks w tablicy " << 1 << "dla (" << key << "  " << value << "): " << cuckooIndex << std::endl;

            // sprawdzanie, czy cos jest w drugiej tablicy
            if (table_1[cuckooIndex].first != free){
                // std::cout << "znowu ta ... kukulka\n";

                // jesli tak, to rekurencja
                counter ++;
                // std::cout << "wartosc licznika: " << counter << " / 4" <<std::endl;

                cuckoo (table_1[cuckooIndex].first, table_1[cuckooIndex].second, counter, 2, newKey, newValue);
            } 

            if (!ifCycle)
            {
            table_1[cuckooIndex] = table_2[index_2];

            // a w jego miejsce wstawia sie nowy element


            table_2[index_2] = std::make_pair(key, value);
            
            // std::cout << "wywolanie funkcji cuckoo nr. " << licznikRekurencji << std::endl;
            // licznikRekurencji ++;

            // std::cout << "wstawiono pare (" << key << "  " << value << ") do tablicy 2 na indeks: " << index_2 << std::endl;

            size_ ++;
            std::cout << "rozmiar po dodaniu z cuckoo: " <<  size_ << std::endl;
            
            }


        return;
        }
        

    }


    void insert (K key, V value) override
    {
        ifCycle = false;
        std::cout << "rozmiar przed dodaniem: " <<  size_ << std::endl;

        if (size_ == capacity_ * 2){
            std::cout << "Slownik jest pelny\n";
            return;
        }

        // deklaracja zmiennych do indeksow tablic; odpowiednio glownej i alternatywnej
        int index_1, index_2; 

        // std::cout << "rozpoczynam dodawanie pary (" << key << "  " << value << ")\n";
        // while (1)
        // {
            // haszowanie pierwsza funkcja
             index_1 = hash_1(key);
            // int index_2 = hash_2(key);


            // sprawdzenie, czy wynik prowadzi
            // do wolnego miejsca w pierwszej tablicy
            if (table_1[index_1].first == free) 
            {
                table_1[index_1] = std::make_pair(key, value);
                // std::cout << "wstawiono pare (" << key << "  " << value << ") do tablicy 1 na indeks: " << index_1  << "bez potrzeby cuckoo\n"<< std::endl;
                size_++;
                std::cout << "rozmiar po dodaniu bez cuckoo: " <<  size_ << std::endl;

                return;
            }

            // w przeciwnym razie trzeba zmienic polozenie znajdujacego sie tam elementu
            else
            {   
                // std::cout << "potrzeba cuckoo, para (" << table_1[index_1].first << "  " << table_1[index_1].second << ") zostanie przeniesiona\n";
                cuckoo(key, value, counter, 2, key, value);
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