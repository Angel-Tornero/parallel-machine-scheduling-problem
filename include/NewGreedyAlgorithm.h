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
  * @file NewGreedyAlgorithm.h
  *
  */

#include "Strategy.h"
#include "Machine.h"

/**
 * @class New Greedy Algorithm for Parallel Machine Scheduling Problem
 * with Dependent Setup Times
 * 
 */
class NewGreedyAlgorithm: public Strategy {

  public:
    NewGreedyAlgorithm()=default;
    ~NewGreedyAlgorithm()=default;
    std::vector<Machine*> solve(PMSProblem& pmsp);
    std::vector<Task*> selectShorterTasks(PMSProblem& pmsp);
    void assignNextTask(Machine* machine, Task* task);
    bool allTasksAssigned(PMSProblem& pmsp);
    void bestInsertion(PMSProblem& pmsp, std::vector<Machine*>& solution);
    int calculateBestInsertion(std::vector<Machine*> machines, Task* task, int& machine);
    int TCT(std::vector<Task*>);
    int C(std::vector<Task*>, int pos);
    void printSolution(std::vector<Machine*>& solution); 
    
};