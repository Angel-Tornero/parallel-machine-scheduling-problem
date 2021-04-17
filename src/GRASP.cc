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
  * @file GRASP.cc
  *
  */

#include "../include/GRASP.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

const int BIG_NUMBER = 999999;

void GRASP::solve(PMSProblem& pmsp) {
  srand(time(NULL));
  std::vector<Machine*> solution;
  for (int i = 0; i < pmsp.getm(); i++) {
    std::vector<Task*> shorterTasks = selectShorterTasks(pmsp);
    int randomNumber = rand() % shorterTasks.size();
    if (shorterTasks[randomNumber]->assigned()) {
      i--;
      continue;
    }
    solution.push_back(new Machine({shorterTasks[randomNumber]}));
    shorterTasks[randomNumber]->setAsAssigned();
  }
  do {
    bestInsertion(pmsp, solution);
  } while (!allTasksAssigned(pmsp));

  //print
  int complexTime = 0;
  std::cout << '\n';
  std::cout << "Algoritmo GRASP: \n";
  for (int i = 0; i < solution.size(); i++) {
    std::cout << "\tMáquina " << i + 1 << " (" << TCT(solution[i]->getTaskArray()) << ") : { ";
    complexTime += TCT(solution[i]->getTaskArray());
    for (int j = 0; j < solution[i]->taskArraySize(); j++) {
      std::cout << solution[i]->getTaskArray()[j]->getId() + 1<< ' ';
    }
    std::cout << "}\n";
  }
  std::cout << "\tTiempo total: " << complexTime << '\n';
  for (int i = 0; i < solution.size(); i++) {
    delete solution[i];
  }
}

void GRASP::assignNextTask(Machine* machine, Task* task) {
  machine->addTask(task);
}

std::vector<Task*> GRASP::selectShorterTasks(PMSProblem& pmsp) {
  Task* auxTask = new Task(-1, BIG_NUMBER, BIG_NUMBER);
  Task* shortestTask;
  std::vector<Task*> shorterTasks;
  for (int i = 0; i < pmsp.getk(); i++) {
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
  for (int i = 0; i < shorterTasks.size(); i++) {
    shorterTasks[i]->setAsUnassigned();
  }
  delete auxTask;
  return shorterTasks;
}

bool GRASP::allTasksAssigned(PMSProblem& pmsp) {
  for (int i = 0; i < pmsp.getn(); i++) {
    if (!pmsp.getTask(i)->assigned()) {
      return false;
    }
  }
  return true;
}

void GRASP::bestInsertion(PMSProblem& pmsp, std::vector<Machine*>& solution) {
  int bestTCT = BIG_NUMBER;
  int bestTask;
  int bestPosition;
  int bestMachine;
  std::vector<int> bestTasksArr;
  std::vector<int> bestPositionsArr;
  std::vector<int> bestMachineArr;

  for (int k = 0; k < pmsp.getk(); k++){
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
    bestTasksArr.push_back(bestTask);
    bestPositionsArr.push_back(bestPosition);
    bestMachineArr.push_back(bestMachine);
    pmsp.getTask(bestTask)->setAsAssigned();
  }
  for (int i = 0; i < bestTasksArr.size(); i++) {
    pmsp.getTask(bestTasksArr[i])->setAsUnassigned();
  }
  int randomNumber = rand() % bestTasksArr.size();
  solution[bestMachineArr[randomNumber]]->insertTask(pmsp.getTask(bestTasksArr[randomNumber]), bestPositionsArr[randomNumber]);
  pmsp.getTask(bestTasksArr[randomNumber])->setAsAssigned();
}

int GRASP::calculateBestTCT(Machine* machine, Task* task, int& position) {
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

int GRASP::TCT(std::vector<Task*> machine) {
  int sum = 0;
  for (int i = 0; i < machine.size(); i++) {
    sum += C(machine, i);
  }
  return sum;
}

int GRASP::C(std::vector<Task*> machine, int pos) {
  int sum = machine[0]->getSetupTimeZero() + machine[0]->getProcessTime();
  for (int i = 0; i < pos; i++) {
    sum += machine[i]->getSetupTimeTo(machine[i + 1]->getId()) + machine[i + 1]->getProcessTime();
  }
  return sum;
}