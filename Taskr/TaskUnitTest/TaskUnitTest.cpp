#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace jsoncons;
using namespace std;

namespace TaskUnitTest
{
	TEST_CLASS(TaskUnitTest)
	{
	public:

		TEST_METHOD(setDescription_TEST)
		{
			//test partition of string consisting of numbers and letters
			Task task;
			task.setDescription("finish cs2103");
			std::string description = "finish cs2103";
			Assert::AreEqual(task.getDescription(), description);

			//test partition of string consisting of only numbers
			task.setDescription("123");
			description = "123";
			Assert::AreEqual(task.getDescription(), description);

		}

		TEST_METHOD(setAsDone_TEST)
		{
			Task task;
			task.setAsDone();
			Assert::IsTrue(task.isDone());
		}

		//json test for task/floating task
		TEST_METHOD(json_TEST)
		{
			Task task;
			string desc = "1";

			task.setDescription(desc);
			task.setAsDone();
			json taskJson = task.toJson();
			Assert::AreEqual(desc, taskJson[Task::TASK_DESCRIPTION].as<string>());
			Assert::IsTrue(taskJson[Task::IS_DONE].as<bool>());

			Task taskFromJson(taskJson);
			Assert::AreEqual(desc, taskFromJson.getDescription());
			Assert::IsTrue(taskFromJson.isDone());
			
		}
	};
}

