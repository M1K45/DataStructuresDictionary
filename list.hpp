#pragma once

#include <iostream>

/*
    Do implementacji slownika kubelkami z lista zmodyfikowano liste wiazana
    ze wzkaznikami head i tail, napisana na potrzeby Miniprojektu 1
    funkcje Add/Remove Beginning/End oraz display zostaly zmodyfikowane jedynie na potrzeby zamiany wartosci wezla na pare klucz - wartosc
*/
template <typename K, typename V>
struct Node{
    K key;
    V value;
    struct Node *next;
};

template <typename K, typename V>
class List
{
private: 
    Node<K, V> *head_;
    Node<K, V> *tail_;
    int size_;
public:

    List(): head_ {nullptr}, tail_ {nullptr}, size_ {0} {}
    ~List(){
    delete head_, tail_;
}

	void addBeginning(K k, V v)
    {
        Node<K, V> *n = new Node<K, V>;
        n -> key = k;
        n -> value = v;

        n -> next = head_; 

        head_ = n;         

        if (size_ == 0) tail_ = n; 
        size_ ++;
    }

	void removeBeginning(){
        if (size_ == 0){
            std::cout << "struktura juz jest pusta\n";
            return;
        }

        Node<K, V> *old = head_;
        head_ = old -> next;
        delete old;
        size_ --;

        if (size_ == 0){
            head_ = nullptr;
            tail_ = nullptr;
        }
    }

    void addEnd(K k, V v){
        Node<K, V> *n = new Node<K, V>;
        n -> key = k;
        n -> value = v;
        n -> next = nullptr;

        if (size_ == 0) {
            tail_ = n;
            head_ = n;
            size_ ++;
            return;
        }

        tail_ -> next = n;
        tail_ = n;
        size_ ++;

    }

    void removeEnd()
    {
        if (size_ == 0){
            std::cout << "struktura juz jest pusta\n";
            return;
        }
        if (size_ == 1){ 
            head_ = nullptr;
            tail_ = nullptr;
            size_ --;
            return;
        }

        struct Node<K, V> *ptr = nullptr;
        ptr = head_;
        while (ptr -> next -> next !=nullptr){
            ptr = ptr -> next; 
        }
        tail_ = ptr;
        ptr -> next = nullptr;
        size_ --;
    }

    /*
        Funkcje pomocnicze na potrzeby slownika
    */

   // funkcja nadpisujaca wartosc dla istniejacej pary, 
   // na potrzeby slownikowej funkcji insert 
    bool overwrite (K k, V v)
    {
        struct Node<K, V> *ptr = nullptr;
        ptr = head_;

        // wartosc na koncu mozna zamienic w czasie stalym
        // if (tail_ -> key == k){ 
        //     std::cout << "a kuku\n";
        //     tail_ -> value = v;    
        //     return true;
        // }



        // przeszukiwanie listy w celu znalezienia zadanego klucza
        // i nadpisanie przypisanej do niego wartosci
        for (int i=0; i < size_; i++){ 
            if (ptr -> key == k) {
                ptr -> value = v;    
                return true;
            }
            ptr = ptr -> next;
        }
        // std::cout << "nie znaleziono warotsci do nadpisania\n";
        // nie nadpisano wartosci - nalezy dodac nowy wezel z para
        return false;
    }

    // Sprawdzanie, czy element o kluczu k istnieje w liscie
    bool find(K k)
    { 
        struct Node<K, V> *ptr = nullptr;
        ptr = head_;

        // element na koncu mozna znalezc w czasie stalym
        if (tail_ -> key == k)
        { 
            return true;    
        }

        // Przeszukiwanie listy w celu znalezienia klucza
        for (int i=0; i < size_; i++)
        { 
            if (ptr -> key == k) {

                return true;
            }
            ptr = ptr -> next;
        }

        return false;
    }

    // zwracanie wartosci przypisanej do klucza k
    V findValue (K k){
        struct Node<K, V> *ptr = nullptr;
        ptr = head_;

        // wartosc na koncu mozna zwrocic w czasie stalym
        if (tail_ -> key == k){ 
            return tail_ -> value;    
        }

        // przeszukiwanie listy w celu znalezienia zadanego klucza
        // i zwracanie przypisanej do niego wartosci
        for (int i=0; i < size_; i++){ 
            if (ptr -> key == k) {
                return ptr -> value;

            }
            ptr = ptr -> next;
        }

        // jesli nie znaleziono wartosci to przypisuje sie do niej watosc -1
        V val = -1;
        return val;
    }

    // zwracanie true przy znalezieniu klucza, w przeciwnym wypadku false
    bool removeByKey(K k)
    {
        if (size_ == 0){
            std::cout << "lista juz jest pusta\n";
            return false;
        }
        struct Node<K, V> *ptr = nullptr;
        ptr = head_;
        // przeszukiwanie listy w celu znalezienia klucza
        
        if (tail_ -> key == k){
            removeEnd();
            return true;
        }

        while (ptr -> next !=nullptr){

            if (head_ -> key == k)
            {
                removeBeginning();
                return true;
            }
            else {
                if (ptr -> next -> key == k){
                    ptr -> next = ptr -> next -> next;
                    return true;
                }
                else ptr = ptr -> next; 
            }

        }
        return false;
    }

    // wyswietlanie par klucz - wartosc w liscie
    void display()
    {
        if (size_ == 0)
        {
            std::cout << "lista jest pusta\n";
            return;
        }
        struct Node<K, V> *ptr = nullptr;
        ptr = head_;

        while (ptr -> next !=nullptr){
        std::cout << "klucz: " << ptr -> key << ", wartosc: " <<  ptr -> value << std::endl;
        ptr = ptr -> next; 
        }
        std::cout << "klucz: " << ptr -> key << ", wartosc: " <<  ptr -> value << std::endl<< std::endl;
    }

    //Wyswietlanie tylko kluczy
    void displayKeys()
    {
        struct Node<K, V> *ptr = nullptr;
        ptr = head_;

        while (ptr -> next !=nullptr)
        {
        std::cout  << ptr -> key << std::endl;
        ptr = ptr -> next; 
        }
        std::cout << ptr -> key << std::endl<< std::endl;

    }

    //Wyswietlanie tylko wartosci
    void displayValues()
    {
        struct Node<K, V> *ptr = nullptr;
        ptr = head_;


        while (ptr -> next !=nullptr)
        {
            std::cout <<  ptr -> value << std::endl;
            ptr = ptr -> next; 
        }
        std::cout << ptr -> value << std::endl<< std::endl;

    }

    int size(){
        return size_;
    }
};