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
  * @file main.cc
  *
  */

#include "../include/PMSProblem.h"
#include "../include/GreedyConstructiveAlgorithm.h"
#include "../include/NewGreedyAlgorithm.h"
#include "../include/GRASP.h"

#include <chrono>

int main(int argc, char* argv[]) {
  std::string fileName(argv[1]);
  std::string k = argv[2];
  PMSProblem pmsp(fileName, stoi(k));

  Strategy* algorithm = new GreedyConstructiveAlgorithm;
  auto start = std::chrono::high_resolution_clock::now();
  algorithm->solve(pmsp);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = stop - start;
  std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  pmsp.setAllTasksAsUnassigned();

  algorithm = new NewGreedyAlgorithm;
  start = std::chrono::high_resolution_clock::now();
  algorithm->solve(pmsp);
  stop = std::chrono::high_resolution_clock::now();
  elapsed = stop - start;
  std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  pmsp.setAllTasksAsUnassigned();

  algorithm = new GRASP;
  start = std::chrono::high_resolution_clock::now();
  algorithm->solve(pmsp);
  stop = std::chrono::high_resolution_clock::now();
  elapsed = stop - start;
  std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  
  return 1;
}
