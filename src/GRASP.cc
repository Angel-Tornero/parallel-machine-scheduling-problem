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

GRASP::GRASP() {
  postprocessingOption_ = 0;
}

std::vector<Machine*> GRASP::solve(PMSProblem& pmsp) {
  return generateSolution(pmsp);
}

std::vector<Machine*> GRASP::solveNonFixedIterations(PMSProblem& pmsp) {
  std::vector<Machine*> currentSolution = generateSolution(pmsp);
  std::vector<Machine*> bestSolution = currentSolution;
  int iterations = 0;
  int bestZ = calculateZ(bestSolution);
  do {
    currentSolution = localSearch(currentSolution, postprocessingOption_);
    int newZ = calculateZ(currentSolution);
    if (newZ < bestZ) {
      bestSolution = currentSolution;
      bestZ = newZ;
      iterations = 0;
    } else {
      iterations++;
    }
    currentSolution = generateSolution(pmsp);
  } while (iterations < 10);
  return bestSolution;
}

std::vector<Machine*> GRASP::solveFixedIterations(PMSProblem& pmsp) {
  std::vector<Machine*> currentSolution = generateSolution(pmsp);
  std::vector<Machine*> bestSolution = currentSolution;
  int iterations = 0;
  int bestZ = calculateZ(bestSolution);
  do {
    currentSolution = localSearch(currentSolution, postprocessingOption_);
    int newZ = calculateZ(currentSolution);
    if (newZ < bestZ) {
      bestSolution = currentSolution;
      bestZ = newZ;
    }
    iterations++;
    currentSolution = generateSolution(pmsp);
  } while (iterations < 10);
  return bestSolution;
}

std::vector<Machine*> GRASP::generateSolution(PMSProblem& pmsp) {
  
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
  int bestZ = calculateZ(currentSolution);
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

    int newZ = calculateZ(bestNeighbour);
    if (newZ < bestZ) {
      currentSolution = bestNeighbour;
      bestZ = newZ;
    } else {
      break;
    }
  } while (true);
  return currentSolution;
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
  int lastBestTCT = 0;
  std::vector<int> bestTasksArr;
  std::vector<int> bestPositionsArr;
  std::vector<int> bestMachineArr;

  for (int k = 0; k < pmsp.getk(); k++) {
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
    if (lastBestTCT != bestTCT) {
      bestTasksArr.push_back(bestTask);
      bestPositionsArr.push_back(bestPosition);
      bestMachineArr.push_back(bestMachine);
      pmsp.getTask(bestTask)->setAsAssigned();
      bestTCT = BIG_NUMBER;
      lastBestTCT = bestTCT;
    }
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

void GRASP::setPostprocessingOption(int option) {
  postprocessingOption_ = option;
}

std::vector<Machine*> GRASP::solveGVNSFixedIterations(PMSProblem& pmsp) {
  srand(time(NULL));
  int iterations = 0;
  std::vector<Machine*> currentSolution = generateSolution(pmsp);
  currentSolution = localSearch(currentSolution, 0);
  std::cout << "-Inicial:\n";
  printSolution(currentSolution);
  std::vector<int> kStructures = {0, 2};
  std::vector<int> lStructures = {3, 1, 2, 0};
  int currentK;
  do {
    currentK = kStructures[0];
    do {
      std::vector<Machine*> shakingSolution = generateRandomPoint(currentSolution, kStructures[currentK]);
      std::vector<Machine*> bestLocal = localSearchVND(shakingSolution, lStructures);
      if (calculateZ(bestLocal) < calculateZ(currentSolution)) {
        currentSolution = bestLocal;
        currentK = 0;
      } else {
        currentK++;
      }
    } while (currentK < kStructures.size());
    iterations++;
  } while (iterations < 20);
  return currentSolution;
}

std::vector<Machine*> GRASP::solveGVNSNonFixedIterations(PMSProblem& pmsp) {
  srand(time(NULL));
  int iterations = 0;
  std::vector<Machine*> currentSolution = generateSolution(pmsp);
  currentSolution = localSearch(currentSolution, 0);
  std::cout << "- Inicial:\n";
  printSolution(currentSolution);
  std::vector<int> kStructures = {0};
  std::vector<int> lStructures = {3, 1, 2, 0};
  int currentK;
  do {
    currentK = kStructures[0];
    do {
      std::vector<Machine*> shakingSolution = generateRandomPoint(currentSolution, kStructures[currentK]);
      std::vector<Machine*> bestLocal = localSearchVND(shakingSolution, lStructures);
      if (calculateZ(bestLocal) < calculateZ(currentSolution)) {
        currentSolution = bestLocal;
        currentK = 0;
        iterations = -1;
      } else {
        currentK++;
      }
    } while (currentK < kStructures.size());
    iterations++;
  } while (iterations < 100);
  return currentSolution;
}

std::vector<Machine*> GRASP::generateRandomPoint(std::vector<Machine*> solution, int structure) {
  std::vector<Machine*> neighbouringSolution;
  int randomA;
  int randomB;
  for (int l = 0; l < solution.size(); l++) {
    neighbouringSolution.push_back(new Machine(solution[l]->getTaskArray()));
  }
  switch (structure) {
    case 0:
      randomA = rand() % neighbouringSolution.size();
      randomB = rand() % neighbouringSolution.size();
      if (randomB == randomA) {
        if (randomB == neighbouringSolution.size() - 1) {
          randomB = neighbouringSolution.size() - 2;
        }
        else {
          randomB++;
        }
      }
      neighbouringSolution[randomA]->intermachineTaskReinsertion(rand() % neighbouringSolution[randomA]->assignedTasks(), neighbouringSolution[randomB], rand() % (neighbouringSolution[randomB]->assignedTasks()));
      break;
    case 2:
      randomA = rand() % neighbouringSolution.size();
      randomB = rand() % neighbouringSolution.size();
      if (randomB == randomA) {
        if (randomB == neighbouringSolution.size() - 1) randomB = neighbouringSolution.size() - 2;
        else {
          randomB++;
        }
      }
      
      neighbouringSolution[randomA]->intermachineTaskSwap(rand() % neighbouringSolution[randomA]->assignedTasks(), neighbouringSolution[randomB], rand() % neighbouringSolution[randomB]->assignedTasks());
      break;
  }
  return neighbouringSolution;
}

std::vector<Machine*> GRASP::localSearchVND(std::vector<Machine*> initialSolution, std::vector<int> lStructures) {
  std::vector<Machine*> currentSolution = initialSolution;
  std::vector<Machine*> bestSolution = currentSolution;
  int bestZ = calculateZ(bestSolution);
  int l = 0;
  do {
    std::vector<Machine*> bestNeighbour;
    switch (lStructures[l]) {
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
    int newZ = calculateZ(bestNeighbour);
    if (newZ < bestZ) {
      currentSolution = bestNeighbour;
      bestSolution = currentSolution;
      bestZ = newZ;
      l = 0;
      continue;
    }
    if (l == lStructures.size() - 1) break;
    l++;
    
  } while (true);
  return bestSolution;
}
