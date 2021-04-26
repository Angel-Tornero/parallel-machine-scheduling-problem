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
  * @file PMSProblem.h
  *
  */


#include <vector>
#include <string>
#include <iostream>
#include "Task.h"

#ifndef _PMSP_
#define _PMSP_

/**
 * @class Parallel Machine Scheduling Problem with Dependent Setup Times.
 * 
 */
class PMSProblem {
  private:
    int n_;                                   // número de tareas
    int m_;                                   // número de máquinas
    int k_;                                   // k
    std::vector<Task*> p_;
    std::vector<std::vector<int>> s_;         // matriz con los tiempos de setup de una tarea a la siguiente

  public:

  /**
   * @brief Construct a new PMSProblem object from a file.
   * 
   * @param fileName 
   * @param k 
   */
    PMSProblem(std::string fileName, int k);

    /**
     * @brief Destroy the PMSProblem object.
     * 
     */
    ~PMSProblem();

    /**
     * @brief Set all the tasks of the problem as unassigned.
     * 
     */
    void setAllTasksAsUnassigned();

    /**
     * @brief Operator << to print the problem data.
     * 
     * @param os 
     * @param pmsp 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, PMSProblem& pmsp);

    /**
     * @brief Get a task by id.
     * 
     * @param id 
     * @return Task* 
     */
    Task* getTask(int id);

    /**
     * @brief Get the setup time from a task to another one.
     * 
     * @param from 
     * @param to 
     * @return int 
     */
    int getSetupTime(int from, int to);

    /**
     * @brief Get number of machines in the problem.
     * 
     * @return int 
     */
    int getm();

    /**
     * @brief Get number of tasks in the problem.
     * 
     * @return int 
     */
    int getn();

    /**
     * @brief Get k value (for GRASP).
     * 
     * @return int 
     */
    int getk();
};

#endif