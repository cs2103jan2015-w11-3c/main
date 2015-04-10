#include "stdafx.h"
#include "CppUnitTest.h"
#include "TimedTask.h"
#include "DeadlineTask.h"
#include "FloatingTask.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace StorageTest
{		
	TEST_CLASS(StorageTest)
	{
	public:
	
		TEST_METHOD(storage_TEST)
		{
			Storage storage;
			vector<Task*> tasks;
			FloatingTask task1;
			task1.setDescription("t1");

			DeadlineTask task2;
			task2.setDescription("t2");
			task2.setDueDateDay(1);
			task2.setDueDateMonth(2);
			task2.setDueTimeHour(3);
			task2.setDueTimeMinute(4);

			TimedTask task3;
			task3.setDescription("t3");
			task3.setAsDone();
			task3.setStartDateDay(1);
			task3.setStartDateMonth(2);
			task3.setStartTimeHour(3);
			task3.setStartTimeMinute(4);
			task3.setEndDateDay(5);
			task3.setEndDateMonth(6);
			task3.setEndTimeHour(7);
			task3.setEndTimeMinute(8);

			tasks.push_back(&task1);
			tasks.push_back(&task2);
			tasks.push_back(&task3);

			storage.saveFile(tasks);
			vector<Task*> tasksFromFile = storage.getAllTasks();
			Assert::AreEqual(tasks.size(), tasksFromFile.size());

			for (int i = 0; i < tasks.size(); i++)
			{
				Task *task = tasks[i];
				Task *taskFromFile = tasksFromFile[i];
				Assert::AreEqual(task->getDescription(), taskFromFile->getDescription());
				Assert::AreEqual(task->isDone(), taskFromFile->isDone());
				Assert::AreEqual(task->getStartDateDay(), taskFromFile->getStartDateDay());
				Assert::AreEqual(task->getStartDateMonth(), taskFromFile->getStartDateMonth());
				Assert::AreEqual(task->getStartTimeHour(), taskFromFile->getStartTimeHour());
				Assert::AreEqual(task->getStartTimeMinute(), taskFromFile->getStartTimeMinute());

				Assert::AreEqual(task->getEndDateDay(), taskFromFile->getEndDateDay());
				Assert::AreEqual(task->getEndDateMonth(), taskFromFile->getEndDateMonth());
				Assert::AreEqual(task->getEndTimeHour(), taskFromFile->getEndTimeHour());
				Assert::AreEqual(task->getEndTimeMinute(), taskFromFile->getEndTimeMinute());

				Assert::AreEqual(task->getDueDateDay(), taskFromFile->getDueDateDay());
				Assert::AreEqual(task->getDueDateMonth(), taskFromFile->getDueDateMonth());
				Assert::AreEqual(task->getDueTimeHour(), taskFromFile->getDueTimeHour());
				Assert::AreEqual(task->getDueTimeMinute(), taskFromFile->getDueTimeMinute());
			}

		

		}


	};
}