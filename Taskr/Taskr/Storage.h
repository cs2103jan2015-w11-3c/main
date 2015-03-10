#pragma once

#include <vector>
#include <string>
#include "Task.h"

class Storage {
private:
  std::vector <Task> _listOfTasks;
  std::string _filename;
  
  
public:
  Storage();
  ~Storage();
  void readFile();
  void saveFile();
  
  int addTask(Task);
  bool deleteTask(int taskIndex);
  void displayTask();
  void editTask(int taskIndex, Task);
  
};
