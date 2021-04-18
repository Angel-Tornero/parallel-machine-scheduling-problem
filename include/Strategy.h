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
 * with Dependent Setup Times
 * 
 */
class Strategy {
  public:
    Strategy()=default;
    ~Strategy()=default;
    virtual std::vector<Machine*> solve(PMSProblem& pmsp)=0;
    virtual void printSolution(std::vector<Machine*>&)=0;
};

#endif