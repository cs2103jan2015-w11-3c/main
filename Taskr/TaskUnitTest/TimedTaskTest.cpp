#include "stdafx.h"
#include "TimedTask.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace jsoncons;
using namespace std;

namespace DeadlineTaskUnit
{
	TEST_CLASS(TimedTaskTest)
	{
	public:

		

		TEST_METHOD(json_TEST)
		{
			TimedTask timedTask;
			string desc = "1";

			timedTask.setDescription(desc);
			timedTask.setAsDone();
			timedTask.setStartDateDay(1);
			timedTask.setStartDateMonth(2);
			timedTask.setStartTimeHour(3);
			timedTask.setStartTimeMinute(4);
			timedTask.setEndDateDay(5);
			timedTask.setEndDateMonth(6);
			timedTask.setEndTimeHour(7);
			timedTask.setEndTimeMinute(8);
			
			json taskJson = timedTask.toJson();
			Assert::AreEqual(desc, taskJson[Task::TASK_DESCRIPTION].as<string>());
			Assert::IsTrue(taskJson[Task::IS_DONE].as<bool>());
			Assert::AreEqual(1, taskJson[Task::START_DATE_DAY].as<int>());
			Assert::AreEqual(2, taskJson[Task::START_DATE_MONTH].as<int>());
			Assert::AreEqual(3, taskJson[Task::START_TIME_HOUR].as<int>());
			Assert::AreEqual(4, taskJson[Task::START_TIME_MINUTE].as<int>());
			Assert::AreEqual(5, taskJson[Task::END_DATE_DAY].as<int>());
			Assert::AreEqual(6, taskJson[Task::END_DATE_MONTH].as<int>());
			Assert::AreEqual(7, taskJson[Task::END_TIME_HOUR].as<int>());
			Assert::AreEqual(8, taskJson[Task::END_TIME_MINUTE].as<int>());

			TimedTask timedTaskFromJson(taskJson);
			Assert::AreEqual(desc, timedTaskFromJson.getDescription());
			Assert::IsTrue(timedTaskFromJson.isDone());
			Assert::AreEqual(1, timedTaskFromJson.getStartDateDay());
			Assert::AreEqual(2, timedTaskFromJson.getStartDateMonth());
			Assert::AreEqual(3, timedTaskFromJson.getStartTimeHour());
			Assert::AreEqual(4, timedTaskFromJson.getStartTimeMinute());
			Assert::AreEqual(5, timedTaskFromJson.getEndDateDay());
			Assert::AreEqual(6, timedTaskFromJson.getEndDateMonth());
			Assert::AreEqual(7, timedTaskFromJson.getEndTimeHour());
			Assert::AreEqual(8, timedTaskFromJson.getEndTimeMinute());
		}




	};
}