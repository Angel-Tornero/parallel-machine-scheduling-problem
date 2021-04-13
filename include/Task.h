/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos
  * 
  * Algoritmos constructivos y búsquedas por entornos
  *
  * @author Ángel Tornero Hernández
  * @date 12 Abr 2021
  * @file Task.h
  *
  */

#include <vector>

#ifndef _TASK_
#define _TASK_

/**
 * @class Task
 * 
 */
class Task {
  private:
    int id_;
    int processTime_;
    int setupTimeZero_;         //setup time when there is no task in process
    std::vector<int> setupTime_;
    bool assigned_;

  public:
    Task(int id, int processTime);
    Task(int id, int processTime, int setupTimeZero);
    ~Task()=default;
    void setSetupTimes(std::vector<int> setupTime);
    int getProcessTime();
    int getSetupTimeTo(int task);
    void setSetupTimeZero(int time);
    int getSetupTimeZero();
    bool assigned();
    void setAsAssigned();
    void setAsUnassigned();
    int getId();
};

#endif