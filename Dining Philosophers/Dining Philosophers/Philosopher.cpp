/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/
/**
 * @file Philosopher.cpp
 * @author Marco "Swampy" Millan
 * @date 2018/10/07 2018
 * @brief the Philosopher method implementation
 * 
 */
/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/

#include "pch.h"
#include "Philosopher.h"

void 
Philosopher::think() {
  std::cout << m_name.c_str() << " is thinking" << std::endl;
  int counter = rand() % m_starvationTime;

  while (counter > 0) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    --counter;
    ++m_thinkingTime;

    if (m_thinkingTime > m_starvationTime) {
      std::cout << " I'm starving! \n" << std::endl;
    }
  }
}

void 
Philosopher::grab() {
  if (grabRight()) {
    if (grabLeft()) {
      eat();
    }
    else {
      //attempt to grab again the other one
      std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));
      if (grabLeft()) {
        eat();
      }
    }
    m_rightFork.m_mutex.unlock();
  }
  //think();
  //if (grabLeft()) {
  //  if (grabRight()) {
  //    eat();
  //  }
  //  else {
  //    //attempt to grab again the other one
  //    std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));
  //    if (grabRight()) {
  //      eat();
  //    }
  //  }
  //  m_leftFork.m_mutex.unlock();
  //}

}

bool 
Philosopher::grabRight() {
  std::unique_lock<std::mutex> lock(m_rightFork.m_mutex, std::try_to_lock);
  return lock.owns_lock();

  //return m_rightFork.m_mutex.try_lock();
}

bool 
Philosopher::grabLeft() {

  std::unique_lock<std::mutex> lock(m_leftFork.m_mutex, std::try_to_lock);
  return lock.owns_lock();

  //return m_rightFork.m_mutex.try_lock();
}

void 
Philosopher::eat() {
  m_thinkingTime = 0;
  std::cout << "I'm eating... OMNOMNOM" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(m_eatingTime));
  m_rightFork.m_mutex.unlock();
  m_leftFork.m_mutex.unlock();
  std::cout << "I finished eating..." << std::endl;
}

void 
Philosopher::start() {
  
  do {
    grab();
    think();
  } while (m_isRunning);
}
