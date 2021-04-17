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

#ifndef _STRATEGY_
#define _STRATEGY_

/**
 * @class Strategy base class for Parallel Machine Scheduling Problem
 * with Dependent Setup Times
 * 
 */
class Strategy {
  private:
    int z_;
  public:
    Strategy()=default;
    ~Strategy()=default;
    virtual void solve(PMSProblem& pmsp)=0;
};

#endif