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
 * @class Parallel Machine Scheduling Problem with Dependent Setup Times
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
    PMSProblem(std::string fileName, int k);
    ~PMSProblem();
    void setAllTasksAsUnassigned();
    friend std::ostream& operator<<(std::ostream& os, PMSProblem& pmsp);
    Task* getTask(int id);
    int getSetupTime(int from, int to);
    int getm();
    int getn();
    int getk();
};

#endif