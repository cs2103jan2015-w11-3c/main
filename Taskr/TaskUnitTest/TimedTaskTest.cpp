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

		
		//json test for timed task
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

		TEST_METHOD(setStartDate_TEST)
		{
			TimedTask timedTask;
			timedTask.setStartDateDay(1);
			Assert::AreEqual(timedTask.getStartDateDay(), 1);
		}

		TEST_METHOD(setStartDateDay_TEST)
		{
			TimedTask timedTask;
			timedTask.setStartDateMonth(2);
			Assert::AreEqual(timedTask.getStartDateMonth(), 2);
		}

		TEST_METHOD(setStartDateHour_TEST)
		{
			TimedTask timedTask;
			timedTask.setStartTimeHour(3);
			Assert::AreEqual(timedTask.getStartTimeHour(), 3);

		}

		TEST_METHOD(setStartDateMinute_TEST)
		{
			TimedTask timedTask;
			timedTask.setStartTimeMinute(4);
			Assert::AreEqual(timedTask.getStartTimeMinute(), 4);

		}

		TEST_METHOD(setEndDateDay_TEST)
		{
			TimedTask timedTask;
			timedTask.setEndDateDay(5);
			Assert::AreEqual(timedTask.getEndDateDay(), 5);
		}

		TEST_METHOD(setEndDateMonth_TEST)
		{
			TimedTask timedTask;
			timedTask.setEndDateMonth(6);
			Assert::AreEqual(timedTask.getEndDateMonth(), 6);
		}

		TEST_METHOD(setEndDateHour_TEST)
		{
			TimedTask timedTask;
			timedTask.setEndTimeHour(7);
			Assert::AreEqual(timedTask.getEndTimeHour(), 7);

		}

		TEST_METHOD(setEndDateMinute_TEST)
		{
			TimedTask timedTask;
			timedTask.setEndTimeMinute(8);
			Assert::AreEqual(timedTask.getEndTimeMinute(), 8);

		}




	};
}