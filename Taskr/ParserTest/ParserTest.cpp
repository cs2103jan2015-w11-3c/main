#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest
{		
	TEST_CLASS(ParserTest)
	{
	public:
		
		TEST_METHOD(TestConvertLowerCase)
		{
			Parser parse;
			std::string upper("UPPER");
			std::string expected("upper");
			Assert::AreEqual(expected, parse.convertLowerCase(upper));

		}
		TEST_METHOD(isTimedTask){
			Parser parse;
			std::string input1("add task1 8 apr 8am 9am");
			Parser parse1(input1);
			parse1.setDescription();
			int matchIndex, foundIndex;
			Assert::IsTrue(parse1.isTimedTask(input1, matchIndex, foundIndex));
			Assert::AreEqual(0, matchIndex);

			std::string task2("task2 8 apr");
			Assert::IsFalse(parse.isTimedTask(task2, matchIndex, foundIndex));

			std::string task3("task3 8 apr 9pm - 11pm");
			Assert::IsTrue(parse.isTimedTask(task3, matchIndex, foundIndex));
			Assert::AreEqual(1, matchIndex);

		}
		TEST_METHOD(isDeadlineTask){
			Parser parse;
			std::string task1("task1 8 apr 8am");
			int matchIndex, foundIndex;
			Assert::IsTrue(parse.isDeadlineTask(task1, matchIndex, foundIndex));
			Assert::AreEqual(3, matchIndex);

			std::string task2("task2");
			Assert::IsFalse(parse.isDeadlineTask(task2, matchIndex, foundIndex));

			std::string task3("task3 8 dec");
			Assert::IsTrue(parse.isDeadlineTask(task3, matchIndex, foundIndex));
			Assert::AreEqual(11, matchIndex);
		}


	};
}