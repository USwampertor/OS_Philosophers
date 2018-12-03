/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/
/**
 * @file Philosopher.h
 * @author Marco "Swampy" Millan
 * @date 2018/10/07 2018
 * @brief the Philosopher class that will use the forks and later fuck the multi thread
 * 
 */
/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/

#pragma once

#include "osUtilities.h"
#include "Fork.h"

/** Philosopher
  * Description:
  *   The philosopher to use the forks
  * Sample usage:
  *   Philosophers serves to use and leave the forks (resources)
  */
class Philosopher
{
 public:
	
  Philosopher() = default;

  /**
   * Name filling constructor
   */
  Philosopher(std::string name, Fork& rightF, Fork& leftF, int threshold, int eating, int quantum) 
    : m_name(name),
      m_leftFork(leftF),
      m_rightFork(rightF),
      m_starvationTime(threshold),
      m_eatingTime(eating),
      m_quantum (quantum) {}

  /**
   * Default destructor
   */
	~Philosopher() {};

  /**
   * @brief sets the philosopher to wait a little bit, keeping it from taking the forks
   * @param --
   * @return --
   * 
   */
  void 
  think();

  /**
   * @brief attempts to grab the forks, tries to grab the left AND the right, or the right AND
   * the left
   * @param --
   * @return nothing, but getting both forks enters him in the eating state
   * 
   */
  void 
  grab();

  /**
   * @brief attempts to grab first the left fork and later the right
   * @param 
   * @return true if he could get both forks
   * 
   */
  bool 
  grabRight();

  /**
   * @brief attempts to take first the right fork and later the left
   * @param 
   * @return true if able to get both forks
   * 
   */
  bool 
  grabLeft();

  /**
   * @brief adds up the counter of eating
   * @param 
   * @return 
   * 
   */
  void 
  eat();

  /**
   * @brief Initializes the dining thread
   * @param --
   * @return --
   * 
   */
  void 
  start();

  /**
   * Member declaration
   */
 public:
  
  /**
   * times philosopher has eaten
   */
   int m_timesAte;

  /**
   * Philosophers name
   */
  std::string m_name;

  /**
   * Left fork of the philosopher
   */
  Fork& m_leftFork;

  /**
   * Right Fork of the philosopher
   */
  Fork& m_rightFork;

  /**
   * Left Philosopher
   */
  Philosopher* m_left;

  /**
   * Right Philosopher
   */
  Philosopher* m_right;

  /**
   * starvation threshold for the philosophers, they should be the same but can 
   * be different
   * starvation threshold serves as the limit point for the philosopher to think
   * if the philosopher while thinking reaches the threshold, it'll attempt to 
   * take the forks
   */
  int m_starvationTime;

  /**
   * eating time using the forks, for all philosophers should be the same, but 
   * can be different
   */
  int m_eatingTime;

  /**
   * thinking time serves as a time of peace for the philosopher before attempting 
   * to eat again
   */
  int m_thinkingTime;

  /**
   * checks if the program is still running
   */
  bool m_isRunning = true;

  /**
   * the quantum they have to work until they stop with the forks
   */
  int m_quantum;
};
