#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "Task.h"
#define SUCCESS 1
#define ERROR_REPEATED_TASK 21
#define ERROR_INDEX_OUT_OF_RANGE 22
#define ERROR_EMPTY_LIST 23
#define ERROR_INVALID_DESCRIPTION 24


class Storage {
private:
  std::vector<Task> _listOfTasks;
  std::string _filename;
  
  
public:
  Storage();
  ~Storage();
  void readFile();
  void saveFile(std::vector<Task>);
  std::vector<Task> getAllTasks();
  void addTask(int, Task);

};

#endif
