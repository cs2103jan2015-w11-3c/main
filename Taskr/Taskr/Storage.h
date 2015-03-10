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
  
  bool addTask(Task);
  bool deleteTask(int taskIndex);
  bool displayTask();
  bool editTask(int taskIndex, Task);
  
};
