/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/
/**
 * @file Dining Philosophers.cpp
 * @author Marco "Swampy" Millan
 * @date 2018/10/07 2018
 * @brief The entry point of the Dining Philosophers problem
 * 
 */
/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/

#include <iostream>

#include "Table.h"

int
main() {
  Table mainTable;
  mainTable.dinner();

  std::cout << "end program \n";
}
