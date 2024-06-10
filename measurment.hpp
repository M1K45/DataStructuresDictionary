#pragma once 
#include "openAddressing.hpp"
#include "separateChain.hpp"
#include <vector>
#include <fstream>
#include <math.h>

// uzytkownik w funkcjach pomiarowych podaje ilosc elementow struktury
// ktory przy jej tworzeniu jest mnozony przez ta zmienna
// - determinuje ona wiec load factor - dla wartosci 2 wynosi on 50%
int loadFactor = 2;

// ilosc instancji slownikow danej wielkosci 
int instances = 20;

/*
    funkcje pomiarowe dla tablicy mieszajacej
    z adresowaniem otwartym
*/

void openAddressMeasureInsert(int numElements)
{   
    double srednia, duration;
	clock_t start, stop;
	std::ofstream file;
	int key, value;

    // wektor przechowujacy okreslona na poczatku pliku ilosc instancji slownikow o zadanych pojemnosciach
    std::vector<openAddressing<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	// otwieranie pliku i informacja, co bedzie mierzone
	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji insert (open addressing) dla " << numElements << " elementow" << std::endl;


	for (int j = 0; j<instances; j++){
		// Ziarno dla kazdej kolejnej instancji slownika
		srand(j+1); 
		
		// wypełnianie struktury zadana na wejscu iloscia liczb
		for (int i=0; i<numElements; i++){ 
			key = rand();
			value = rand();
            dictionary[j].insert(key, value);
		}

		srand (instances + 1); // osobne ziarno dla liczb dodawanych do struktury
		for (int k=0; k<4; k++){
			key = rand();
			value = rand();

			// rozpoczencie pomiaru
			start = clock();

			// funkcja, ktorej czas sie mierzy
			dictionary[j].insert(key, value); 

			// zakonczenie pomiaru i zapisanie go w zmiennej
			duration = clock() - start;

			//dodanie czasu do poprzednich, aby potem wyciagnac z nich srednia
			// wraz z przeliczaniem cykli procsora na mikrosekundy (1s = 10^6 us)
			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);

			//usuwanie dodanego elementu (o tym samym kluczu), aby nastepny mogl byc dodany do tego samego slownika, co poprzedni
			dictionary[j].remove(key);
		}
	}

	// obliczanie sredniej i jej zapis
	srednia /= (instances * 4);
	std::string stringSrednia = std::to_string(srednia);
	file << "srednia: \n" << stringSrednia << std::endl;
	file.close();
}

void openAddressMeasureRemove(int numElements)
{   
    double srednia, duration;
	clock_t start, stop;
	std::ofstream file;
	int key, value;

    std::vector<openAddressing<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji remove (open addressing) dla " << numElements << " elementow" << std::endl;

	for (int j = 0; j<instances; j++){

		srand(j+1); 
		
		for (int i=0; i<numElements; i++){ 
			key = rand();
			value = rand();
            dictionary[j].insert(key, value);
		}

		srand (instances +1); 
		for (int k=0; k<4; k++){
			key = rand();
			value = rand();

			start = clock();
			// mierzona operacja
			dictionary[j].remove(key); 

			duration = clock() - start;

			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);

			//dodawanie "z powrotem" tego samego elementu, aby nastepna operacja mogla zostac wykonana na tym samym slowniku
			dictionary[j].insert(key, value);
		}
	}

	// obliczanie sredniej i zapis jej do pliku
	srednia /= (instances * 4);
	std::string stringSrednia = std::to_string(srednia);
	file << "srednia: \n" << stringSrednia << std::endl;
	file.close();
}


// /*
//     Funkcje pomiarowe dla kubelkow z listami
// 		sa one napisane analogicznie do tych dla adresowania otawrtego
// */
void separateChainMeasureInsert(int numElements)
{   
    double srednia, duration;
	clock_t start, stop;
	std::ofstream file;
	int key, value;

    std::vector<separateChain<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji insert (separate chaining) dla " << numElements << " elementow" << std::endl;


	for (int j = 0; j< instances; j++){

		srand(j+1); 
		
		for (int i=0; i<numElements; i++){ 
			key = rand();
			value = rand();
            dictionary[j].insert(key, value);
		}

		srand (instances + 1); 
		for (int k=0; k<4; k++){
			key = rand();
			value = rand();

			start = clock();
			dictionary[j].insert(key, value); 
			duration = clock() - start;

			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);
			dictionary[j].remove(key);
		}
	}

	srednia /= (instances * 4);
	std::string stringSrednia = std::to_string(srednia);
	file << "srednia: \n" << stringSrednia << std::endl;
	file.close();
}

void separateChainMeasureRemove(int numElements)
{   
    double srednia, duration;
	clock_t start, stop;
	std::ofstream file;
	int key, value;

    std::vector<separateChain<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji remove (separate chaining) dla " << numElements << " elementow" << std::endl;

	for (int j = 0; j<instances; j++){
		srand(j+1); 
		
		for (int i=0; i< numElements; i++){ 
			key = rand();
			value = rand();
            dictionary[j].insert(key, value);
		}

		srand (instances + 1);
		for (int k=0; k < 4; k++){
			key = rand();
			value = rand();

			start = clock();
			dictionary[j].remove(key); 
			duration = clock() - start;

			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);
			dictionary[j].insert(key, value);
		}
	}

	
	srednia /= (instances * 4);
	std::string stringSrednia = std::to_string(srednia);
	file << "srednia: \n" << stringSrednia << std::endl; 
	file.close();
}