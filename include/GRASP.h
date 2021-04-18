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
  private:
    int option_;
  public:
    GRASP();
    ~GRASP()=default;
    std::vector<Machine*> solve(PMSProblem& pmsp);
    std::vector<Machine*> generateSolution(PMSProblem& pmsp);
    std::vector<Task*> selectShorterTasks(PMSProblem& pmsp);
    std::vector<Machine*> localSearch(std::vector<Machine*> initialSolution, int option);

    std::vector<Machine*> greedyInterReinsertion(std::vector<Machine*> currentSolution);
    std::vector<Machine*> greedyIntraReinsertion(std::vector<Machine*> currentSolution);
    std::vector<Machine*> greedyInterSwap(std::vector<Machine*> currentSolution);
    std::vector<Machine*> greedyIntraSwap(std::vector<Machine*> currentSolution);
    std::vector<Machine*> anxiousInterReinsertion(std::vector<Machine*> currentSolution);
    std::vector<Machine*> anxiousIntraReinsertion(std::vector<Machine*> currentSolution);
    std::vector<Machine*> anxiousInterSwap(std::vector<Machine*> currentSolution);
    std::vector<Machine*> anxiousIntraSwap(std::vector<Machine*> currentSolution);
 
    void assignNextTask(Machine* machine, Task* task);
    bool allTasksAssigned(PMSProblem& pmsp);
    void bestInsertion(PMSProblem& pmsp, std::vector<Machine*>& solution);
    int calculateBestTCT(Machine* machine, Task* task, int& position);
    int TCT(std::vector<Task*>);
    int calculateZ(std::vector<Machine*>& solution);
    int C(std::vector<Task*>, int pos);
    void printSolution(std::vector<Machine*>& solution);
    
    void setOption(int option);
};