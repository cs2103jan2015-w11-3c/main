#include "Logic.h"


const std::string Logic::MESSAGE_ADDED = " has been added to Taskr!\n";
const std::string Logic::MESSAGE_DELETED = " has been deleted from Taskr.\n";
const std::string Logic::MESSAGE_MARK_DONE = " has been marked done!\n";
const std::string Logic::MESSAGE_ERROR_TASK_NOT_EXIST = " does not exist.\n";
const std::string Logic::MESSAGE_EDITED = " has been edited to ";
const std::string Logic::MESSAGE_UNDO = "Your last action has been undone.\n";
const std::string Logic::MESSAGE_FILEPATH_CHANGED = "Your filepath has been changed to ";
const std::string Logic::MESSAGE_OPERATION_NOT_EXECUTED = "Your last command was not executed.";
const std::string Logic::MESSAGE_CONFIRM_ACTION = "This action cannot be undone. Are you sure you wish to carry on? (y/n): ";

const std::string Logic::ERROR_REPEATED_TASK = " is a repeated task.\n";
const std::string Logic::ERROR_INDEX_OUT_OF_RANGE = " is an invalid index.\n";
const std::string Logic::ERROR_EMPTY_LIST = "The list is currently empty.\n";
const std::string Logic::ERROR_INVALID_DESCRIPTION = "The input description is invalid. Please do not enter an empty task.\n";
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


std::string Logic::executeCommand(std::string userInput) {
	std::string command;
	std::string description;
	std::ostringstream oss;

	_parse = Parser(userInput);
	command = _parse.getCommand();

	if (command != "exit") {

		if (command == "add") {
			executeAdd(oss);
		} else if (command == "delete") {
			deleteTask(oss);
		} else if (command == "display") {
			displayList(oss);
		} else if (command == "edit") {		//BIG LOGIC PROBLEM HERE.
			editTask(oss);
		} else if (command == "done") {
			setDone(oss);
		} else if (command == "undo") {
			undoLastAction(oss);
		} else if (command == "search") {
			searchList(_parse.getDescription(), oss);
		} else if (command == "file") {
			changeFilePath(_parse.getDescription(), oss);
		} else if (command == "help") {
			showHelp(oss);
		} else {
			oss << "C\n" << "\"" << command << "\"" << ERROR_USER_COMMAND_INVALID;
		}
		oss << std::endl;
		_confirmationMessage = oss.str();
		return _confirmationMessage;

	}
	else {
		return command;
	}
}

std::string Logic::getCommand() {
	return _parse.getCommand();
}

void Logic::initializeListOfTasks() {
	_listOfTasks = _store.getAllTasks();
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (_listOfTasks[i]->isDone()) {
			_doneTasksCount++;
		}
	}
}

void Logic::executeAdd(std::ostringstream& oss) {
	int taskType = _parse.getTaskType();

	if (taskType == FLOATING_TASK) {
		FloatingTask* tempFloatTask = new FloatingTask;
		tempFloatTask->setTaskType(taskType);
		tempFloatTask->setDescription(_parse.getDescription());

		addTask(tempFloatTask, oss);

	} else if (taskType == TIMED_TASK) {
		TimedTask* tempTimedTask = new TimedTask;
		tempTimedTask->setTaskType(taskType);
		tempTimedTask->setDescription(_parse.getDescription());

		tempTimedTask->setStart(_parse.getStart());
		tempTimedTask->setEnd(_parse.getEnd());
/*
		tempTimedTask.setStartTimeHour(_parse.getStartTimeHour);
		tempTimedTask.setStartTimeMinute(_parse.getStartTimeMinute);
		tempTimedTask.setStartDateDay(_parse.getStartDateDay);
		tempTimedTask.setStartDateMonth(_parse.getStartDateMonth);
		tempTimedTask.setEndTimeHour(_parse.getEndTimeHour);
		tempTimedTask.setEndTimeMinute(_parse.getEndTimeMinute);
		tempTimedTask.setEndDateDay(_parse.getEndDateDay);
		tempTimedTask.setEndDateMonth(_parse.getEndDateMonth);
*/
		addTask(tempTimedTask, oss);

	} else if (taskType == DEADLINE_TASK) {
		DeadlineTask* tempDeadlineTask = new DeadlineTask;
		tempDeadlineTask->setTaskType(taskType);
		tempDeadlineTask->setDescription(_parse.getDescription());

		tempDeadlineTask->setDue(_parse.getEnd());
/*
		tempDeadlineTask.setDueTimeHour(_parse.getDueTimeHour);
		tempDeadlineTask.setDueTimeMinute(_parse.getDueTimeMinute);
		tempDeadlineTask.setDueDateDay(_parse.getDueDateDay);
		tempDeadlineTask.setDueDateMonth(_parse.getDueDateMonth);
*/
		addTask(tempDeadlineTask, oss);
	} else {
		oss << "C\n" << ERROR_INVALID_DESCRIPTION;
	}
}

void Logic::addTask(Task* tempTask, std::ostringstream& oss) {
	oss << "C\n";
	if (isRepeated(tempTask)) {
		oss << ERROR_REPEATED_TASK;
	} else if (tempTask->getDescription() == "") {
		oss << ERROR_INVALID_DESCRIPTION;
	} else {
		_history.saveState(_listOfTasks);
		_listOfTasks.push_back(tempTask);
		sortTasksByTime(_listOfTasks);
		_store.saveFile(_listOfTasks);
		oss << "\"" << tempTask->getDescription() << "\"" << MESSAGE_ADDED;
	}
}

void Logic::editTask(std::ostringstream& oss) {
	int indexToEdit;
	indexToEdit = _parse.getIndex();
	
	oss << "C\n";
	if (!isValidIndex(indexToEdit)) {
		oss << indexToEdit << ERROR_INDEX_OUT_OF_RANGE;
	} else if (_parse.getDescription() == "") {
		oss << ERROR_INVALID_DESCRIPTION;
	} else {
		int typeOfTaskToEdit;
		typeOfTaskToEdit = _listOfTasks[indexToEdit]->getTaskType();
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
		oss << "\"" << oldTaskDescription << "\"" << MESSAGE_EDITED << "\"" << newTaskDescription << "\"." << std::endl;
	}
}

void Logic::displayList(std::ostringstream& oss) {
	std::string parameter;
	parameter = _parse.getDescription();
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
				if (!(_listOfTasks[i]->isDone()) && _listOfTasks[i]->getTaskType() == 2 && _listOfTasks[i]->checkMonth() == (localTime.tm_mon + 1) && _listOfTasks[i]->checkDay() == localTime.tm_mday) {
					tempTaskList.push_back(_listOfTasks[i]);
				} else if (!(_listOfTasks[i]->isDone()) && _listOfTasks[i]->getTaskType() == 3 && _listOfTasks[i]->checkMonth() == (localTime.tm_mon + 1) && _listOfTasks[i]->checkDay() == localTime.tm_mday) {
					tempTaskList.push_back(_listOfTasks[i]);
				}
			}
		//display all undone tasks
		} else {
			for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
				if (!(_listOfTasks[i]->isDone())) {
					tempTaskList.push_back(_listOfTasks[i]);
				}
			}
			sortTasksByTime(tempTaskList);
		}

		if (!tempTaskList.empty()) {
			listToString(tempTaskList, oss);
		} else {
			oss << "C\n" << ERROR_EMPTY_LIST;
		}

	} else {
		oss << "C\n" << ERROR_EMPTY_LIST;
	}
}


void Logic::deleteTask(std::ostringstream& oss) {
	int indexToDelete;
	indexToDelete = _parse.getIndex();
	oss << "C\n";
	if (isValidIndex(indexToDelete)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[_doneTasksCount + indexToDelete - 1]->getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks.erase(_listOfTasks.begin() + _doneTasksCount + indexToDelete - 1);
		_store.saveFile(_listOfTasks);
		oss << "\"" << taskDescription << "\"" << MESSAGE_DELETED;
	}
	else {
		oss << indexToDelete << ERROR_INDEX_OUT_OF_RANGE;
	}
}

void Logic::setDone(std::ostringstream& oss) {
	int indexToSet;
	indexToSet = _parse.getIndex();
	oss << "C\n";
	if (isValidIndex(indexToSet)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[indexToSet + _doneTasksCount - 1]->getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks[indexToSet + _doneTasksCount - 1]->setAsDone();
		_doneTasksCount++;
		sortDoneTasks();
		_store.saveFile(_listOfTasks);
		oss << "\"" << taskDescription << "\"" << MESSAGE_MARK_DONE;
	}
	else {
		oss << indexToSet << ERROR_INDEX_OUT_OF_RANGE;
	}
}

void Logic::undoLastAction(std::ostringstream& oss) {
	oss << "C\n";
	if (isActionConfirmed()) {
		if (_history.isEmpty()) {
			oss << ERROR_NOTHING_TO_UNDO;
		} else {
			_listOfTasks = _history.popLastState();
			_store.saveFile(_listOfTasks);
			oss << MESSAGE_UNDO;
		}
	} else {
		oss << MESSAGE_OPERATION_NOT_EXECUTED;
	}
}

void Logic::searchList(std::string searchString, std::ostringstream& oss) {
	std::vector<Task*> tempList;
	if (_listOfTasks.empty()) {
		oss << "C\n" << ERROR_EMPTY_LIST;
	} else {
		for (std::vector<Task*>::iterator iter = _listOfTasks.begin(); iter != _listOfTasks.end(); iter++) {
			std::size_t found;
			found = (*iter)->getDescription().find(searchString);
			if (found != std::string::npos) {
				tempList.push_back(*iter);
			}
		}
		listToString(tempList, oss);
	}
}

void Logic::changeFilePath(std::string filepath, std::ostringstream& oss) {
	oss << "C\n";
	if (isActionConfirmed()) {
		_store.setFilePath(filepath);
		_store.saveFile(_listOfTasks);
		oss << MESSAGE_FILEPATH_CHANGED << "\"" << filepath << "\"." << std::endl;
	}
	else {
		oss << MESSAGE_OPERATION_NOT_EXECUTED;
	}
}

void Logic::showHelp(std::ostringstream& oss) {
	oss << "HELP\n";
}


bool Logic::isActionConfirmed() {
	std::cout << MESSAGE_CONFIRM_ACTION;
	std::string userConfirmation;
	std::cin >> userConfirmation;
	if (userConfirmation == "y" || userConfirmation == "Y" || userConfirmation == "yes" || userConfirmation == "Yes" || userConfirmation == "YES") {
		return true;
	}
	else {
		return false;
	}
}

bool Logic::isValidIndex(int index) {
	return index > 0 && index <= (unsigned)(_listOfTasks.size() - _doneTasksCount);
}

bool Logic::isRepeated(Task* task) {
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (task->getDescription() == _listOfTasks[i]->getDescription()) {
			return true;
		}
	}
	return false;
}

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
}

void Logic::listToString(std::vector<Task*> listOfTasks, std::ostringstream& oss) {
	int displayIndex = 1;
	for (unsigned int i = 0; i < listOfTasks.size(); i++) {
		oss << listOfTasks[i]->toString() << std::endl;
	}
}

void Logic::sortTasksByTime(std::vector<Task*> listOfTasks) {
	for (int i = 0; i < (listOfTasks.size() - 1); i++) {
		int minIndex = i;
		for (unsigned int j = i + 1; j < listOfTasks.size(); j++) {
			if (checkTiming(listOfTasks[j], listOfTasks[minIndex])) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swapTasks(listOfTasks[minIndex], listOfTasks[i]);
		}
	}
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

void Logic::swapTasks(Task* taskA, Task* taskB) {
	Task temp = *taskA;
	*taskA = *taskB;
	*taskB = temp;
}