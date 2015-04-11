//@author A0111966A
#include "Logic.h"
INITIALIZE_EASYLOGGINGPP

const std::string Logic::MESSAGE_ADDED = " has been added to Taskr!\n";
const std::string Logic::MESSAGE_DELETED = " has been deleted from Taskr.\n";
const std::string Logic::MESSAGE_MARK_DONE = " has been marked done!\n";
const std::string Logic::MESSAGE_ERROR_TASK_NOT_EXIST = " does not exist.\n";
const std::string Logic::MESSAGE_EDITED = " has been edited to ";
const std::string Logic::MESSAGE_UNDO = "Your last action has been undone.\n";
const std::string Logic::MESSAGE_FILEPATH_CHANGED = "Your filepath has been changed to ";
const std::string Logic::MESSAGE_OPERATION_NOT_EXECUTED = "Your last command was not executed.";
const std::string Logic::MESSAGE_CONFIRM_ACTION = "This action cannot be undone. Are you sure you wish to carry on? (y/n): ";

const std::string Logic::ERROR_EXCEPTION_OCCURRED = "An exception has occurred. Please refer to the Help screen to see valid input.\n";
const std::string Logic::ERROR_REPEATED_TASK = " is a repeated task.\n";
const std::string Logic::ERROR_INDEX_OUT_OF_RANGE = " is an invalid index.\n";
const std::string Logic::ERROR_SEARCH_NOT_FOUND = "No matches were found in Taskr.\n";
const std::string Logic::ERROR_EMPTY_LIST = "The list is currently empty.\n";
const std::string Logic::ERROR_INVALID_DESCRIPTION = "The input description is invalid. Please refer to the Help screen to see valid input.\n";
const std::string Logic::ERROR_USER_COMMAND_INVALID = " is not a valid command. Please enter a valid command.\n";
const std::string Logic::ERROR_NOTHING_TO_UNDO = "There is nothing to undo.\n";

const int Logic::FLOATING_TASK = 1;
const int Logic::TIMED_TASK = 2;
const int Logic::DEADLINE_TASK = 3;

Logic::Logic() {
	_doneTasksCount = 0;
}


Logic::~Logic() {
}

//  The following function takes in the user input, parses the input and decides what command to
//  execute. The function returns an output string for UI to display based on the command entered.
//  UI will decide what kind of message the string contains by reading the leading token.
//  Tokens include: 
//  'C'    == Confirmation Message
//  'D'    == Deadline Task
//  'T'    == Timed Task
//  'F'    == Floating Task
//  'HELP' == Tells UI to display the help screen.
std::string Logic::executeCommand(std::string userInput) {
	try {
		std::string command;
		std::string description;
		std::ostringstream ossConfirmationMessage;
		
		LOG(INFO) << "userInput is " << userInput << std::endl;
		assert(userInput != "");
		_parse = Parser(userInput);
		command = _parse.getCommand();

		if (command != "exit") {

			if (command == "add") {
				executeAdd(ossConfirmationMessage);
			} else if (command == "delete") {
				deleteTask(ossConfirmationMessage);
			} else if (command == "display") {
				displayList(ossConfirmationMessage);
			} else if (command == "edit") {
				editTask(ossConfirmationMessage);
			} else if (command == "done") {
				setDone(ossConfirmationMessage);
			} else if (command == "undo") {
				undoLastAction(ossConfirmationMessage);
			} else if (command == "search") {
				searchList(_parse.getDescription(), ossConfirmationMessage);
			} else if (command == "file") {
				changeFilePath(_parse.getDescription(), ossConfirmationMessage);
			} else if (command == "help") {
				showHelp(ossConfirmationMessage);
			} else {
				ossConfirmationMessage << "C\n" << "\"" << command << "\"" << ERROR_USER_COMMAND_INVALID;
			}
			ossConfirmationMessage << std::endl;
			_confirmationMessage = ossConfirmationMessage.str();
			return _confirmationMessage;
		} else {
			return command;
		}

	} catch (std::string& errmsg) {
		std::cout << errmsg;
	}
	return _confirmationMessage;
}

//  This function calls getAllTasks on the private _store attribute to read
//  all the tasks from the text file in the directory that the user specified.
//  It sets the private vector of task pointers, _listOfTasks, in the Logic object
//  so that the users' tasks are not lost when he exits Taskr.
void Logic::initializeListOfTasks() {
	try {
		_listOfTasks = _store.getAllTasks();
		for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
			if (_listOfTasks[i]->isDone()) {
				_doneTasksCount++;
			}
		}
	}
	catch (int& errMsgNo) {
		std::ostringstream errorOSS;
		errorOSS << "Error index: " << errMsgNo << ". Taskr file may be corrupted, please check your file configurations.\n";
		throw errorOSS.str();
	}
	
}

//  This function decides what kind of Task the user has input, creates the correct
//  type of task (Floating, Timed or Deadline) dynamically and pushes the child object
//  onto the vector of Task pointers. 
void Logic::executeAdd(std::ostringstream& ossConfirmationMessage) {
	try {
		int taskType = _parse.getTaskType();
		assert(taskType == FLOATING_TASK || taskType == TIMED_TASK || taskType == DEADLINE_TASK);
		if (taskType == FLOATING_TASK) {
			FloatingTask* tempFloatTask = new FloatingTask;
			tempFloatTask->setTaskType(taskType);
			tempFloatTask->setDescription(_parse.getDescription());

			addTask(tempFloatTask, ossConfirmationMessage);

		} else if (taskType == TIMED_TASK) {
			TimedTask* tempTimedTask = new TimedTask;
			tempTimedTask->setTaskType(taskType);
			tempTimedTask->setDescription(_parse.getDescription());
			tempTimedTask->setStart(_parse.getStart());
			tempTimedTask->setEnd(_parse.getEnd());

			addTask(tempTimedTask, ossConfirmationMessage);

		} else if (taskType == DEADLINE_TASK) {
			DeadlineTask* tempDeadlineTask = new DeadlineTask;
			tempDeadlineTask->setTaskType(taskType);
			tempDeadlineTask->setDescription(_parse.getDescription());
			tempDeadlineTask->setDue(_parse.getEnd());

			addTask(tempDeadlineTask, ossConfirmationMessage);
		} else {
			ossConfirmationMessage << "C\n" << ERROR_INVALID_DESCRIPTION;
		}
		LOG(INFO) << "Result of addTask is:\n" << ossConfirmationMessage.str() << std::endl;
	}
	catch (std::string& errmsg) {
		std::ostringstream errorOSS;
		errorOSS << "Error index: " << errmsg << ". There was an error in adding that task. Please check if input is valid.\n";
		throw errorOSS.str();
	}
	
}

//  This function takes in a task to be added to the list and checks if it is valid.
//  If it is valid, the new task will be added to the list and a confirmation message will be set.
//  If not, the respective error message will be set.
void Logic::addTask(Task* tempTask, std::ostringstream& ossConfirmationMessage) {
	try {
		ossConfirmationMessage << "C\n";
		if (isRepeated(tempTask)) {
			ossConfirmationMessage << ERROR_REPEATED_TASK;
		} else if (tempTask->getDescription() == "") {
			ossConfirmationMessage << ERROR_INVALID_DESCRIPTION;
		} else {
			_history.saveState(_listOfTasks);
			_listOfTasks.push_back(tempTask);
			sortTasksByTime(_listOfTasks);
			_store.saveFile(_listOfTasks);
			ossConfirmationMessage << "\"" << tempTask->getDescription() << "\"" << MESSAGE_ADDED;
		}
	}
	catch (std::string& errmsg) {
		std::ostringstream errorOSS;
		errorOSS << "Error index: " << errmsg << ". There was an error in saving that task to file. Please check if input is valid.\n";
		throw errorOSS.str();
	}
}

//  This function reads the index of the task to be edited and checks if the index is valid.
//  If it is valid, a new task will be created based on the user input and added to the list.
//  If not, the respective error message will be set.
void Logic::editTask(std::ostringstream& ossConfirmationMessage) {
	int indexToEdit;
	indexToEdit = _parse.getIndex();
	assert(indexToEdit != NULL);
	ossConfirmationMessage << "C\n";
	if (!isValidIndex(indexToEdit)) {
		ossConfirmationMessage << indexToEdit << ERROR_INDEX_OUT_OF_RANGE;
	} else if (_parse.getDescription() == "") {
		ossConfirmationMessage << ERROR_INVALID_DESCRIPTION;
	} else {
		int typeOfTaskToEdit;
		typeOfTaskToEdit = _listOfTasks[indexToEdit - 1]->getTaskType();
		std::string oldTaskDescription;
		std::string newTaskDescription;
		oldTaskDescription = _listOfTasks[indexToEdit + _doneTasksCount - 1]->getDescription();
		newTaskDescription = _parse.getDescription();

		_history.saveState(_listOfTasks);

		if (typeOfTaskToEdit == FLOATING_TASK) {
			FloatingTask* tempFloatTask = new FloatingTask;
			tempFloatTask->setTaskType(typeOfTaskToEdit);
			tempFloatTask->setDescription(_parse.getDescription());

			_listOfTasks[indexToEdit + _doneTasksCount - 1] = tempFloatTask;

		} else if (typeOfTaskToEdit == TIMED_TASK) {
			TimedTask* tempTimedTask = new TimedTask;
			tempTimedTask->setTaskType(typeOfTaskToEdit);
			tempTimedTask->setDescription(_parse.getDescription());
			tempTimedTask->setStart(_parse.getStart());
			tempTimedTask->setEnd(_parse.getEnd());

			_listOfTasks[indexToEdit + _doneTasksCount - 1] = tempTimedTask;

		} else if (typeOfTaskToEdit == DEADLINE_TASK) {
			DeadlineTask* tempDeadlineTask = new DeadlineTask;
			tempDeadlineTask->setTaskType(typeOfTaskToEdit);
			tempDeadlineTask->setDescription(_parse.getDescription());
			tempDeadlineTask->setDue(_parse.getEnd());

			_listOfTasks[indexToEdit + _doneTasksCount - 1] = tempDeadlineTask;
		}
		sortTasksByTime(_listOfTasks);
		_store.saveFile(_listOfTasks);
		ossConfirmationMessage << "\"" << oldTaskDescription << "\"" << MESSAGE_EDITED << "\"" << newTaskDescription << "\"." << std::endl;
	}
	LOG(INFO) << "Result of editTask is:\n" << ossConfirmationMessage.str() << std::endl;
}

//  This function has an option of taking in a parameter after the command "display", ie the user can enter "display <parameter>".
//  Parameters include:
//  1. done  == displays all tasks that are marked as done
//  2. today == displays all tasks that are due today
//  3. tomorrow? == displays all tasks that are due tomorrow.?
//  
//  If the user does not specify a parameter, this function will return all outstanding tasks that are being tracked.
void Logic::displayList(std::ostringstream& ossConfirmationMessage) {
	std::string parameter;
	parameter = _parse.getDescription();
	assert(parameter == "done" || parameter == "today" || parameter == "");
	if (!_listOfTasks.empty()) {
		std::vector<Task*> tempTaskList;

		//display all done tasks
		if (parameter == "done") {
			std::vector<Task> doneTasks;
			for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
				if (_listOfTasks[i]->isDone()) {
					tempTaskList.push_back(_listOfTasks[i]);
				}
			}
			//display all tasks for today	
		} else if (parameter == "today") {
			time_t currentTime;
			struct tm localTime;
			time(&currentTime);                   // Get the current time
			localtime_s(&localTime, &currentTime);  // Convert the current time to the local time

			for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
				if (!(_listOfTasks[i]->isDone()) && _listOfTasks[i]->getTaskType() == TIMED_TASK && _listOfTasks[i]->checkMonth() == (localTime.tm_mon + 1) && _listOfTasks[i]->checkDay() == localTime.tm_mday) {
					tempTaskList.push_back(_listOfTasks[i]);
				} else if (!(_listOfTasks[i]->isDone()) && _listOfTasks[i]->getTaskType() == DEADLINE_TASK && _listOfTasks[i]->checkMonth() == (localTime.tm_mon + 1) && _listOfTasks[i]->checkDay() == localTime.tm_mday) {
					tempTaskList.push_back(_listOfTasks[i]);
				}
			}
			//display all undone tasks
		} else if (parameter == "") {
			for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
				if (!(_listOfTasks[i]->isDone())) {
					tempTaskList.push_back(_listOfTasks[i]);
				}
			}
			sortTasksByTime(tempTaskList);
		} else {
			ossConfirmationMessage << "C\n" << "\"display " << parameter << "\"" << ERROR_USER_COMMAND_INVALID;
			return;
		}

		if (!tempTaskList.empty()) {
			listToString(tempTaskList, ossConfirmationMessage);
		} else {
			ossConfirmationMessage << "C\n" << ERROR_EMPTY_LIST;
		}

	} else {
		ossConfirmationMessage << "C\n" << ERROR_EMPTY_LIST;
	}
	LOG(INFO) << "Result of displayList is:\n" << ossConfirmationMessage.str() << std::endl;
}

//  This function deletes an item from Taskr, but can be undone using the "undo" command.
//  It can take in an index after the command "delete", ie the user can enter "display <index>". Only a single index can be input at once.
//  As such, to use this function the user must first enter the "display" function to find the index of the corresponding task to delete.
//  A valid index (i.e. within the number of tasks that are being tracked) must be input, or the function will return an error message.
void Logic::deleteTask(std::ostringstream& ossConfirmationMessage) {
	int indexToDelete;
	indexToDelete = _parse.getIndex();
	assert(indexToDelete != NULL);
	ossConfirmationMessage << "C\n";
	if (isValidIndex(indexToDelete)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[_doneTasksCount + indexToDelete - 1]->getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks.erase(_listOfTasks.begin() + _doneTasksCount + indexToDelete - 1);
		_store.saveFile(_listOfTasks);
		ossConfirmationMessage << "\"" << taskDescription << "\"" << MESSAGE_DELETED;
	} else {
		ossConfirmationMessage << indexToDelete << ERROR_INDEX_OUT_OF_RANGE;
	}	
}

//  This function marks an indicated task as done and removes it from the list visible to the user, but keeps a copy of it in the saved txt file.
//  It takes in an index after the command "done", i.e. the user can enter "done <index>". Only a single index can be input at once.
//  As such, to use this function the user must first enter the "display" function to find the index of the corresponding task to mark as done.
//  A valid index (i.e. within the number of tasks that are being tracked) must be input, or the function will return an error message.
void Logic::setDone(std::ostringstream& ossConfirmationMessage) {
	int indexToSet;
	indexToSet = _parse.getIndex();
	assert(indexToSet != NULL);
	ossConfirmationMessage << "C\n";
	if (isValidIndex(indexToSet)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[indexToSet + _doneTasksCount - 1]->getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks[indexToSet + _doneTasksCount - 1]->setAsDone();
		_doneTasksCount++;
		sortDoneTasks();
		_store.saveFile(_listOfTasks);
		ossConfirmationMessage << "\"" << taskDescription << "\"" << MESSAGE_MARK_DONE;
	}
	else {
		ossConfirmationMessage << indexToSet << ERROR_INDEX_OUT_OF_RANGE;
	}
	LOG(INFO) << "Result of setDone is:\n" << ossConfirmationMessage.str() << std::endl;
}

//  This function makes use of the History object to save up to three snapshots of the Logic object's _listOfTasks.
//  There is a maximum of 3 undo actions, and the user CANNOT undo an undo. As such, the user must confirm his/her action before he/she can proceed.
//  This command does not take in any parameters. When the user has made the maximum number undos, an error message will indicate that there is nothing left to undo.
void Logic::undoLastAction(std::ostringstream& ossConfirmationMessage) {
	ossConfirmationMessage << "C\n";
	if (isActionConfirmed()) {
		if (_history.isEmpty()) {
			ossConfirmationMessage << ERROR_NOTHING_TO_UNDO;
		} else {
			_listOfTasks = _history.popLastState();
			_store.saveFile(_listOfTasks);
			ossConfirmationMessage << MESSAGE_UNDO;
		}
	} else {
		ossConfirmationMessage << MESSAGE_OPERATION_NOT_EXECUTED;
	}
	LOG(INFO) << "Result of undoLastAction is:\n" << ossConfirmationMessage.str() << std::endl;
}

//  This function searches all the tasks being tracked for a string that the user inputs, and returns all the tasks that contain that string.
//  This function takes in a parameter after the "search" command, i.e. "search <parameter>". Any task that contains part of the parameter in its description will be
//  returned. If no task is found, an error message will indicate that there are no matches in Taskr.
void Logic::searchList(std::string searchString, std::ostringstream& ossConfirmationMessage) {
	std::vector<Task*> tempList;
	if (_listOfTasks.empty()) {
		ossConfirmationMessage << "C\n" << ERROR_EMPTY_LIST;
	} else {
		for (std::vector<Task*>::iterator iter = _listOfTasks.begin(); iter != _listOfTasks.end(); iter++) {
			std::size_t found;
			found = (*iter)->getDescription().find(searchString);
			if (found != std::string::npos) {
				tempList.push_back(*iter);
			}
		}
		if (tempList.empty()) {
			ossConfirmationMessage << "C\n" << ERROR_EMPTY_LIST;
		}
		listToString(tempList, ossConfirmationMessage);
	}
	LOG(INFO) << "Result of searchList is:\n" << ossConfirmationMessage.str() << std::endl;
}

//  This function changes the file location where Taskr.txt is stored. As this action cannot be undone, the user is required to confirm
//  his/her action before proceeding. The file path input MUST be a valid file path.
void Logic::changeFilePath(std::string filepath, std::ostringstream& ossConfirmationMessage) {
	ossConfirmationMessage << "C\n";
	if (isActionConfirmed()) {
		_store.setFilePath(filepath);
		_store.saveFile(_listOfTasks);
		ossConfirmationMessage << MESSAGE_FILEPATH_CHANGED << "\"" << filepath << "\"." << std::endl;
	}
	else {
		ossConfirmationMessage << MESSAGE_OPERATION_NOT_EXECUTED;
	}
	LOG(INFO) << "Result of changeFilePath is:\n" << ossConfirmationMessage.str() << std::endl;
}

//  This function tells the UI to display the help screen.
void Logic::showHelp(std::ostringstream& ossConfirmationMessage) {
	ossConfirmationMessage << "HELP\n";
}

bool Logic::isActionConfirmed() {
	std::cout << MESSAGE_CONFIRM_ACTION;
	std::string userConfirmation;
	std::cin >> userConfirmation;
	//get rid of the carriage return
	std::string rubbish;
	std::getline(std::cin, rubbish);

	if (userConfirmation == "y" || userConfirmation == "Y" || userConfirmation == "yes" || userConfirmation == "Yes" || userConfirmation == "YES") {
		LOG(INFO) << "User confirmed action." << std::endl;
		return true;
	}
	else {
		LOG(INFO) << "User canceled action." << std::endl;
		return false;
	}
}

bool Logic::isValidIndex(int index) {
	return index > 0 && index <= (unsigned)(_listOfTasks.size() - _doneTasksCount);
}

bool Logic::isRepeated(Task* task) {
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (task->getDescription() == _listOfTasks[i]->getDescription()) {
			LOG(INFO) << "Task entered is repeated." << std::endl;
			return true;
		}
	}
	return false;
}

//  This function is used internally, and sorts all tasks that are marked
//  as done to be placed at the front of Logic object's _listOfTasks.
void Logic::sortDoneTasks() {
	std::vector<Task*> sortedDoneTaskList;
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (_listOfTasks[i]->isDone()) {
			sortedDoneTaskList.push_back(_listOfTasks[i]);
		}
	}
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (!(_listOfTasks[i]->isDone())) {
			sortedDoneTaskList.push_back(_listOfTasks[i]);
		}
	}
	_listOfTasks = sortedDoneTaskList;
	LOG(INFO) << "Done tasks sorted to the top." << std::endl;
}

void Logic::listToString(std::vector<Task*> listOfTasks, std::ostringstream& ossConfirmationMessage) {
	int displayIndex = 1;
	for (unsigned int i = 0; i < listOfTasks.size(); i++) {
		ossConfirmationMessage << listOfTasks[i]->toString() << std::endl;
	}
}

void Logic::sortTasksByTime(std::vector<Task*>& listOfTasks) {
	for (int i = 0; i + 1 < listOfTasks.size(); i++) {
		int minIndex = i;
		for (unsigned int j = i + 1; j < listOfTasks.size(); j++) {
			if (checkTiming(listOfTasks[j], listOfTasks[minIndex])) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			std::swap(listOfTasks[minIndex], listOfTasks[i]);
		}
	}
	LOG(INFO) << "Tasks have been sorted chronologically." << std::endl;
}

bool Logic::checkTiming(Task* taskA, Task* taskB) {
	if (taskA->checkMonth() < taskB->checkMonth()) {
		return true;
	} else if (taskA->checkMonth() == taskB->checkMonth()) {
		if (taskA->checkDay() < taskB->checkDay()) {
			return true;
		} else if (taskA->checkDay() == taskB->checkDay()) {
			if (taskA->checkHour() < taskB->checkHour()) {
				return true;
			} else if (taskA->checkHour() == taskB->checkHour()) {
				if (taskA->checkMinute() < taskB->checkMinute()) {
					return true;
				} else if (taskA->checkMinute() == taskB->checkMinute()) {
					return false;
				}
			}
		}
	}	
	return false;
}

std::string Logic::printListToString() {
	std::ostringstream oss;
	listToString(_listOfTasks, oss);
	return oss.str();	
}
