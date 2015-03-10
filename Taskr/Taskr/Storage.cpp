#include "Storage.h"


TaskStorage::TaskStorage() {
  
  void readFile() {
    
  }
  void saveFile() {
    ofstream outFile(fileName);
    for (int i = 0; i < _listofTasks.size(); i++) {
      outFile << _listofTasks[i] << endl;
    }
    outFile.close();
  }
  
  int addTask(Task) {
    int index;
    _listOfTasks.push_back(Task);
    return 1;
    
    // if insufficient disk space
    //
    
    
  }
  void deleteTask(int taskIndex) {
    
  }
  void displayTask() {
    if(!_listOfTasks.empty()) {
      for (int i = 0; i < _listOfTasks.size(); i++) {
        cout << i + 1 << ". " << _listOfTasks[i] << endl;
      }
    } else {
      cout << "Nothing to display." << endl;
    }
    
  }
  void editTask(int taskIndex, Task) {
    
  }
}
