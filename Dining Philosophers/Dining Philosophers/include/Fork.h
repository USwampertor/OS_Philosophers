/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/
/**
 * @file Fork.h
 * @author Marco "Swampy" Millan
 * @date 2018/10/07 2018
 * @brief the fork class that'll be used to prove the multi threading paradigms
 * 
 */
/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/

#pragma once

#include "osUtilities.h"

 /**
  * ENUM for states
  */
enum class STATE
{
  UNTAKEN = 0, 
  TAKEN
};

/** Fork
 * Description:
 *   The fork to use in the table by the philosophers
 * Sample usage:
 *   fork is being used as part of a multi threading example
 */
class Fork
{
 public:

  /**
   * Default constructor for Fork
   */
  Fork() = default;

  /**
   * Copy constructor for Fork
   */
  Fork(const Fork& other) 
    : m_state (other.m_state),
      m_ID (other.m_ID) {}

  /**
   * Default Destructor
   */
  ~Fork() {};


  /**
   * Member declaration
   */
 public:
  
  /**
   * Mute object for the multi threading shit
   */
  std::mutex m_mutex;

  /**
   * state in which the fork is right now
   */
  STATE m_state = STATE::UNTAKEN;

  /**
   * ID of the fork
   */
  int m_ID;

};

