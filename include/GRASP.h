/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos
  * 
  * Algoritmos constructivos y búsquedas por entornos
  *
  * @author Ángel Tornero Hernández
  * @date 13 Abr 2021
  * @file GRASP.h
  *
  */

#include "Strategy.h"
#include "Machine.h"
/**
 * @class Greedy Randomized Adaptative Search Procedures for Parallel Machine Scheduling Problem
 * with Dependent Setup Times
 * 
 */
class GRASP: public Strategy {

  public:
    GRASP()=default;
    ~GRASP()=default;
    void solve(PMSProblem& pmsp);
    std::vector<Task*> selectShorterTasks(PMSProblem& pmsp);
    void assignNextTask(Machine* machine, Task* task);
    bool allTasksAssigned(PMSProblem& pmsp);
    void bestInsertion(PMSProblem& pmsp, std::vector<Machine*>& solution);
    int calculateBestTCT(Machine* machine, Task* task, int& position);
    int TCT(std::vector<Task*>);
    int C(std::vector<Task*>, int pos);
    
};