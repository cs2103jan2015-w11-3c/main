//@author A0114077L
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
  std::string _fileConfig;
  std::string _filename;
  std::string _filepath;
  
  
public:
  Storage();
  ~Storage(); 
  void setFilePath(std::string filepath);
  void saveFile(std::vector<Task*>);
  std::vector<Task*> getAllTasks();
  std::string getFullFileName();
  void setFileConfig();
  void updateFileConfig();
  
};

#endif
