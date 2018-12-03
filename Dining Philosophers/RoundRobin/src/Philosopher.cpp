/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/
/**
 * @file Philosopher.cpp
 * @author Marco "Swampy" Millan
 * @date 2018/10/07 2018
 * @brief the Philosopher method implementation
 * 
 */
/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/

#include "Philosopher.h"
//#define ROUNDROBIN
#define SHORTESTJ
//#define DEFAULT
void 
Philosopher::think() {

  std::cout << m_name.c_str() << " is thinking \n" << std::endl;
  int counter = m_starvationTime;
  while (counter > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    --counter;
    ++m_thinkingTime;
    if (m_thinkingTime > m_starvationTime) {
      std::cout << m_name << " is starving! \n" << std::endl;
    }
  }
}

void 
Philosopher::grab() {
#ifndef DEFAULT
# ifdef ROUNDROBIN
  //ROUND ROBIN

  //Philosopher tries to grab the right fork
  if (grabRight()) {
    m_rightFork.m_mutex.lock();
    //YAY he could, now to see i the left fork is available
    if (!grabLeft()) {

      //he couldn't, but he'll try to get it again
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      if (!grabLeft()) {

        //he couldn't get it again, he should leave the other fork available
        m_rightFork.m_mutex.unlock();
        return;
      }

    }
    m_leftFork.m_mutex.lock();
    eat();
  }
# else 
  //SHORTEST JOB FIRST

  if (m_right->m_eatingTime >= m_eatingTime) {
    if (grabRight()) {
      m_rightFork.m_mutex.lock();
      //YAY he could, now to see i the left fork is available
      if (!grabLeft()) {

        //he couldn't, but he'll try to get it again
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (!grabLeft()) {

          //he couldn't get it again, he should leave the other fork available
          m_rightFork.m_mutex.unlock();
          return;
        }
      }
      m_leftFork.m_mutex.lock();
      eat();
    }
  }
# endif

#else
  //DEFAULT

  //Philosopher tries to grab the right fork
  if (grabRight()) {
    m_rightFork.m_mutex.lock();
    //YAY he could, now to see i the left fork is available
    if (!grabLeft()) {
      //he couldn't, but he'll try to get it again
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      if (!grabLeft()) {
        m_rightFork.m_mutex.unlock();
        return;
      }
    }
    m_leftFork.m_mutex.lock();
    eat();
  }
#endif

  
}

bool
Philosopher::grabRight() {
  std::unique_lock<std::mutex> lock(m_rightFork.m_mutex, std::try_to_lock);
  return lock.owns_lock();
}

bool 
Philosopher::grabLeft() {
  std::unique_lock<std::mutex> lock(m_leftFork.m_mutex, std::try_to_lock);
  return lock.owns_lock();
}

void 
Philosopher::eat() {

  m_thinkingTime = 0;
#ifndef DEFAULT
# ifdef ROUNDROBIN
  //ROUND ROBIN
  int counter = 0;
  while (counter < m_quantum && counter != m_eatingTime) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ++counter;
}
  if (counter < m_eatingTime) {
    std::cout << "Didn't finish eating, will leave the forks by now" << std::endl;
    m_eatingTime -= m_quantum;
  }

  else if (counter == m_eatingTime) {
    std::cout << m_name << " finished eating" << std::endl;
    ++m_timesAte;
    std::cout << m_name << " has eaten: " << m_timesAte << " times" << std::endl;
    m_eatingTime = std::rand() % 5;
  }
  m_rightFork.m_mutex.unlock();
  m_leftFork.m_mutex.unlock();

# else 
  //SHORTEST JOB FIRST
  std::this_thread::sleep_for(std::chrono::seconds(m_eatingTime));
  ++m_timesAte;
  std::cout << m_name << " has eaten: " << m_timesAte << " times" << std::endl;
  m_eatingTime = std::rand() % 5;
  m_rightFork.m_mutex.unlock();
  m_leftFork.m_mutex.unlock();
# endif

#else
  //DEFAULT

  std::this_thread::sleep_for(std::chrono::seconds(m_eatingTime));
  m_eatingTime = std::rand() % 5;
  m_rightFork.m_mutex.unlock();
  m_leftFork.m_mutex.unlock();
#endif
}

void 
Philosopher::start() {
  m_timesAte = 0;
  do {
    grab();
    think();
  } while (m_isRunning);
}
