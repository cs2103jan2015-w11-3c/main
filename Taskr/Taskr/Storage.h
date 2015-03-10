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
  
  std::vector<Task> getAllTasks() {
	  return _listOfTasks;
  }

  bool addTask(Task);
  bool deleteTask(int index);
  // bool displayTask();
  bool editTask(int index, Task);

  bool isValidIndex(int index);
  
};
