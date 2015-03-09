#pragma once

using namespace std;

class TaskStorage {
private:
  vector <Task> _listOfTasks;
  
  
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
