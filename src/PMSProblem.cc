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
  * @file PMSProblem.cc
  *
  */

#include "../include/PMSProblem.h"
#include <fstream>

PMSProblem::PMSProblem(std::string fileName, int k) {

  std::ifstream inFile(fileName);
  if (inFile.fail()) {
    throw "No se pudo abrir el fichero " + fileName + ". Saliendo del programa.\n";
  }
  k_ = k;
  std::string strStore;
  std::getline(inFile, strStore, '\t');
  inFile >> n_;
  std::getline(inFile, strStore, '\t');
  inFile >> m_;
  std::getline(inFile, strStore, '\t');
  int numStore;

  for (int i = 0; i < n_; i++) {
    inFile >> numStore;
    p_.push_back(new Task(i, numStore));
  }
  std::getline(inFile, strStore);
  std::getline(inFile, strStore);
  s_.resize(n_ + 1);
  for (int i = 0; i < s_.size(); i++) {
    std::vector<int> vectorStore;
    for (int j = 0; j < n_ + 1; j++) {
      inFile >> numStore;
      s_[i].push_back(numStore);
      vectorStore.push_back(numStore);
    }
    if (i != 0) {
      vectorStore.erase(vectorStore.begin());
      p_[i - 1]->setSetupTimes(vectorStore);
    }
  }
  for (int i = 0; i < p_.size(); i++) {
    p_[i]->setSetupTimeZero(s_[0][i+1]);
  }
}

PMSProblem::~PMSProblem() {
  for (int i = 0; i < p_.size(); i++) {
    delete p_[i];
  }
}

Task* PMSProblem::getTask(int id) {
  return p_[id];
}

int PMSProblem::getSetupTime(int from, int to) {
  return s_[from][to];
}

int PMSProblem::getm() {
  return m_;
}

int PMSProblem::getn() {
  return n_;
}

int PMSProblem::getk() {
  return k_;
}

std::ostream& operator<<(std::ostream& os, PMSProblem& pmsp) {
  std::cout << "n: " << pmsp.n_ << '\n';
  std::cout << "m: " << pmsp.m_ << '\n';
  std::cout << "pi:\n   ";
  for (int i = 0; i < pmsp.p_.size(); i++) {
    std::cout << (((pmsp.getTask(i)->getProcessTime() / 10) == 0) ? " " : "") << pmsp.getTask(i)->getProcessTime() << ' ';
  }
  std::cout << "\nsij:\n   ";
  for (int i = 0; i < pmsp.getn(); i++) {
    std::cout << (((pmsp.getTask(i)->getSetupTimeZero() / 10) == 0) ? " " : "") << pmsp.getTask(i)->getSetupTimeZero() << ' ';
  }
  std::cout << "\n   ";
  for (int i = 0; i < pmsp.p_.size(); i++) {
    for (int j = 0; j < pmsp.getn(); j++) {
      std::cout << (((pmsp.p_[i]->getSetupTimeTo(j) / 10) == 0) ? " " : "") << pmsp.p_[i]->getSetupTimeTo(j) << ' ';
    }
    std::cout << "\n   ";
  }
}

void PMSProblem::setAllTasksAsUnassigned() {
  for (int i = 0; i < p_.size(); i++) {
    p_[i]->setAsUnassigned();
  }
}