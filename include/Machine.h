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
  * @file Machine.h
  *
  */

#include <vector>
#include "Task.h"

#ifndef _MACHINE_
#define _MACHINE_

/**
 * @class Machine
 * 
 */
class Machine {
  private:
    std::vector<Task*> machineTasks_;

  public:
    Machine()=default;
    Machine(std::vector<Task*>);
    ~Machine()=default;
    void addTask(Task*);
    void insertTask(Task* task, int pos);
    int assignedTasks();
    std::vector<Task*> getTaskArray();
};

#endif