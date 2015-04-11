//@author A0114077L
#include "stdafx.h"
#include "DeadlineTask.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace jsoncons;
using namespace std;

namespace DeadlineTaskUnit
{
	TEST_CLASS(DeadlineTaskTest)
	{
	public:

		TEST_METHOD(setDueDateMonth_TEST)
		{
			DeadlineTask ddlTask;
			ddlTask.setDueDateMonth(1);
			Assert::AreEqual(ddlTask.getDueDateMonth(), 1);
		}

		TEST_METHOD(setDueDateDay_TEST)
		{
			DeadlineTask ddlTask;
			ddlTask.setDueDateDay(1);
			Assert::AreEqual(ddlTask.getDueDateDay(), 1);
		}

		TEST_METHOD(setDueDateHour_TEST)
		{
			DeadlineTask ddlTask;
			ddlTask.setDueTimeHour(1);
			Assert::AreEqual(ddlTask.getDueTimeHour(), 1);

		}

		TEST_METHOD(setDueDateMinute_TEST)
		{
			DeadlineTask ddlTask;
			ddlTask.setDueTimeMinute(1);
			Assert::AreEqual(ddlTask.getDueTimeMinute(), 1);

		}

		//json unit testing for deadline task
		TEST_METHOD(json_TEST)
		{
			DeadlineTask ddlTask;
			string desc = "1";

			ddlTask.setDescription(desc);
			ddlTask.setAsDone();
			ddlTask.setDueDateDay(1);
			ddlTask.setDueDateMonth(2);
			ddlTask.setDueTimeHour(3);
			ddlTask.setDueTimeMinute(4);

			json taskJson = ddlTask.toJson();
			Assert::AreEqual(desc, taskJson[Task::TASK_DESCRIPTION].as<string>());
			Assert::IsTrue(taskJson[Task::IS_DONE].as<bool>());
			Assert::AreEqual(1, taskJson[Task::DUE_DATE_DAY].as<int>());
			Assert::AreEqual(2, taskJson[Task::DUE_DATE_MONTH].as<int>());
			Assert::AreEqual(3, taskJson[Task::DUE_TIME_HOUR].as<int>());
			Assert::AreEqual(4, taskJson[Task::DUE_TIME_MINUTE].as<int>());

			DeadlineTask ddlTaskFromJson(taskJson);
			Assert::AreEqual(desc, ddlTaskFromJson.getDescription());
			Assert::IsTrue(ddlTaskFromJson.isDone());
			Assert::AreEqual(1, ddlTaskFromJson.getDueDateDay());
			Assert::AreEqual(2, ddlTaskFromJson.getDueDateMonth());
			Assert::AreEqual(3, ddlTaskFromJson.getDueTimeHour());
			Assert::AreEqual(4, ddlTaskFromJson.getDueTimeMinute());
		}




	};
}