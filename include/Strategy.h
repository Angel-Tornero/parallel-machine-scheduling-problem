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
  * @file Strategy.h
  *
  */

#include "PMSProblem.h"
#include "Machine.h"

#ifndef _STRATEGY_
#define _STRATEGY_

/**
 * @class Strategy base class for Parallel Machine Scheduling Problem
 * with Dependent Setup Times.
 * 
 */
class Strategy {
  public:
    /**
     * @brief Construct a new Strategy object.
     * 
     */
    Strategy()=default;

    /**
     * @brief Destroy the Strategy object.
     * 
     */
    ~Strategy()=default;

    /**
     * @brief Solves the given problem and returns the solution.
     * 
     * @param pmsp 
     * @return std::vector<Machine*> 
     */
    virtual std::vector<Machine*> solve(PMSProblem& pmsp)=0;

    /**
     * @brief Prints on terminal the solution.
     * 
     */
    virtual void printSolution(std::vector<Machine*>&)=0;
};

#endif