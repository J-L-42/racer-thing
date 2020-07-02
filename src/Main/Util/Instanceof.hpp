/*
 * Instanceof.hpp
 *
 *  Created on: 18 Apr 2017
 *      Author: james
 */

#ifndef MAIN_UTIL_INSTANCEOF_HPP_
#define MAIN_UTIL_INSTANCEOF_HPP_


#include <typeinfo>

/* Similar to Java's instanceof */
template<typename T, typename K>
inline bool isType(const K* k) {
    return dynamic_cast<const T*>(k) != 0;
}


#endif /* MAIN_UTIL_INSTANCEOF_HPP_ */
