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
#include "../include/GreedyAlgorithm.h"
#include "../include/NewGreedyAlgorithm.h"
#include "../include/GRASP.h"
#include "../include/GVNS.h"

#include <chrono>

int main(int argc, char* argv[]) {
  srand(time(NULL));
  std::string fileName(argv[1]);
  std::string k = argv[2];
  PMSProblem pmsp(fileName, stoi(k));
  std::vector<Machine*> solution;
  std::vector<std::string> methods({"Greedy Inter-reinsertion", "Greedy Intra-reinsertion", "Greedy Inter-swap", "Greedy Intra-swap", "Anxious Inter-reinsertion", "Anxious Intra-reinsertion", "Anxious Inter-swap", "Anxious Intra-swap"});

  Strategy* algorithm = new GreedyAlgorithm;
  auto start = std::chrono::high_resolution_clock::now();
  solution = algorithm->solve(pmsp);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = stop - start;
  //algorithm->printSolution(solution);
  
  //std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  pmsp.setAllTasksAsUnassigned();

  algorithm = new GVNS;
  std::cout << "- GVNS:\n"; 
  start = std::chrono::high_resolution_clock::now();
  solution = ((GVNS*)algorithm)->solveNonFixedIterations(pmsp);
  stop = std::chrono::high_resolution_clock::now();
  elapsed = stop - start;
  std::cout << "\n- Mejorado:\n";
  algorithm->printSolution(solution);

  std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  pmsp.setAllTasksAsUnassigned();

  /*algorithm = new NewGreedyAlgorithm;
  start = std::chrono::high_resolution_clock::now();
  solution = algorithm->solve(pmsp);
  stop = std::chrono::high_resolution_clock::now();
  elapsed = stop - start;
  algorithm->printSolution(solution);

  std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  pmsp.setAllTasksAsUnassigned();

  algorithm = new GRASP;
  std::cout << "\n- GRASP sin postprocesamiento:\n";
  start = std::chrono::high_resolution_clock::now();
  solution = algorithm->solve(pmsp);
  stop = std::chrono::high_resolution_clock::now();
  elapsed = stop - start;
  algorithm->printSolution(solution);
  std::cout << "\tTiempo de ejecución: " << elapsed.count() << " ms\n\n";

  std::cout << "\n- GRASP con postprocesamiento:\n";
  std::cout << "Iteraciones fijas (10):\n";
  for (int i = 0; i < 8; i++) {
    std::cout << "\t- Metodo de postprocesamiento " << methods[i] << '\n';
    ((GRASP*)algorithm)->setPostprocessingOption(i);
    auto start = std::chrono::high_resolution_clock::now();
    solution = ((GRASP*)algorithm)->solveFixedIterations(pmsp);
    auto stop = std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    algorithm->printSolution(solution);
    std::cout << "\tTiempo de ejecución: " << elapsed.count() << " ms\n\n";
  }
  std::cout << "\nNumero de iteraciones sin cambio (10):\n";
  for (int i = 0; i < 8; i++) {
    std::cout << "\t- Metodo de postprocesamiento " << methods[i] << '\n';
    ((GRASP*)algorithm)->setPostprocessingOption(i);
    auto start = std::chrono::high_resolution_clock::now();
    solution = ((GRASP*)algorithm)->solveFixedIterations(pmsp);
    auto stop = std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    algorithm->printSolution(solution);
    std::cout << "\tTiempo de ejecución: " << elapsed.count() << " ms\n\n";
  }*/

  return 1;
}