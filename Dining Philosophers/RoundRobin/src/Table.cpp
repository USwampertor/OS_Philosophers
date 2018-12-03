/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/
/**
 * @file Table.cpp
 * @author Marco "Swampy" Millan
 * @date 2018/10/07 2018
 * @brief the table member definition
 * 
 */
/*||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||°°°||*/

#include "Table.h"

Table::Table() {

  m_quantum = 3;

  std::string name = "aristotle";
  Philosopher aristotle(name, m_gold, m_silver, 2, std::rand() % 5, m_quantum);
  m_philosophers.push_back(aristotle);

  name = "socrates";
  Philosopher socrates(name, m_silver, m_copper, 2, std::rand() % 5, m_quantum);
  m_philosophers.push_back(socrates);

  name = "plato";
  Philosopher plato(name, m_copper, m_steel, 2, std::rand() % 5, m_quantum);
  m_philosophers.push_back(plato);

  name = "nietzche";
  Philosopher nietzche(name, m_steel, m_wood, 2, std::rand() % 5, m_quantum);
  m_philosophers.push_back(nietzche);

  name = "liebman";
  Philosopher liebman(name, m_wood, m_gold, 2, std::rand() % 5, m_quantum);
  m_philosophers.push_back(liebman);

  m_philosophers[0].m_left  = &m_philosophers[4];
  m_philosophers[1].m_left  = &m_philosophers[0];
  m_philosophers[2].m_left  = &m_philosophers[1];
  m_philosophers[3].m_left  = &m_philosophers[2];
  m_philosophers[4].m_left  = &m_philosophers[3];

  m_philosophers[0].m_right = &m_philosophers[1];
  m_philosophers[1].m_right = &m_philosophers[2];
  m_philosophers[2].m_right = &m_philosophers[3];
  m_philosophers[3].m_right = &m_philosophers[4];
  m_philosophers[4].m_right = &m_philosophers[0];
}

void 
Table::dinner() {
  bool dining = true;
  
  std::thread a(&Philosopher::start, &m_philosophers[0]);
  std::thread b(&Philosopher::start, &m_philosophers[1]);
  std::thread c(&Philosopher::start, &m_philosophers[2]);
  std::thread d(&Philosopher::start, &m_philosophers[3]);
  std::thread e(&Philosopher::start, &m_philosophers[4]);
  a.join();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  b.join();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  c.join();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  d.join();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  e.join();

  //for (unsigned int i = 0; i < m_philosophers.size(); ++i) {
  //  m_philosophers[i].m_isRunning = false;
  //}

}
