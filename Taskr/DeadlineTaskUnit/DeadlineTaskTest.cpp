#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeadlineTaskUnit
{		
	TEST_CLASS(DeadlineTaskTest)
	{
	public:
		
		TEST_METHOD(setDueDateMonth_TEST)
		{
			DeadlineTask DDLTask;
			DDLTask.setDueDateMonth(1);
			Assert::AreEqual(DDLTask.getDueDateMonth(), 1);
		}

		TEST_METHOD(setDueDateDay_TEST)
		{
			DeadlineTask DDLTask;
			DDLTask.setDueDateDay(1);
			Assert::AreEqual(DDLTask.getDueDateDay(), 1);
		}

		TEST_METHOD(setDueDateHour_TEST)
		{
			DeadlineTask DDLTask;
			DDLTask.setDueTimeHour(1);
			Assert::AreEqual(DDLTask.getDueTimeHour(), 1);

		}

		TEST_METHOD(setDueDateMinute_TEST)
		{
			DeadlineTask DDLTask;
			DDLTask.setDueTimeMinute(1);
			Assert::AreEqual(DDLTask.getDueTimeMinute(), 1);

		}
	


	};
}