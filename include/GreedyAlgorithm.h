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
 * with Dependent Setup Times.
 * 
 */
class GreedyAlgorithm: public Strategy {
  public:
    /**
     * @brief Construct a new Greedy Algorithm object.
     * 
     */
    GreedyAlgorithm()=default;

    /**
     * @brief Destroy the Greedy Algorithm object.
     * 
     */
    ~GreedyAlgorithm()=default;

    /**
     * @brief Solves the given problem and returns the solution.
     * 
     * @param pmsp 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> solve(PMSProblem& pmsp);

    /**
     * @brief Select the m shortest tasks to initialize the machines.
     * 
     * @param pmsp 
     * @return std::vector<Task*> 
     */
    std::vector<Task*> selectShorterTasks(PMSProblem& pmsp);

    /**
     * @brief Assigns the new task to a machine.
     * 
     * @param machine 
     * @param task 
     */
    void assignNextTask(Machine* machine, Task* task);

    /**
     * @brief Boolean to know if all tasks of the problem are already assigned.
     * 
     * @param pmsp 
     * @return true 
     * @return false 
     */
    bool allTasksAssigned(PMSProblem& pmsp);

    /**
     * @brief Calculate the best insertion that can be performed in certain moment
     * of the problem solving and do it.
     * 
     * @param pmsp 
     * @param solution 
     */
    void bestInsertion(PMSProblem& pmsp, std::vector<Machine*>& solution);

    /**
     * @brief Given a machine and a task, returns the position where it would be better
     * (minimizing the TCT increase).
     * 
     * @param machine 
     * @param task 
     * @param position 
     * @return int 
     */
    int calculateBestTCT(Machine* machine, Task* task, int& position);

    /**
     * @brief Calculates the TCT of a sequence of tasks.
     * 
     * @return int 
     */
    int TCT(std::vector<Task*>);

    /**
     * @brief Calculates the C of a sequence of tasks on given position.
     * 
     * @param pos 
     * @return int 
     */
    int C(std::vector<Task*>, int pos);

    /**
     * @brief Prints on terminal the solution.
     * 
     */
    void printSolution(std::vector<Machine*>& solution); 
    
};