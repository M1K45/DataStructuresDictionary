#pragma once 

#include <iostream> 
#include "openAddressing.hpp"

#include "list.hpp"
#include "separateChain.hpp"


void menuOpenAddress(){
    openAddressing <int, int>  dictionaryOpen(6);
    std::pair<int, int> pair;
    // dodawanie poczatkowych wartosci, zeby mozna bylo juz na nich wykonywac czesc operacji
    dictionaryOpen.insert(1, 11);
    dictionaryOpen.insert(2, 22);
    dictionaryOpen.insert(3, 33);

    std::cout << "Stworzono przykladowy slownik z dodanymi wartosciami.\n";
    dictionaryOpen.display();

    menu:
    std::cout << "\nKtora funkcje tej implementacji slownika chcesz przetestowac?\n";
    std::cout << "a) insert()\n";
    std::cout << "b) find()\n";
    std::cout << "c) remove()\n";
    std::cout << "d) exists()\n";
    std::cout << "e) size()\n";
    std::cout << "f) empty()\n";
    std::cout << "g) keys()\n";
    std::cout << "h) values()\n";
    std::cout << "i) wypisz cala zawartosc slownik (funkcja pomocnicza)\n";
    std::cout << "Wcisnij dowolny inny znak, aby wyjsc do menu glownego (zmiany na slowniku zostana utracone).\n";
    char operation;
    std::cout << "Wybierz operacje: "; std::cin >> operation;

    switch (operation)
    {
    case 'a':
        std::cout << "\nPodaj nowy klucz: "; std::cin >> pair.first;
        std::cout << "Podaj nowa wartosc: "; std::cin >> pair.second;

        // dodawanie wpisanych przez uzytkownika wartosci do slownika
        dictionaryOpen.insert(pair.first, pair.second);
        std::cout << std::endl;
        // i wypisywanie go, aby pokazac, ze wartosc zostala dodana
        std::cout << "Zawartosc slownika po dodaniu wartosci\n";
        dictionaryOpen.display();

        //przejscie z powrotem do menu
        goto menu;
    
    case 'b': 
        std::cout << "\nPodaj klucz: "; std::cin >> pair.first;
        std::cout << "\nWartosc mapowana przez klucz: " << dictionaryOpen.find(pair.first) << std::endl;
        goto menu;

    case 'c':
        // Wypisywanie zawartosci slownika, aby uzytkownik mogl 
        // wybrac wartosc do usuniecia
        std::cout << "\nZawartosc slownika:\n";
        dictionaryOpen.display(); 

        std::cout << "Podaj klucz elementu, ktorego chcesz usunac: "; std::cin >> pair.first;
        // usuwanie wybranego elementu
        dictionaryOpen.remove(pair.first);
        std::cout << std::endl;
        // wypisywanie slownika, aby pokazac, ze wartosc zostala usunieta
        std::cout << "Zawartosc slownika po usunieciu wartosci\n";
        dictionaryOpen.display();
        goto menu;

    case 'd': 
        std::cout << "\nPodaj klucz: "; std::cin >> pair.first;

        // wypisanie opdowiedniego komunikatu w zaleznosci od wyniku funkcji exists()
        if (dictionaryOpen.exists(pair.first)) std::cout << "Element o takim kluczu znajduje sie w slowniku\n\n";
        else std::cout << "Element o takim kluczu nie znajduje sie w slowniku\n\n";
        goto menu;

    case 'e':
        std::cout << "Ilosc elementow w slowniku: " << dictionaryOpen.size() << std::endl;
        goto menu;

    case 'f': 
        if (dictionaryOpen.empty()) std::cout << "Slownik jest pusty\n";
        else std::cout << "Slownik nie jest pusty\n";
        goto menu;

    case 'g':
        dictionaryOpen.keys();
        goto menu;

    case 'h': 
        dictionaryOpen.values();
        goto menu;

    case 'i':
        dictionaryOpen.display();
        goto menu;

    default:
        break;
    }
}

// menu dla pozostalych implementacji dziala tak samo 
void menuSeparateChain(){

    separateChain <int, int>  dictionaryChain(6);
    std::pair<int, int> pair;

    dictionaryChain.insert(1, 11);
    dictionaryChain.insert(2, 22);
    dictionaryChain.insert(3, 33);
    dictionaryChain.insert(4, 44);
    dictionaryChain.insert(5, 55);
    dictionaryChain.insert(6, 66);
    dictionaryChain.insert(7, 77);
    dictionaryChain.insert(8, 88);
    dictionaryChain.insert(9, 99);

    std::cout << "Stworzono przykladowy slownik z dodanymi wartosciami.\n";
    dictionaryChain.display();

    menu:
    std::cout << "\nJakia funkcje tej implementacji slownika chcesz przetestowac?\n";
    std::cout << "a) insert()\n";
    std::cout << "b) find()\n";
    std::cout << "c) remove()\n";
    std::cout << "d) exists()\n";
    std::cout << "e) size()\n";
    std::cout << "f) empty()\n";
    std::cout << "g) keys()\n";
    std::cout << "h) values()\n";
    std::cout << "i) wypisz cala zawartosc slownik (funkcja pomocnicza)\n";
    std::cout << "Wcisnij dowolny inny znak, aby wyjsc do menu glownego (zmiany na slowniku zostana utracone).\n";
    char operation;
    std::cout << "Wybierz operacje: "; std::cin >> operation;

    switch (operation)
    {
    case 'a':
        std::cout << "\nPodaj nowy klucz: "; std::cin >> pair.first;
        std::cout << "Podaj nowa wartosc: "; std::cin >> pair.second;

        dictionaryChain.insert(pair.first, pair.second);
        std::cout << std::endl;
        dictionaryChain.display();
        goto menu;
    
    case 'b': 
        std::cout << "\nPodaj klucz: "; std::cin >> pair.first;
        std::cout << "\nWartosc mapowana przez klucz: " << dictionaryChain.find(pair.first) << std::endl;
        goto menu;

    case 'c':
        std::cout << "\nZawartosc slownika:\n";
        dictionaryChain.display(); 

        std::cout << "\nPodaj klucz elementu, ktorego chcesz usunac: "; std::cin >> pair.first;
        dictionaryChain.remove(pair.first);
        std::cout << std::endl;
        dictionaryChain.display();
        goto menu;

    case 'd': 
        std::cout << "\nPodaj klucz: "; std::cin >> pair.first;

        if (dictionaryChain.exists(pair.first)) std::cout << "Element o takim kluczu znajduje sie w slowniku\n";
        else std::cout << "Element o takim kluczu nie znajduje sie w slowniku\n";
        goto menu;

    case 'e':
        std::cout << "\nIlosc elementow w slowniku: " << dictionaryChain.size() << std::endl;
        goto menu;

    case 'f': 
        if (dictionaryChain.empty()) std::cout << "\nSlownik jest pusty\n";
        else std::cout << "Slownik nie jest pusty\n";
        goto menu;

    case 'g':
        dictionaryChain.keys();
        goto menu;

    case 'h': 
        dictionaryChain.values();
        goto menu;

    case 'i':
        dictionaryChain.display();
        goto menu;

    default:
        break;
    }
}
