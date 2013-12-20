/*
 * Debug.hpp
 *
 *  Created on: Dec 17, 2013
 *      Author: habl
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <iostream>
#include <iomanip>

void Dump( const void * mem, unsigned int n ) {
  const char * p = reinterpret_cast< const char *>( mem );
  for ( unsigned int i = 0; i < n; i++ ) {
     std::cout << std::hex << int(p[i]) << " ";
  }
  std::cout << std::endl;
}

#endif /* DEBUG_HPP_ */
