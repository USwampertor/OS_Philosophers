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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    --counter;
    ++m_thinkingTime;

    if (m_thinkingTime > m_starvationTime) {
      std::cout << " I'm starving! \n" << std::endl;
    }
  }
}

void 
Philosopher::grab() {

  //Philosopher tries to grab the right fork
  if (grabRight()) {
    m_rightFork.m_mutex.lock();
    //YAY he could, now to see i the left fork is available
    if (!grabLeft()) {

      //he couldn't, but he'll try to get it again
      std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
      if (!grabLeft()) {

        //he couldn't get it again, he should leave the other fork available
        std::cout << m_name.c_str() << " left the fork"<<std::endl;
        m_rightFork.m_mutex.unlock();
        return;
      }

    }
    m_leftFork.m_mutex.lock();

    eat();
  }



  //if (grabRight()) {
  //  if (grabLeft()) {
  //    eat();
  //    return;
  //  }
  //  else {
  //    //attempt to grab again the other one
  //    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
  //    if (grabLeft()) {
  //      eat();
  //      return;
  //    }
  //  }
  //}

}

bool 
Philosopher::grabRight() {
  std::cout << m_name.c_str() << " is trying to take right" << std::endl;
  std::unique_lock<std::mutex> lock(m_rightFork.m_mutex, std::try_to_lock);
  return lock.owns_lock();

  //return m_rightFork.m_mutex.try_lock();
}

bool 
Philosopher::grabLeft() {
  std::cout << m_name.c_str() << " is trying to take left" << std::endl;
  std::unique_lock<std::mutex> lock(m_leftFork.m_mutex, std::try_to_lock);
  return lock.owns_lock();

  //return m_rightFork.m_mutex.try_lock();
}

void 
Philosopher::eat() {
  m_thinkingTime = 0;
  std::cout << m_name.c_str() << " is eating... OMNOMNOM" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(m_eatingTime));
  std::cout << m_name.c_str() << " finished eating" << std::endl;
  m_rightFork.m_mutex.unlock();
  m_leftFork.m_mutex.unlock();
  std::cout << m_name.c_str() << " left forks" << std::endl;
}

void 
Philosopher::start() {
  
  do {
    grab();
    think();
  } while (m_isRunning);
}
