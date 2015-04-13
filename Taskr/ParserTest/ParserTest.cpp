#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest
{		
	TEST_CLASS(ParserTest)
	{
	public:
		//@author A0114943H
		TEST_METHOD(TestConvertLowerCase)
		{
			Parser parse;
			std::string upper("UPPER");
			std::string expected("upper");
			Assert::AreEqual(expected, parse.convertLowerCase(upper));

		}
		TEST_METHOD(isTimedTask){
			std::string task1("task1 today 8am 9am");
			Parser parse1(task1);
			parse1.setDescription();
			int matchIndex, foundIndex;
			Assert::IsTrue(parse1.isTimedTask(task1, matchIndex, foundIndex));

			std::string task2("task2 8 apr");
			Parser parse2(task2);
			Assert::IsFalse(parse2.isTimedTask(task2, matchIndex, foundIndex));

			std::string task3("task3 8 apr 9pm");
			Parser parse3(task3);
			Assert::IsFalse(parse3.isTimedTask(task3, matchIndex, foundIndex));

		}
		TEST_METHOD(isDeadlineTask){
			Parser parse;
			std::string task1("task1 8 apr 8am");
			int matchIndex, foundIndex;
			Assert::IsTrue(parse.isDeadlineTask(task1, matchIndex, foundIndex));

			std::string task2("task2");
			Assert::IsFalse(parse.isDeadlineTask(task2, matchIndex, foundIndex));

			std::string task3("task3 8 dec");
			Assert::IsTrue(parse.isDeadlineTask(task3, matchIndex, foundIndex));
		}
		TEST_METHOD(findFirstTimeToken){
			std::string input("webcast 7am");
			Parser parse(input);
			parse.setDescription();
			int expected = 9;
			Assert::AreEqual(expected, parse.findFirstTimeToken(input));
		}
		TEST_METHOD(extractTime){
			int timeIndex = 1;
			int foundIndex = 9;
			std::string input("webcast 7am");
			Parser parse(input);
			parse.setDescription();
			std::string expected("7am");
			Assert::AreEqual(expected, parse.extractTime(timeIndex, foundIndex));
		}
	};
}