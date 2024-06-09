#pragma once 
#include "openAddressing.hpp"
#include "separateChain.hpp"
#include <vector>
#include <fstream>
#include <math.h>

// zmienna determinujaca load factor w slownikach
// obecnie load factor wynosi 50%
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

    // wektor przechowujacy 10 instancji slownikow o zadanych pojemnosciach
	// load factor wynosi 1/3
    std::vector<openAddressing<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji insert (open addressing) dla " << numElements << " elementow" << std::endl;


	for (int j = 0; j<instances; j++){
		// Ziarno dla pierwszej instancji slownika
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

			start = clock();

			dictionary[j].insert(key, value); 

			duration = clock() - start;

			//dodajemy czasy, aby potem wyciagnac z nich srednia
			// Wraz z przeliczaniem cykli procsora na mikrosekundy (1s = 10^6 us)
			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);

			//usuwanie dodanego elementu (o tym samym kluczu), aby nastepny mogl byc dodany do slownika o takim samym rozmiarze, co na poczatku
			dictionary[j].remove(key);
		}
	}

	
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

    // wektor przechowujacy 10 instancji slownikow o zadanych pojemnosciach
	// load factor wynosi 1/3
    std::vector<openAddressing<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji remove (open addressing) dla " << numElements << " elementow" << std::endl;


	for (int j = 0; j<instances; j++){
		// Ziarno dla pierwszej instancji slownika
		srand(j+1); 
		
		// wypełnianie struktury zadana na wejscu iloscia liczb
		for (int i=0; i<numElements; i++){ 
			key = rand();
			value = rand();
            dictionary[j].insert(key, value);
		}

		srand (instances +1); // osobne ziarno dla liczb dodawanych do struktury
		for (int k=0; k<4; k++){
			key = rand();
			value = rand();

			start = clock();
			// mierzona operacja
			dictionary[j].remove(key); 

			duration = clock() - start;

			//dodajemy czasy, aby potem wyciagnac z nich srednia
			// Wraz z przeliczaniem cykli procsora na mikrosekundy (1s = 10^6 us)
			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);

			//dodawanie "z powrotem" tego samego elementu, aby nastepna operacja mogla zostac wykonana na tym samym slowniku
			dictionary[j].insert(key, value);
		}
	}

	// obliczanie sredniej, z 40 (4*10) pomiarow,
	srednia /= (instances * 4);
	std::string stringSrednia = std::to_string(srednia);
	file << "srednia: \n" << stringSrednia << std::endl;
	file.close();
}


// /*
//     Funkcje pomiarowe dla kubelkow z listami
// */
void separateChainMeasureInsert(int numElements)
{   
    double srednia, duration;
	clock_t start, stop;
	std::ofstream file;
	int key, value;

    // wektor przechowujacy 10 instancji slownikow o zadanych pojemnosciach
	// load factor wynosi 1/3
    std::vector<separateChain<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji insert (separate chaining) dla " << numElements << " elementow" << std::endl;


	for (int j = 0; j< instances; j++){
		// Ziarno dla pierwszej instancji slownika
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

			start = clock();

			dictionary[j].insert(key, value); 

			duration = clock() - start;

			//dodajemy czasy, aby potem wyciagnac z nich srednia
			// Wraz z przeliczaniem cykli procsora na mikrosekundy (1s = 10^6 us)
			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);

			//usuwanie dodanego elementu (o tym samym kluczu)
			//aby następna operacja mogla zostac wykonana na tym samym slowniku
			dictionary[j].remove(key);
		}
	}

	// obliczanie sredniej, z 40 (4*10) pomiarow,
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

    // wektor przechowujacy 10 instancji slownikow o zadanych pojemnosciach
	// load factor wynosi 1/3
    std::vector<separateChain<int, int>> dictionary;
    dictionary.reserve(instances); 
    for (int i = 0; i < instances; ++i) {
        dictionary.emplace_back(numElements * loadFactor);
    }

	file.open("pomiary.csv", std::ios::app);
	file << "Czasy funkcji remove (separate chaining) dla " << numElements << " elementow" << std::endl;


	for (int j = 0; j<instances; j++){
		// Ziarno dla pierwszej instancji slownika
		srand(j+1); 
		
	// 	// wypełnianie struktury zadana na wejscu iloscia liczb
		for (int i=0; i< numElements; i++){ 
			key = rand();
			value = rand();
            dictionary[j].insert(key, value);
		}

		srand (instances + 1); // osobne ziarno dla liczb dodawanych do struktury
		for (int k=0; k < 4; k++){
			key = rand();
			value = rand();

			start = clock();
			// mierzona operacja
			// std::cout << key << std::endl;
			dictionary[j].remove(key); 
			
			duration = clock() - start;

	// 		//dodajemy czasy, aby potem wyciagnac z nich srednia
	// 		// Wraz z przeliczaniem cykli procsora na mikrosekundy (1s = 10^6 us)
			srednia += double(duration)/ CLOCKS_PER_SEC * pow(10.0, 6.0);

	// 		//dodawanie "z powrotem" tego samego elementu, aby nastepna operacja mogla zostac wykonana na tym samym słowniku
			dictionary[j].insert(key, value);
		}
	}

	
	srednia /= (instances * 4);
	std::string stringSrednia = std::to_string(srednia);
	file << "srednia: \n" << stringSrednia << std::endl; 
	file.close();
}