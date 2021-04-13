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
