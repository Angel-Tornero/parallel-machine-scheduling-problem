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
  * @file Task.cc
  *
  */

#include "../include/Task.h"

Task::Task(int id, int processTime) {
  id_ = id;
  processTime_ = processTime;
  assigned_ = false;
}

Task::Task(int id, int processTime, int setupTimeZero) {
  id_ = id;
  processTime_ = processTime;
  assigned_ = false;
  setupTimeZero_ = setupTimeZero;
}

void Task::setSetupTimes(std::vector<int> setupTime) {
  setupTime_ = setupTime;
}

int Task::getProcessTime() {
  return processTime_;
}

void Task::setSetupTimeZero(int time) {
  setupTimeZero_ = time;
}

int Task::getSetupTimeTo(int task) {
  return setupTime_[task];
}

int Task::getSetupTimeZero() {
  return setupTimeZero_;
}

bool Task::assigned() {
  return assigned_;
}

void Task::setAsAssigned() {
  assigned_ = true;
}

void Task::setAsUnassigned() {
  assigned_ = false;
}

int Task::getId() {
  return id_;
}