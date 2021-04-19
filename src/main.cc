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

#include <chrono>

int main(int argc, char* argv[]) {
  srand(time(NULL));
  /*std::string fileName(argv[1]);
  std::string k = argv[2];
  std::string iterationLimit = argv[3];*/
  std::vector<std::string> files({"problems/I40j_2m_S1_1.txt", "problems/I40j_4m_S1_1.txt", "problems/I40j_6m_S1_1.txt", "problems/I40j_8m_S1_1.txt"});
  std::vector<std::string> problema({"I40j_2m_S1_1", "I40j_4m_S1_1", "I40j_6m_S1_1", "I40j_8m_S1_1"});
  std::vector<Machine*> solution;
  Strategy* algorithm = new GreedyAlgorithm;
  std::cout << "| Problema | n | | |LRC| | Ejecución | Z | CPU |\n";
  std::cout << "|:-:|:-:|:-:|:-:|:-:|:-:|\n";
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << "|" << problema[i] << "|40|" << (i + 1) * 2 << "|" << j + 1 << "|";
      PMSProblem pmsp(files[i], 1);
      auto start = std::chrono::high_resolution_clock::now();
      solution = algorithm->solve(pmsp);
      auto stop = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = stop - start;
      algorithm->printSolution(solution);
      
      std::cout << "|" << elapsed.count() << " ms|\n";
    }
  }
        delete algorithm;

  return 1;
}

/*int main(int argc, char* argv[]) {
  srand(time(NULL));
  std::string fileName(argv[1]);
  std::string k = argv[2];
  std::string iterationLimit = argv[3];
  PMSProblem pmsp(fileName, stoi(k));
  std::vector<Machine*> solution;

  Strategy* algorithm = new GRASP(stoi(iterationLimit));
  auto start = std::chrono::high_resolution_clock::now();
  solution = algorithm->solve(pmsp);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = stop - start;
  algorithm->printSolution(solution);
  
  std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  pmsp.setAllTasksAsUnassigned();

  algorithm = new NewGreedyAlgorithm;
  start = std::chrono::high_resolution_clock::now();
  solution = algorithm->solve(pmsp);
  stop = std::chrono::high_resolution_clock::now();
  elapsed = stop - start;
  algorithm->printSolution(solution);

  std::cout << "\tTiempo de ejecución del algoritmo: " << elapsed.count() << " ms\n";
  delete algorithm;
  pmsp.setAllTasksAsUnassigned();

  algorithm = new GRASP(stoi(iterationLimit));
  std::cout << "\n GRASP sin postprocesamiento:\n";
  auto start = std::chrono::high_resolution_clock::now();
  solution = ((GRASP*)algorithm)->generateSolution(pmsp);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = stop - start;
  algorithm->printSolution(solution);
  std::cout << "\tTiempo de ejecución: " << elapsed.count() << " ms\n\n";
  std::cout << "\nMultiarranque:\n";
  for (int j = 0; j < 2; j++) {
    std::cout << "CONDICION DE PARADA " << j + 1 << ":\n";
    ((GRASP*)algorithm)->setStopCondition(j);
    for (int i = 0; i < 8; i++) {
      std::cout << "- Metodo de postprocesamiento " << i + 1 << '\n';
      ((GRASP*)algorithm)->setPostprocessingOption(i);
      auto start = std::chrono::high_resolution_clock::now();
      solution = algorithm->solve(pmsp);
      auto stop = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = stop - start;
      algorithm->printSolution(solution);
      std::cout << "\tTiempo de ejecución: " << elapsed.count() << " ms\n\n";
    }
  }
  delete algorithm;

  return 1;
}*/