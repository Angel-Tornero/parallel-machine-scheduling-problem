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
#include <chrono>

const int BIG_NUMBER = 999999;

void GRASP::solve(PMSProblem& pmsp) {
  for (int i = 0; i < 8; i++) {
    std::cout << "\n- Postprocessing method " << i << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Machine*> currentSolution = generateSolution(pmsp);
    std::vector<Machine*> bestSolution = currentSolution;
    int noImprovementIterations = 0;
    int bestZ = calculateZ(bestSolution);
    do {
      currentSolution = localSearch(currentSolution, i);
      int newZ = calculateZ(currentSolution);
      if (newZ < bestZ) {
        bestSolution = currentSolution;
        bestZ = newZ;
        noImprovementIterations = 0;
      } else {
        noImprovementIterations++;
      }
      noImprovementIterations++;
      currentSolution = generateSolution(pmsp);
    } while (noImprovementIterations < 1);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = stop - start;
    printSolution(bestSolution);
    std::cout << "Tiempo de ejecución: " << elapsed.count() << " ms\n";
  }
}

std::vector<Machine*> GRASP::generateSolution(PMSProblem& pmsp) {
  srand(time(NULL));
  std::vector<Task*> shorterTasks = selectShorterTasks(pmsp);
  std::vector<Machine*> solution;
  for (int i = 0; i < shorterTasks.size(); i++) {
    solution.push_back(new Machine({shorterTasks[i]}));
  }
  do {
    bestInsertion(pmsp, solution);
  } while (!allTasksAssigned(pmsp));
  pmsp.setAllTasksAsUnassigned();
  return solution;
}

std::vector<Machine*> GRASP::localSearch(std::vector<Machine*> initialSolution, int option) {
  std::vector<Machine*> currentSolution = initialSolution;
  std::vector<Machine*> bestSolution = currentSolution;
  int bestZ = calculateZ(bestSolution);
  do {
    std::vector<Machine*> bestNeighbour;
    switch (option) {
      case 0:
        bestNeighbour = greedyInterReinsertion(currentSolution);
        break;
      case 1:
        bestNeighbour = greedyIntraReinsertion(currentSolution);
        break;
      case 2:
        bestNeighbour = greedyInterSwap(currentSolution);
        break;
      case 3:
        bestNeighbour = greedyIntraSwap(currentSolution);
        break;
      case 4:
        bestNeighbour = anxiousInterReinsertion(currentSolution);
        break;
      case 5:
        bestNeighbour = anxiousIntraReinsertion(currentSolution);
        break;
      case 6:
        bestNeighbour = anxiousInterSwap(currentSolution);
        break;
      case 7:
        bestNeighbour = anxiousIntraSwap(currentSolution);
        break;
    }
    if (bestNeighbour == currentSolution) {
      break;
    }
    currentSolution = bestNeighbour;
    int newZ = calculateZ(currentSolution);
    if (newZ < bestZ) {
      bestSolution = currentSolution;
      bestZ = newZ;
    }
  } while (true);
  return bestSolution;
}

// greedy

std::vector<Machine*> GRASP::greedyIntraReinsertion(std::vector<Machine*> currentSolution) {
  std::vector<Machine*> bestSolution = currentSolution;
  int bestZ = calculateZ(bestSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution[i]->assignedTasks(); j++) {
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        if (k == j) continue;
        std::vector<Machine*> neighbouringSolution;
        for (int l = 0; l < currentSolution.size(); l++) {
          neighbouringSolution.push_back(new Machine(currentSolution[l]->getTaskArray()));
        }
        neighbouringSolution[i]->reinsertTask(j, k);
        int newZ = calculateZ(neighbouringSolution);
        if (newZ < bestZ) {
          bestZ = newZ;
          bestSolution = neighbouringSolution;
        }
      }
    }
  }
  return bestSolution;
}

std::vector<Machine*> GRASP::greedyInterReinsertion(std::vector<Machine*> currentSolution) {
  std::vector<Machine*> bestSolution = currentSolution;
  int bestZ = calculateZ(bestSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution.size(); j++) {
      if (i == j) continue;
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        for (int l = 0; l < currentSolution[j]->assignedTasks(); l++) {
          std::vector<Machine*> neighbouringSolution;
          for (int m = 0; m < currentSolution.size(); m++) {
            neighbouringSolution.push_back(new Machine(currentSolution[m]->getTaskArray()));
          }
          neighbouringSolution[i]->intermachineTaskReinsertion(k, neighbouringSolution[j], l);
          int newZ = calculateZ(neighbouringSolution);
          if (newZ < bestZ) {
            bestZ = newZ;
            bestSolution = neighbouringSolution;
          }
        }
      }
    }
  }
  return bestSolution;
}

std::vector<Machine*> GRASP::greedyIntraSwap(std::vector<Machine*> currentSolution) {
  std::vector<Machine*> bestSolution = currentSolution;
  int bestZ = calculateZ(bestSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution[i]->assignedTasks(); j++) {
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        if (k == j) continue;
        std::vector<Machine*> neighbouringSolution;
        for (int l = 0; l < currentSolution.size(); l++) {
          neighbouringSolution.push_back(new Machine(currentSolution[l]->getTaskArray()));
        }
        neighbouringSolution[i]->swapTask(j, k);
        int newZ = calculateZ(neighbouringSolution);
        if (newZ < bestZ) {
          bestZ = newZ;
          bestSolution = neighbouringSolution;
        }
      }
    }
  }
  return bestSolution;
}

std::vector<Machine*> GRASP::greedyInterSwap(std::vector<Machine*> currentSolution) {
  std::vector<Machine*> bestSolution = currentSolution;
  int bestZ = calculateZ(bestSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution.size(); j++) {
      if (i == j) continue;
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        for (int l = 0; l < currentSolution[j]->assignedTasks(); l++) {
          std::vector<Machine*> neighbouringSolution;
          for (int m = 0; m < currentSolution.size(); m++) {
            neighbouringSolution.push_back(new Machine(currentSolution[m]->getTaskArray()));
          }
          neighbouringSolution[i]->intermachineTaskSwap(k, neighbouringSolution[j], l);
          int newZ = calculateZ(neighbouringSolution);
          if (newZ < bestZ) {
            bestZ = newZ;
            bestSolution = neighbouringSolution;
          }
        }
      }
    }
  }
  return bestSolution;
}

// anxious

std::vector<Machine*> GRASP::anxiousInterReinsertion(std::vector<Machine*> currentSolution) {
  int bestZ = calculateZ(currentSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution.size(); j++) {
      if (i == j) continue;
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        for (int l = 0; l < currentSolution[j]->assignedTasks(); l++) {
          std::vector<Machine*> neighbouringSolution;
          for (int m = 0; m < currentSolution.size(); m++) {
            neighbouringSolution.push_back(new Machine(currentSolution[m]->getTaskArray()));
          }
          neighbouringSolution[i]->intermachineTaskReinsertion(k, neighbouringSolution[j], l);
          int newZ = calculateZ(neighbouringSolution);
          if (newZ < bestZ) {
            return neighbouringSolution;
          }
        }
      }
    }
  }
  return currentSolution;
}

std::vector<Machine*> GRASP::anxiousIntraReinsertion(std::vector<Machine*> currentSolution) {
  int bestZ = calculateZ(currentSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution[i]->assignedTasks(); j++) {
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        if (k == j) continue;
        std::vector<Machine*> neighbouringSolution;
        for (int l = 0; l < currentSolution.size(); l++) {
          neighbouringSolution.push_back(new Machine(currentSolution[l]->getTaskArray()));
        }
        neighbouringSolution[i]->reinsertTask(j, k);
        if (calculateZ(neighbouringSolution) < bestZ) {
          return neighbouringSolution;
        }
      }
    }
  }
  return currentSolution;
}

std::vector<Machine*> GRASP::anxiousInterSwap(std::vector<Machine*> currentSolution) {
  int bestZ = calculateZ(currentSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution.size(); j++) {
      if (i == j) continue;
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        for (int l = 0; l < currentSolution[j]->assignedTasks(); l++) {
          std::vector<Machine*> neighbouringSolution;
          for (int m = 0; m < currentSolution.size(); m++) {
            neighbouringSolution.push_back(new Machine(currentSolution[m]->getTaskArray()));
          }
          neighbouringSolution[i]->intermachineTaskSwap(k, neighbouringSolution[j], l);
          if (calculateZ(neighbouringSolution) < bestZ) {
            return neighbouringSolution;
          }
        }
      }
    }
  }
  return currentSolution;
}

std::vector<Machine*> GRASP::anxiousIntraSwap(std::vector<Machine*> currentSolution) {
  int bestZ = calculateZ(currentSolution);
  for (int i = 0; i < currentSolution.size(); i++) {
    for (int j = 0; j < currentSolution[i]->assignedTasks(); j++) {
      for (int k = 0; k < currentSolution[i]->assignedTasks(); k++) {
        if (k == j) continue;
        std::vector<Machine*> neighbouringSolution;
        for (int l = 0; l < currentSolution.size(); l++) {
          neighbouringSolution.push_back(new Machine(currentSolution[l]->getTaskArray()));
        }
        neighbouringSolution[i]->swapTask(j, k);
        if (calculateZ(neighbouringSolution) < bestZ) {
          return neighbouringSolution;
        }
      }
    }
  }
  return currentSolution;
}

void GRASP::assignNextTask(Machine* machine, Task* task) {
  machine->addTask(task);
}

std::vector<Task*> GRASP::selectShorterTasks(PMSProblem& pmsp) {
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

int GRASP::calculateZ(std::vector<Machine*>& solution) {
  int z = 0;
  for (int i = 0; i < solution.size(); i++) {
    z += TCT(solution[i]->getTaskArray());
  }
  return z;
}

void GRASP::printSolution(std::vector<Machine*>& solution) {
  int complexTime = 0;
  for (int i = 0; i < solution.size(); i++) {
    std::cout << "\tMáquina " << i + 1 << " (" << TCT(solution[i]->getTaskArray()) << ") : { ";
    complexTime += TCT(solution[i]->getTaskArray());
    for (int j = 0; j < solution[i]->assignedTasks(); j++) {
      std::cout << solution[i]->getTaskArray()[j]->getId() + 1 << ' ';
    }
    std::cout << "}\n";
  }
  std::cout << "\tTiempo total: " << complexTime << '\n';
}