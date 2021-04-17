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
    /**
     * @brief Change the position of a task in a machine.
     * 
     * @param task 
     * @param pos 
     */
    void reinsertTask(Task* task, int pos);
    /**
     * @brief Change the machine and the position of a task.
     * 
     * @param task 
     * @param machine 
     * @param pos 
     */
    void intermachineTaskReinsertion(Task* task, Machine* machine, int pos);
    /**
     * @brief Swap tasks into the same machine.
     * 
     * @param taskA 
     * @param taskB 
     */
    void swapTask(Task* taskA, Task* taskB);
    /**
     * @brief Swap tasks from different machines.
     * 
     * @param taskA 
     * @param machineB 
     * @param taskB 
     */
    void intermachineTaskSwap(Task* taskA, Machine* machineB, Task* taskB);
};

#endif