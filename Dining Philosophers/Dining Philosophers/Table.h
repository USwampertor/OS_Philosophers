/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/
/**
 * @file Table.h
 * @author Marco "Swampy" Millan
 * @date 2018/10/07 2018
 * @brief The table class is an object made to have static forks and therefore not having to
 * declare constantly new forks
 * 
 */
/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/

#pragma once

//#include "osUtilities.h"
#include "Fork.h"
#include "Philosopher.h"
/** Table
  * Description:
  *   A fork container
  * Sample usage:
  *   Table has the 5 forks used in the dinners problem
  */
class Table
{
 public:

  /**
   * Custom constructor
   */
  Table();
 
  /**
   * @brief makes everyone eat
   * @param 
   * @return 
   * 
   */
  void 
  dinner();

  /**
   * Default destructor
   */
  ~Table() {};

  /**
   * member declaration
   */
 public:
  
  /**
   * vector with the philosophers
   */
  std::vector<Philosopher> m_philosophers;

  /**
   * Silver fork
   */
  Fork m_silver;

  /**
   * Golden fork
   */
  Fork m_gold;

  /**
   * Copper fork
   */
  Fork m_copper;

  /**
   * Steel fork
   */
  Fork m_steel;

  /**
   * Silver fork
   */
  Fork m_wood;

};

