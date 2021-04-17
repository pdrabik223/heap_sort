//
// author : Piotr Drabik				Data: 24.12.2020
#ifndef NODE_H
#define NODE_H

#include <assert.h>

template<class T>
class node {
public:
    using node_ptr = node<T> *;
    using node_ref = node<T> &;

    enum Color {
        red = 0,
        black = 1
    };


    node();

    node(T);

    node(node_ptr, Color, T);

    node<T> &operator=(const node<T> &);

    node(const node<T> &);

    node_ptr search(const T &);

    node_ptr acces_or_asign(const T &);


    node_ptr end(); // zwraca adres ostatniego elementu w kolejnosci przeszukiwania "In order"
    node_ptr next(const T &previous_value);// zwraca adres kolejnego elementu wzgledem przeszukiwania "In order"
    node_ptr in_order(unsigned &); // zwraca n-ty element w kolejnoœci "In order"
    // inaczej zwraca nullptr
    size_t size(); // zwraca ilosc wezlow w drzewie
    size_t size_depth(size_t partial_depth = 0);

    void append(const T &value);// dodaje node o danym value

    void append_or_replace(const T &value); // dodaje albo zamienia w miejscu value

    T *show_slice(size_t from_top, size_t index, T **array) {

        if (from_top == 0) {
            array[index] = this;
            return;
        }
        if (left)
            left->show_slice(from_top - 1, index, array);
        else
            for (int i = 0; i < pow(2, from_top); i++) array[index + i] = nullptr;

        if (right)
            right->show_slice(from_top - 1, index + 1, array);
        else
            for (int i = 0; i < pow(2, from_top); i++) array[index + i] = nullptr;

    }

    T &get_value(); // zwraca wartosc noda jako referencje
    ~node();

protected:

    T value; // wartosc przechowywana przez wezel
    Color color; // kolor wezla
    node_ptr father; // wskaznik na ojca wwezla
    node_ptr left; // wskaznik na wezel o mniejszym value
    node_ptr right; //  wskaznik na wezel o wiekszym value

};

template<class T>
inline node<T>::node()

        :father(nullptr),
         left(nullptr),
         right(nullptr),
         color(node<T>::black),
         value(NULL) {}


template<class T>
inline node<T>::node(T value) {
    father = nullptr;
    left = nullptr;
    right = nullptr;
    color = node<T>::black;
    this->value = value;

}


template<class T>
inline node<T>::node(node<T> *father, Color color, T value) {
    this->father = father;
    left = nullptr;
    right = nullptr;
    this->color = color;
    this->value = value;

}

template<class T>
inline node<T> &node<T>::operator=(const node<T> &other) {

    if (this == &other) return *this;
    father = nullptr;

    color = other.color;
    value = other.value;

    if (!other.left)left = new node<T>(other.left);   // todo this shiet is crazy
    if (!other.right)right = node<T>(other.right);
    return *this;
}


template<class T>
inline node<T>::node(const node<T> &other) {
    father = nullptr;

    color = other.color;
    value = other.value;

    if (other.left) {
        left = new node<T>(*other.left);
        left->father = this;
    } else left = nullptr;
    if (other.right) {
        right = new node<T>(*other.right);
        right->father = this;
    } else right = nullptr;

}

template<class T>
inline node<T> *node<T>::search(const T &value) {
    if (this->value == value) return this;

    node<T> *ptr_to_return = nullptr;

    if (value < this->value && left) ptr_to_return = left->search(value);

    if (value > this->value && right) ptr_to_return = right->search(value);

    return ptr_to_return;
}

template<class T>
inline node<T> *node<T>::acces_or_asign(const T &value) {
    if (value == this->value) return this;

    if (value < this->value) {
        if (left) return left->acces_or_asign(value);
        else left = new node<T>(this, node<T>::black, value);
        return left;
    }

    if (value > this->value) {
        if (right) return right->acces_or_asign(value);
        else right = new node<T>(this, node<T>::black, value);
        return right;

    }

// this should never happen :
    assert(false);
    return nullptr;
}

template<class T>
inline node<T> *node<T>::end() {

    if (right) return right->end();
    if (left) return left->end();

    return this;

}

template<class T>
inline node<T> *node<T>::next(const T &previous_value) {

    if (previous_value == this->value && left) return left;
    if (previous_value == this->value && right) return right;

    if (previous_value < value) {
        if (right) return right;
        else if (father)return father->next(value);
        else return nullptr;

    }
    if (father)return father->next(value);
    else return nullptr;

}

template<class T>
inline node<T> *node<T>::in_order(unsigned &counter) {

    if (counter == 0) return this;
    counter--;
    node<T> *ptr_to_return = nullptr;

    if (left) ptr_to_return = left->in_order(counter);
    if (ptr_to_return) return ptr_to_return;
    if (right) ptr_to_return = right->in_order(counter);
    if (ptr_to_return) return ptr_to_return;

    return nullptr;

}

template<class T>
inline size_t node<T>::size() {
    size_t partial_sum = 1;
    if (left)partial_sum += left->size();
    if (right)partial_sum += right->size();
    return partial_sum;

}

template<class T>
size_t node<T>::size_depth( size_t partial_depth = 0) {
    if(left) {

        if(left->size_depth(partial_depth + 1) > partial_depth) return left->size_depth(partial_depth + 1);
        else return partial_depth;
    }
    if(right){
        if(right->size_depth(partial_depth+1) > partial_depth) return right->size_depth(partial_depth +1 );
        else return  partial_depth;
    }
    return partial_depth;

}

template<class T>
inline void node<T>::append(const T &value) {


    if (value < this->value && left) left->append(value);
    if (value < this->value && !left) left = new node<T>(this, node<T>::black, value);

    if (value > this->value && right) right->append(value);
    if (value > this->value && !right) right = new node<T>(this, node<T>::black, value);


}

template<class T>
inline void node<T>::append_or_replace(const T &value) {

    if (value < this->value) {
        if (left) left->append_or_replace(value);
        else left = new node<T>(this, node<T>::black, value);

    } else if (value > this->value) {
        if (right) right->append_or_replace(value);
        else right = new node<T>(this, node<T>::black, value);
    } else this->value = value;

}

template<class T>
inline T &node<T>::get_value() {
    return value;
}

template<class T>
inline node<T>::~node() {
    if (!left)delete left;
    if (!right)delete right;
// if (!father)delete father // almost made dodo
}




#endif // !NODE_H