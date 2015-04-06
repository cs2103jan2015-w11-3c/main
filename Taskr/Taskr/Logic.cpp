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
const std::string Logic::ERROR_REPEATED_TASK = " is a repeated floating task.\n";
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
			//implementing polymorphism of Tasks
			//executeAdd(oss);
			Task tempTask;
			tempTask.setDescription(_parse.getDescription());
			addTask(tempTask, oss);
		}
		else if (command == "delete") {
			int indexToDelete;
			indexToDelete = _parse.getIndex();
			deleteTask(indexToDelete, oss);
		}
		else if (command == "display") {
			std::string parameter;
			parameter = _parse.getDescription();
			displayList(parameter, oss);
		}
		else if (command == "edit") {
			Task tempTask;
			int indexToEdit;
			indexToEdit = _parse.getIndex();
			tempTask.setDescription(_parse.getDescription());
			editTask(indexToEdit, tempTask, oss);
		}
		else if (command == "done") {
			int indexToSet;
			indexToSet = _parse.getIndex();
			setDone(indexToSet, oss);
		}
		else if (command == "undo") {
			undoLastAction(oss);
		}
		else if (command == "search") {
			searchList(_parse.getDescription(), oss);
		}
		else if (command == "file") {
			changeFilePath(_parse.getDescription(), oss);
		}
		else {
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
		if (_listOfTasks[i].isDone()) {
			_doneTasksCount++;
		}
	}
}

////POLYMORPHISM OF TASKS
//void Logic::executeAdd(std::ostringstream& oss) {
//	int taskType = _parse.getTaskType();
//
//	if (taskType == FLOATING_TASK) {
//		FloatingTask tempFloatTask;
//		tempFloatTask.setTaskType(taskType);
//		tempFloatTask.setDescription(_parse.getDescription());

//		addTask(tempFloatTask, oss);

//	} else if (taskType == TIMED_TASK) {
//		TimedTask tempTimedTask;
//		tempTimedTask.setTaskType(taskType);
//		tempTimedTask.setDescription(_parse.getDescription());

//		tempTimedTask.setStartTimeHour(_parse.getStartTimeHour);
//		tempTimedTask.setStartTimeMinute(_parse.getStartTimeMinute);
//		tempTimedTask.setStartDateDay(_parse.getStartDateDay);
//		tempTimedTask.setStartDateMonth(_parse.getStartDateMonth);
//		
//		tempTimedTask.setEndTimeHour(_parse.getEndTimeHour);
//		tempTimedTask.setEndTimeMinute(_parse.getEndTimeMinute);
//		tempTimedTask.setEndDateDay(_parse.getEndDateDay);
//		tempTimedTask.setEndDateMonth(_parse.getEndDateMonth);

//		addTask(tempTimedTask, oss);

//	} else if (taskType == DEADLINE_TASK) {
//		DeadlineTask tempDeadlineTask;
//		tempDeadlineTask.setTaskType(taskType);
//		tempDeadlineTask.setDescription(_parse.getDescription());
//
//		tempDeadlineTask.setDueTimeHour(_parse.getDueTimeHour);
//		tempDeadlineTask.setDueTimeMinute(_parse.getDueTimeMinute);
//		tempDeadlineTask.setDueDateDay(_parse.getDueDateDay);
//		tempDeadlineTask.setDueDateMonth(_parse.getDueDateMonth);

//		addTask(tempDeadlineTask, oss);
//	} else {
//		tempTask.setTaskType(0);
//	}
//}

void Logic::addTask(Task tempTask, std::ostringstream& oss) {
	oss << "C\n";
	if (isRepeated(tempTask)) {
		oss << ERROR_REPEATED_TASK;
	} else if (tempTask.getDescription() == "") {
		oss << ERROR_INVALID_DESCRIPTION;
	} else {
		_history.saveState(_listOfTasks);
		_listOfTasks.push_back(tempTask);

		//must change implementation of saveFile in storage. basically need to accomodate the multiple kinds of tasks.
		_store.saveFile(_listOfTasks);
		oss << "\"" << tempTask.getDescription() << "\"" << MESSAGE_ADDED;
	}
}

void Logic::editTask(int index, Task task, std::ostringstream& oss) {
	oss << "C\n";
	if (!isValidIndex(index)) {
		oss << index << ERROR_INDEX_OUT_OF_RANGE;
	} else if (task.getDescription() == "") {
		oss << ERROR_INVALID_DESCRIPTION;
	} else {
		std::string oldTaskDescription;
		std::string newTaskDescription;
		oldTaskDescription = _listOfTasks[index + _doneTasksCount - 1].getDescription();
		newTaskDescription = task.getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks[index + _doneTasksCount - 1] = task;
		_store.saveFile(_listOfTasks);
		oss << "\"" << oldTaskDescription << "\"" << MESSAGE_EDITED << "\"" << newTaskDescription << "\"." << std::endl;
	}
}

void Logic::displayList(std::string parameter, std::ostringstream& oss) {
	if (!_listOfTasks.empty()) {
		if (parameter == "done") {
			std::vector<Task> doneTasks;
			for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
				if (_listOfTasks[i].isDone()) {
					doneTasks.push_back(_listOfTasks[i]);
				}
			}
			sortTasksByTime(doneTasks);
			listToString(doneTasks, oss);

		} else if (parameter == "today") {
			std::vector<Task> doneTasks;
			for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
				if (!(_listOfTasks[i].isDone()) && ((_listOfTasks[i].getTaskType()) == 1)) {
					doneTasks.push_back(_listOfTasks[i]);
				}
				//if (_listOfTasks[i].getDateString() == )
			}
			sortTasksByTime(doneTasks);
			listToString(doneTasks, oss);

		} else if (parameter == "") {
			std::vector<Task> undoneTasks;
			for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
				if (!(_listOfTasks[i].isDone())) {
					undoneTasks.push_back(_listOfTasks[i]);
				}
			}
			sortTasksByTime(undoneTasks);
			listToString(undoneTasks, oss);
		}
	} else {
		oss << "C\n" << ERROR_EMPTY_LIST;
	}
}


void Logic::deleteTask(int index, std::ostringstream& oss) {
	oss << "C\n";
	if (isValidIndex(index)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[_doneTasksCount + index - 1].getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks.erase(_listOfTasks.begin() + _doneTasksCount + index - 1);
		_store.saveFile(_listOfTasks);
		oss << "\"" << taskDescription << "\"" << MESSAGE_DELETED;
	}
	else {
		oss << index << ERROR_INDEX_OUT_OF_RANGE;
	}
}

void Logic::setDone(int index, std::ostringstream& oss) {
	oss << "C\n";
	if (isValidIndex(index)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[index + _doneTasksCount - 1].getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks[index + _doneTasksCount - 1].setAsDone();
		_doneTasksCount++;
		sortDoneTasks();
		_store.saveFile(_listOfTasks);
		oss << "\"" << taskDescription << "\"" << MESSAGE_MARK_DONE;
	}
	else {
		oss << index << ERROR_INDEX_OUT_OF_RANGE;
	}
}

void Logic::undoLastAction(std::ostringstream& oss) {
	oss << "C\n";
	if (isActionConfirmed()) {
		if (_history.isEmpty()) {
			oss << ERROR_NOTHING_TO_UNDO;
		}
		else {
			_listOfTasks = _history.popLastState();
			_store.saveFile(_listOfTasks);
			oss << MESSAGE_UNDO;
		}
	}
	else {
		oss << MESSAGE_OPERATION_NOT_EXECUTED;
	}
	
}

void Logic::searchList(std::string searchString, std::ostringstream& oss) {
	std::vector<Task> tempList;
	if (_listOfTasks.empty()) {
		oss << "C\n" << ERROR_EMPTY_LIST;
	} else {
		for (std::vector<Task>::iterator iter = _listOfTasks.begin(); iter != _listOfTasks.end(); iter++) {
			std::size_t found;
			found = iter->getDescription().find(searchString);
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
		oss << MESSAGE_FILEPATH_CHANGED << "\"" << filepath << "\".";
	}
	else {
		oss << MESSAGE_OPERATION_NOT_EXECUTED;
	}
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

bool Logic::isRepeated(Task task) {
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (task.getDescription() == _listOfTasks[i].getDescription()) {
			return true;
		}
	}
	return false;
}

void Logic::sortDoneTasks() {
	std::vector<Task> sortedDoneTaskList;
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (_listOfTasks[i].isDone()) {
			sortedDoneTaskList.push_back(_listOfTasks[i]);
		}
	}
	for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
		if (!(_listOfTasks[i].isDone())) {
			sortedDoneTaskList.push_back(_listOfTasks[i]);
		}
	}
	_listOfTasks = sortedDoneTaskList;
}

void Logic::listToString(std::vector<Task> listOfTasks, std::ostringstream& oss) {
	int displayIndex = 1;
	for (unsigned int i = 0; i < listOfTasks.size(); i++) {
		oss << listOfTasks[i].toString() << std::endl;
		//if (!(listOfTasks[i].isDone())) {
		//	oss << displayIndex++ << ". " << listOfTasks[i].toString() << std::endl;
		//}
	}
}

//precondition and usage: logic passes an unsorted vector of tasks as the parameter. this is used in
//the "display" function, where the user should see a chronologically sorted list.
//considerations: not all tasks have start datetime end datetime due datetime.
//implement using if else blocks based ont _taskType of Task object, create a new vector<Task>,
//push_back earliest timed to latest timed, followed by earliest deadline to latest deadline, 
//followed by floating tasks. equate new vector<Task> to listOfTasks.
void Logic::sortTasksByTime(std::vector<Task>& listOfTasks) {
	/*for (int i = 0; i < (listOfTasks.size() - 1); i++) {
		int minIndex = i;
		for (unsigned int j = i + 1; j < listOfTasks.size(); j++) {
			if (checkTiming(listOfTasks[j], listOfTasks[minIndex]) == -1) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swapTasks(listOfTasks[minIndex], listOfTasks[i]);
		}
	}*/
}

//check month then year then hour then minute, two if else blocks each ( < and then ==)
int Logic::checkTiming(Task, Task) {
	//to implement by monday
	return 0;
}

void Logic::swapTasks(Task& taskA, Task& taskB) {
	Task temp = taskA;
	taskA = taskB;
	taskB = temp;
}