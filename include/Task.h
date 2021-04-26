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
  * @file Task.h
  *
  */

#include <vector>

#ifndef _TASK_
#define _TASK_

/**
 * @class Task.
 * 
 */
class Task {
  private:
    int id_;
    int processTime_;
    int setupTimeZero_;         //setup time when there is no task in process
    std::vector<int> setupTime_;
    bool assigned_;

  public:
    /**
     * @brief Construct a new Task object.
     * 
     * @param id 
     * @param processTime 
     */
    Task(int id, int processTime);

    /**
     * @brief Construct a new Task object.
     * 
     * @param id 
     * @param processTime 
     * @param setupTimeZero 
     */
    Task(int id, int processTime, int setupTimeZero);

    /**
     * @brief Destroy the task object.
     * 
     */
    ~Task()=default;

    /**
     * @brief Set the setup times of the task to any other task.
     * 
     * @param setupTime 
     */
    void setSetupTimes(std::vector<int> setupTime);

    /**
     * @brief Get the process time.
     * 
     * @return int 
     */
    int getProcessTime();

    /**
     * @brief Get the setup time from this task to other task.
     * 
     * @param task 
     * @return int 
     */
    int getSetupTimeTo(int task);

    /**
     * @brief Set the setup time from no task to this task.
     * 
     * @param time 
     */
    void setSetupTimeZero(int time);

    /**
     * @brief Get the setup time zero object
     * 
     * @return int 
     */
    int getSetupTimeZero();

    /**
     * @brief Boolean to know if the task is already assigned to a machine.
     * 
     * @return true 
     * @return false 
     */
    bool assigned();

    /**
     * @brief Set the task as assigned.
     * 
     */
    void setAsAssigned();

    /**
     * @brief Set the task as unassigned.
     * 
     */
    void setAsUnassigned();

    /**
     * @brief Get the id of the task.
     * 
     * @return int 
     */
    int getId();
};

#endif