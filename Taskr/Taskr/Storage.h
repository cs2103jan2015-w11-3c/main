#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "Task.h"
#include "FloatingTask.h"
#include "TimedTask.h"
#include "DeadlineTask.h"


class Storage {
private:
  std::vector<Task> _listOfTasks;
  std::string _filename;
  
  
public:
  Storage();
  ~Storage(); 
  void setFilePath(std::string filepath);
  void readFile();
  void saveFile(std::vector<Task*>);
  std::vector<Task*> getAllTasks();

};

#endif
