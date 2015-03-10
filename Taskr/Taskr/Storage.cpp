#include "Storage.h"

#include <fstream>

using namespace std;

Storage::Storage() {
}

void Storage::readFile() {
  ifstream myFile(_filename, ifstream::out);
 
}
void Storage::saveFile() {
 ofstream outFile(_filename, ofstream::out);
 for (int i = 0; i < _listOfTasks.size(); i++) {
   // outFile << _listOfTasks[i] << endl;
 }
 outFile.close();
}

int Storage::addTask(Task task) {
 int index;
 _listOfTasks.push_back(task);
 return 1;
 
 
 
}
bool Storage::deleteTask(int taskIndex) {
  int i = taskIndex;
  if (i <=_listOfTasks.size() && i > 0) {
    _listOfTasks.erase (_listOfTasks.begin() + i - 1);
    saveFile();
    return true;
  } else {
    return false;
  }
}
void Storage::displayTask() {
 if(!_listOfTasks.empty()) {
   for (int i = 0; i < _listOfTasks.size(); i++) {
     // cout << i + 1 << ". " << _listOfTasks[i] << endl;
   }
 } else {
   cout << "Nothing to display." << endl;
 }
 
}
void Storage::editTask(int taskIndex, Task) {
 
}
