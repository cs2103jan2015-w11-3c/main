//@author A0111966A
#include "FloatingTask.h"

using namespace std;
using namespace jsoncons;

FloatingTask::FloatingTask() {
	_taskType = 1;
}

FloatingTask::FloatingTask(json taskJson) : Task(taskJson) {
}

FloatingTask::~FloatingTask() {
}

string FloatingTask::toString() {
	ostringstream oss;
	oss << "F\n";
	oss << getDescription() << std::endl;
	return oss.str();
}
