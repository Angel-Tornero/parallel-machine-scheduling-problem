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
  * @file GreedyAlgorithm.h
  *
  */

#include "Strategy.h"
#include "Machine.h"

/**
 * @class Greedy Constructive Algorithm for Parallel Machine Scheduling Problem
 * with Dependent Setup Times
 * 
 */
class GreedyAlgorithm: public Strategy {

  public:
    GreedyAlgorithm()=default;
    ~GreedyAlgorithm()=default;
    std::vector<Machine*> solve(PMSProblem& pmsp);
    std::vector<Task*> selectShorterTasks(PMSProblem& pmsp);
    void assignNextTask(Machine* machine, Task* task);
    bool allTasksAssigned(PMSProblem& pmsp);
    void bestInsertion(PMSProblem& pmsp, std::vector<Machine*>& solution);
    int calculateBestTCT(Machine* machine, Task* task, int& position);
    int TCT(std::vector<Task*>);
    int C(std::vector<Task*>, int pos);
    void printSolution(std::vector<Machine*>& solution); 
    
};