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
  * @file GreedyAlgorithm.cc
  *
  */

#include "../include/GreedyAlgorithm.h"
#include <iostream>

const int BIG_NUMBER = 999999;

std::vector<Machine*> GreedyAlgorithm::solve(PMSProblem& pmsp) {
  std::vector<Task*> shorterTasks = selectShorterTasks(pmsp);
  std::vector<Machine*> solution;
  for (int i = 0; i < pmsp.getm(); i++) {
    solution.push_back(new Machine({shorterTasks[i]}));
  }
  do {
    bestInsertion(pmsp, solution);
  } while (!allTasksAssigned(pmsp));

  return solution;
}

void GreedyAlgorithm::assignNextTask(Machine* machine, Task* task) {
  machine->addTask(task);
}

std::vector<Task*> GreedyAlgorithm::selectShorterTasks(PMSProblem& pmsp) {
  Task* auxTask = new Task(-1, BIG_NUMBER, BIG_NUMBER);
  Task* shortestTask;
  std::vector<Task*> shorterTasks;
  for (int i = 0; i < pmsp.getm(); i++) {
    shortestTask = auxTask;
    for (int j = 0; j < pmsp.getn(); j++) {
      if (pmsp.getTask(j)->getProcessTime() + pmsp.getTask(j)->getSetupTimeZero() < shortestTask->getProcessTime() + shortestTask->getSetupTimeZero()
          && !pmsp.getTask(j)->assigned()) {
          shortestTask = pmsp.getTask(j);
      }
    }
    shortestTask->setAsAssigned();
    shorterTasks.push_back(shortestTask);
  }
  delete auxTask;
  return shorterTasks;
}

bool GreedyAlgorithm::allTasksAssigned(PMSProblem& pmsp) {
  for (int i = 0; i < pmsp.getn(); i++) {
    if (!pmsp.getTask(i)->assigned()) {
      return false;
    }
  }
  return true;
}

void GreedyAlgorithm::bestInsertion(PMSProblem& pmsp, std::vector<Machine*>& solution) {
  int bestTCT = BIG_NUMBER;
  int bestTask;
  int bestPosition;
  int bestMachine;
  for (int i = 0; i < solution.size(); i++) {
    for (int j = 0; j < pmsp.getn(); j++) {
      if (pmsp.getTask(j)->assigned()) {
        continue;
      }
      int newPosition;
      int newTCT = calculateBestTCT(solution[i], pmsp.getTask(j), newPosition);
      if (newTCT < bestTCT) {
        bestTCT = newTCT;
        bestTask = j;
        bestPosition = newPosition;
        bestMachine = i;
      }
    }
  }
  solution[bestMachine]->insertTask(pmsp.getTask(bestTask), bestPosition);
  pmsp.getTask(bestTask)->setAsAssigned();
}

int GreedyAlgorithm::calculateBestTCT(Machine* machine, Task* task, int& position) {
  int bestTCT = BIG_NUMBER;
  int actualTCT = TCT(machine->getTaskArray());
  for (int i = 0; i < machine->assignedTasks() + 1; i++) {
    Machine aux(machine->getTaskArray());
    aux.insertTask(task, i);
    int tct = TCT(aux.getTaskArray());
    if (tct - actualTCT < bestTCT) {
      bestTCT = tct - actualTCT;
      position = i;
    }
  }
  return bestTCT;
}

int GreedyAlgorithm::TCT(std::vector<Task*> machine) {
  int sum = 0;
  for (int i = 0; i < machine.size(); i++) {
    sum += C(machine, i);
  }
  return sum;
}

int GreedyAlgorithm::C(std::vector<Task*> machine, int pos) {
  int sum = machine[0]->getSetupTimeZero() + machine[0]->getProcessTime();
  for (int i = 0; i < pos; i++) {
    sum += machine[i]->getSetupTimeTo(machine[i + 1]->getId()) + machine[i + 1]->getProcessTime();
  }
  return sum;
}

void GreedyAlgorithm::printSolution(std::vector<Machine*>& solution) {
  //std::cout << "\nAlgoritmo Greedy:\n";
  int complexTime = 0;
  for (int i = 0; i < solution.size(); i++) {
    //std::cout << "\tMáquina " << i + 1 << " (" << TCT(solution[i]->getTaskArray()) << ") : { ";
    complexTime += TCT(solution[i]->getTaskArray());
    for (int j = 0; j < solution[i]->assignedTasks(); j++) {
      //std::cout << solution[i]->getTaskArray()[j]->getId() + 1 << ' ';
    }
    //std::cout << "}\n";
  }
  //std::cout << "\tTiempo total: " << complexTime << '\n';
  std::cout << complexTime;
}