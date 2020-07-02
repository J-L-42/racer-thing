/*
 * ArrayList.hpp
 *
 *  Created on: 17 Apr 2017
 *      Author: james
 */

#ifndef MAIN_UTIL_ARRAYLIST_HPP_
#define MAIN_UTIL_ARRAYLIST_HPP_


#define DEFAULT_SIZE 8

#include <vector>

/* Wrapper for std::vector */
template <typename T>
class ArrayList : public std::vector<T> {
private:
    std::vector<T> list;
    typename std::vector<T>::iterator iterator;
public:
    ArrayList();
    ArrayList(int size);

    void add(T element);
    void remove(unsigned int position);
    void remove(T element);
    void clear();

    bool isEmpty();
    bool contains(T element);
    int size();
    inline T get(unsigned int position) const { return list[position]; }

    inline T operator[](unsigned int position) const { return list[position]; }

    ~ArrayList();
};

// Include the implementation for ArrayList
#include "ArrayListImp.hpp"


#endif /* MAIN_UTIL_ARRAYLIST_HPP_ */
