#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "Task.h"


class Storage {
private:
  std::vector<Task> _listOfTasks;
  std::string _filename;
  
  
public:
  Storage();
  ~Storage();
  Storage(std::string filename); 
  void setFilePath(std::string filepath);
  void readFile();
  void saveFile(std::vector<Task>);
  std::vector<Task> getAllTasks();

};

#endif
