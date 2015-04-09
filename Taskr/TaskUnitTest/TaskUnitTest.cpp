#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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



	};
}

