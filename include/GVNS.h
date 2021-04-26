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
  * @file GVNS.cc
  *
  */

#include "Strategy.h"

class GVNS: public Strategy {
  public:
    /**
     * @brief Construct a new GVNS object.
     * 
     */
    GVNS()=default;

    /**
     * @brief Destroy the GVNS object.
     * 
     */
    ~GVNS()=default;

    /**
     * @brief Solves the given problem and returns the solution.
     * 
     * @param pmsp 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> solve(PMSProblem& pmsp);

    /**
     * @brief Solves the problem with post-processing and fixed iterations (stop condition).
     * 
     * @param pmsp 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> solveFixedIterations(PMSProblem& pmsp);

    /**
     * @brief Solves the problem with post-processing and non-fixed iterations (stop condition).
     * 
     * @param pmsp 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> solveNonFixedIterations(PMSProblem& pmsp);

    /**
     * @brief Generates a random solution in the neighbourhood structure of given solution.
     * 
     * @param solution 
     * @param structure 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> generateRandomPoint(std::vector<Machine*> solution, int structure);

    /**
     * @brief Search the optimal local of a solution using VND.
     * 
     * @param solution 
     * @param lStructures 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> localSearchVND(std::vector<Machine*> solution, std::vector<int> lStructures);

    /**
     * @brief Generates a solution with GRASP.
     * 
     * @param pmsp 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> generateSolution(PMSProblem& pmsp);

    /**
     * @brief Select the m shortest tasks to initialize the machines.
     * 
     * @param pmsp 
     * @return std::vector<Task*> 
     */
    std::vector<Task*> selectShorterTasks(PMSProblem& pmsp);

    /**
     * @brief Search the optimal local of a solution.
     * 
     * @param initialSolution 
     * @param option 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> localSearch(std::vector<Machine*> initialSolution, int option);

    /**
     * @brief Post processing with greedy inter-reinsertion of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> greedyInterReinsertion(std::vector<Machine*> currentSolution);

    /**
     * @brief Post processing with greedy intra-reinsertion of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> greedyIntraReinsertion(std::vector<Machine*> currentSolution);

    /**
     * @brief Post processing with greedy inter-swap of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> greedyInterSwap(std::vector<Machine*> currentSolution);

    /**
     * @brief Post processing with greedy intra-swap of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> greedyIntraSwap(std::vector<Machine*> currentSolution);

    /**
     * @brief Post processing with anxious inter-reinsertion of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> anxiousInterReinsertion(std::vector<Machine*> currentSolution);

    /**
     * @brief Post processing with anxious intra-reinsertion of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> anxiousIntraReinsertion(std::vector<Machine*> currentSolution);

    /**
     * @brief Post processing with anxious inter-swap of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> anxiousInterSwap(std::vector<Machine*> currentSolution);

    /**
     * @brief Post processing with anxious intra-swap of tasks.
     * 
     * @param currentSolution 
     * @return std::vector<Machine*> 
     */
    std::vector<Machine*> anxiousIntraSwap(std::vector<Machine*> currentSolution);

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
    int calculateZ(std::vector<Machine*>& solution);

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