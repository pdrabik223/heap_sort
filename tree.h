
//
//
// Autor: Piotr Drabik				Data: 25.12.2020
#pragma once
#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <vector>
#include <exception>


struct out_of_range :public std::exception { // wyjatek out of range
    const char* what() const throw() {
        return "out of range";
    }
};


// --- iterator over the tree ---

template<typename tree>
class iterator  // iterator dla drzewa dziala na podstawie przeszukiwania drzewa in order
    // iterator bazuje na funkcji next nalezacej do klasy node
    {
public:
    using ValueType = typename tree::ValueType;

    ValueType* current_ptr;


public:

    iterator<tree>(ValueType* x) : current_ptr(x) {};

    iterator<tree>(const iterator<tree>& x) : current_ptr(x.current_ptr) {};
    iterator<tree>& operator=(const iterator<tree>& x) {
        if (this == x) return *this;
        current_ptr(x.current_ptr);

        return *this;
    }
    iterator<tree>& operator++() { // preinkrementacja
        current_ptr = current_ptr->next(current_ptr->get_value());

        return *this;
    };

    iterator<tree> operator++(int) { // postinkrementacja
        iterator<tree> tmp(*this);
        operator++();
        return tmp;
    };


    bool operator==(const iterator<tree>& rhs) const { return current_ptr == rhs.current_ptr; };
    bool operator!=(const iterator<tree>& rhs) const { return current_ptr != rhs.current_ptr; };
    ValueType& operator*() { return *current_ptr; }; // dereferencja
};



// --- TREE ---

template <class T>
class tree {
public:
    using ValueType = node<T>;
public:

    tree<T>();
    tree<T>(const T& value);
    tree<T>(const tree<T>&);
    tree<T>& tree<T>::operator=(const tree<T>&);
    ~tree<T>();

    size_t size();
    void append(const T& value); // dodaje nowa wartosc do drzewa

    void clear(); // usuwa drzewo
    void append_or_replace(const T& value); // dodaje albo zamienia node o podanym value
    T& in_order(const unsigned& counter)  ;
    T& operator[](const T&);

    T& search(const T& value);

    iterator<tree<T>> begin() {
        return iterator<tree<T>>(root);
    };

    iterator<tree<T>> end() {
        return iterator<tree<T>>(nullptr);
    };

protected:
    node<T>* give_root() { return root; };

    node<T>* root;


};



#endif // !TREE_H

template<class T>
inline tree<T>::tree()
{
    root = nullptr;

}

template<class T>
inline tree<T>::tree(const T& value)
{
    root = new node<T>(value);

}

template<class T>
inline tree<T>::tree(const tree<T>& other)
{
    this->root = new node<T>(*other.root);

}

template<class T>
inline tree<T>::~tree()
{
    if (!root) delete root;
}

template<class T>
inline tree<T>& tree<T>::operator=(const tree<T>& other)
{
    if (this == &other) return* this;
    if (other.root) this->root = new node<T>(*other.root);
    else root = nullptr;
    return *this;
}

template<class T>
inline size_t tree<T>::size()
{
    if (root) return root->size();
    else return 0;
}

template<class T>
inline void tree<T>::append(const T& value)
{
    if (root) return root->append(value);
    else root = new node<T>(value);
}

template<class T>
inline void tree<T>::clear()
{
    if(root) delete root;

    else root = nullptr;
}

template<class T>
inline void tree<T>::append_or_replace(const T& value)
{
    if (root) root->append_or_replace(value);
    else root = new node<T>(value);
}

template<class T>
inline T& tree<T>::in_order(const unsigned& counter)
{

    if (root) return root->in_order(counter)->get_value();
    else throw out_of_range();

}

template<class T>
inline T& tree<T>::operator[](const T& value)
{

    if (root)return root->acces_or_asign(value)->get_value();
    else root = new node<T>(value);
    return root->get_value();
}

template<class T>
inline T& tree<T>::search(const T& value)
{
    if (root) {
        auto* ptr_to_return = root->search(value);
        if (ptr_to_return) return ptr_to_return->get_value();
        else throw out_of_range();
    }
    else throw out_of_range();
};