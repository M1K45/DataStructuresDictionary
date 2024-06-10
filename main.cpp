#include <iostream> 
#include "openAddressing.hpp"
#include "cuckooHashing.hpp"
#include "list.hpp"
#include "separateChain.hpp"
#include "visualize.hpp"
#include "measurment.hpp"

void mainMenu(){
    std::cout << "\n=====MENU GLOWNE====\n";
    std::cout << "Co chcesz zrobic?\n";
    std::cout << "1) Zobaczyc dzialanie slownika na tablicy mieszajacej z adresowaniem otwartym\n";
    std::cout << "2) Zobaczyc dzialanie slownika na kubelkach z lista\n";
    std::cout << "3) Wykonac pomiary operacji insert() i remove() dla obu implementacji\n";
    std::cout << "Wybierz dowolny inny klawisz, aby wyjsc z programu\n";
    std::cout << "\nWpisz numer odpowiadajacy Twojej decyzji: "; 

    int choice; std::cin >> choice;
    int numElements;
    switch (choice)
    {
    case 1:
        menuOpenAddress();
        mainMenu();
    
    case 2: 
        menuSeparateChain();
        mainMenu();

    case 3: 
        std::cout << "Ilosc danych dla ktorej chcesz przeprowadzic pomiary: "; std::cin >> numElements;
        openAddressMeasureInsert(numElements);
        openAddressMeasureRemove(numElements);
        separateChainMeasureInsert(numElements);
        separateChainMeasureRemove(numElements);      
        mainMenu();
    default:
        break;
    }   
}

int main (){
    // mainMenu();
   
        return 0;
}


