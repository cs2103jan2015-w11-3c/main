#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UITest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(doSegment)
		{
			UI ui;
			std::string feedback("D\ncs v0.4\n8 Apr\n11am\n\nT\nproject meeting\n9 Apr\n2pm\n9 Apr\n4pm\n\nF\ntest task\n\n");
			std::vector<std::string> tokens = ui.doSegment(feedback);

			std::string expected0("D");
			Assert::AreEqual(expected0, tokens[0]);

			std::string expected1("cs v0.4");
			Assert::AreEqual(expected1, tokens[1]);

			std::string expected2("");
			Assert::AreEqual(expected2, tokens[5]);

			size_t size = 15;
			Assert::AreEqual(size, tokens.size());
		}

		TEST_METHOD(findFirstEmptyIndex){
			UI ui;
			std::string feedback("D\ncs v0.4\n8 Apr\n11am\n\nT\nproject meeting\n9 Apr\n2pm\n9 Apr\n4pm\n\nF\ntest task\n\n");
			std::vector<std::string> tokens = ui.doSegment(feedback);

			int expected = 4;
			Assert::AreEqual(expected, ui.findFirstEmptyIndex(tokens));
		}

		TEST_METHOD(getNumberOfTasks){
			UI ui;
			std::string feedback("D\ncs v0.4\n8 Apr\n11am\n\nT\nproject meeting\n9 Apr\n2pm\n9 Apr\n4pm\n\nF\ntest task\n\n");
			std::vector<std::string> tokens = ui.doSegment(feedback);

			int expected = 3;
			Assert::AreEqual(expected, ui.getNumberOfTasks(tokens));
		}

		TEST_METHOD(getDate){
			UI ui;
			std::string feedback1("D\ncs v0.4\n8 Apr\n11am\n\n");
			std::string feedback2("T\nproject meeting\n9 Apr\n2pm\n9 Apr\n4pm\n\n");
			std::string feedback3("F\nie meeting\n\n");

			std::vector<std::string> tokens1 = ui.doSegment(feedback1);
			std::string expected1("8 Apr");
			Assert::AreEqual(expected1, ui.getDate(tokens1));

			std::vector<std::string> tokens2 = ui.doSegment(feedback2);
			std::string expected2("9 Apr");
			Assert::AreEqual(expected2, ui.getDate(tokens2));

			std::vector<std::string> tokens3 = ui.doSegment(feedback3);
			std::string expected3("unscheduled");
			Assert::AreEqual(expected3, ui.getDate(tokens3));
		}

		TEST_METHOD(removePrinted){
			UI ui;
			std::string feedback1("T\nproject meeting\n9 Apr\n2pm\n9 Apr\n4pm\n\nF\ntest task\n\n");
			std::vector<std::string> tokens = ui.doSegment(feedback1);
			std::vector<std::string> output = ui.removePrinted(tokens);
			
			std::string expected("test task");
			
			Assert::AreEqual(expected, output[1]);
		}

	};
}