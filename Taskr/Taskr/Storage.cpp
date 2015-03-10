#include "Storage.h"

#include <fstream>

using namespace std;

TaskStorage::TaskStorage() {
}

void TaskStorage::readFile() {
 
}
void TaskStorage::saveFile() {
 ofstream outFile(_filename, ofstream::out);
 for (int i = 0; i < _listOfTasks.size(); i++) {
   // outFile << _listOfTasks[i] << endl;
 }
 outFile.close();
}

int TaskStorage::addTask(Task task) {
 int index;
 _listOfTasks.push_back(task);
 return 1;
 
 // if insufficient disk space
 //
 
 
}
void TaskStorage::deleteTask(int taskIndex) {
 
}
void TaskStorage::displayTask() {
 if(!_listOfTasks.empty()) {
   for (int i = 0; i < _listOfTasks.size(); i++) {
     // cout << i + 1 << ". " << _listOfTasks[i] << endl;
   }
 } else {
   cout << "Nothing to display." << endl;
 }
 
}
void TaskStorage::editTask(int taskIndex, Task) {
 
}
