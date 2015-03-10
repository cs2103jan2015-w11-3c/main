#pragma once

#include <vector>
#include <string>
#include "Task.h"

class TaskStorage {
private:
  std::vector <Task> _listOfTasks;
  std::string _filename;
  
  
public:
  TaskStorage();
  ~TaskStorage();
  void readFile();
  void saveFile();
  
  int addTask(Task);
  void deleteTask(int taskIndex);
  void displayTask();
  void editTask(int taskIndex, Task);
  
};
