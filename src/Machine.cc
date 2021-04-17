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
  * @file Machine.cc
  *
  */

#include "../include/Machine.h"
#include <iostream>

Machine::Machine(std::vector<Task*> tasks) {
  machineTasks_ = tasks;
}

void Machine::addTask(Task* task) {
  machineTasks_.push_back(task);
}

void Machine::insertTask(Task* task, int pos) {
  machineTasks_.resize(machineTasks_.size() + 1);
  for (int i = machineTasks_.size() - 1; i > pos; i--) {
    machineTasks_[i] = machineTasks_[i - 1];
  }
  machineTasks_[pos] = task;
}

int Machine::assignedTasks() {
  return machineTasks_.size();
}

std::vector<Task*> Machine::getTaskArray() {
  return machineTasks_;
}

void Machine::reinsertTask(Task* task, int pos) {
  bool found = false;
  for (int i = 0; i < machineTasks_.size(); i++) {
    if (task == machineTasks_[i]) {
      machineTasks_.erase(machineTasks_.begin() + i);
      found = true;
      break;
    }
  }
  if (found) insertTask(task, pos);
}

void Machine::intermachineTaskReinsertion(Task* task, Machine* machine, int pos) {
  bool found = false;
  for (int i = 0; i < machineTasks_.size(); i++) {
    if (task == machineTasks_[i]) {
      machineTasks_.erase(machineTasks_.begin() + i);
      found = true;
      break;
    }
  }
  if (found) machine->insertTask(task, pos);
}

void Machine::swapTask(Task* taskA, Task* taskB) {
  int i, j;
  bool foundA = false;
  bool foundB = false;
  for (i = 0; i < machineTasks_.size(); i++) {
    if (taskA == machineTasks_[i]) {
      foundA = true;
      break;
    }
  }
  for (j = 0; j < machineTasks_.size(); j++) {
    if (taskB == machineTasks_[j]) {
      foundB = true;
      break;
    }
  }
  if (foundA && foundB) {
    std::swap(machineTasks_[i], machineTasks_[j]);
  }
}

void Machine::intermachineTaskSwap(Task* taskA, Machine* machineB, Task* taskB) {
  int i, j;
  bool foundA = false;
  bool foundB = false;
  for (i = 0; i < machineTasks_.size(); i++) {
    if (taskA == machineTasks_[i]) {
      foundA = true;
      break;
    }
  }
  for (j = 0; j < machineB->machineTasks_.size(); j++) {
    if (taskB == machineB->machineTasks_[j]) {
      foundB = true;
      break;
    }
  }
  if (foundA && foundB) {
    std::swap(machineTasks_[i], machineB->machineTasks_[j]);
  }
}