/*
 * ArrayListImp.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_UTIL_ARRAYLISTIMP_HPP_
#define MAIN_UTIL_ARRAYLISTIMP_HPP_


#include "ArrayList.hpp"

template <typename T>
ArrayList<T>::ArrayList() {
    list.reserve(DEFAULT_SIZE);
}

template <typename T>
ArrayList<T>::ArrayList(int size) {
    list.reserve(size);
}

template <typename T>
void ArrayList<T>::add(T element) {
    list.push_back(element);
}

template <typename T>
void ArrayList<T>::remove(unsigned int position) {
    if (position < list.size()) {
        iterator = list.begin() + position;
        list.erase(iterator);
    }
}

template <typename T>
void ArrayList<T>::remove(T element) {
    // Cycle through to get the iterator to the right place, then remove
    unsigned int i = 0;
    iterator = list.begin();
    while (i < list.size() && list[i] != element) {
        iterator++;
        i++;
    }
    if (list[i] == element)
        list.erase(iterator);
}

template <typename T>
void ArrayList<T>::clear() {
    list.clear();
}

template <typename T>
bool ArrayList<T>::isEmpty() {
    return size() == 0;
}

template <typename T>
bool ArrayList<T>::contains(T element) {
    unsigned int i = 0;
    iterator = list.begin();
    while (i < list.size()) {
        if (list[i] == element)
            return true;

        iterator++;
        i++;
    }
    return false;
}

template <typename T>
int ArrayList<T>::size() {
    return (int) list.size();
}

template <typename T>
ArrayList<T>::~ArrayList() {
    clear();
}


#endif /* MAIN_UTIL_ARRAYLISTIMP_HPP_ */
