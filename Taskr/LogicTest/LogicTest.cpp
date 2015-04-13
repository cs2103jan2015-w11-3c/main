#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{		
	TEST_CLASS(LogicTest)
	{
	public:
		//@author A0111966A
		TEST_METHOD(testAddFloatingTask) {
			Logic logic;
			std::ostringstream confirmationMessage;
			std::string expected = "F\ntest adding of floating task.\n\n";

			FloatingTask temp;
			temp.setDescription("test adding of floating task.");
			logic.addTask(&temp, confirmationMessage);
			Assert::AreEqual(expected, logic.printListToString());
		}

		TEST_METHOD(testAddTimedTask) {
			Logic logic;
			std::ostringstream confirmationMessage;
			std::string expected = "T\ntest adding of timed task.\n04/05\n1600\n04/05\n1800\n\n";
			
			TimedTask temp;
			temp.setDescription("test adding of timed task.");
			temp.setStartDateMonth(5);
			temp.setStartDateDay(4);
			temp.setStartTimeHour(16);
			temp.setStartTimeMinute(0);
			temp.setEndDateMonth(5);
			temp.setEndDateDay(4);
			temp.setEndTimeHour(18);
			temp.setEndTimeMinute(0);

			logic.addTask(&temp, confirmationMessage);
			Assert::AreEqual(expected, logic.printListToString());
		}

		TEST_METHOD(testAddDeadlineTask) {
			Logic logic;
			std::ostringstream confirmationMessage;
			std::string expected = "D\ntest adding of deadline task.\n04/05\n1600\n\n";

			DeadlineTask temp;
			temp.setDescription("test adding of deadline task.");
			temp.setDueDateMonth(5);
			temp.setDueDateDay(4);
			temp.setDueTimeHour(16);
			temp.setDueTimeMinute(0);

			logic.addTask(&temp, confirmationMessage);
			Assert::AreEqual(expected, logic.printListToString());
		}
		
		TEST_METHOD(testExecuteAdd) {
			Logic logic;
			std::string confirmationMessage;
			std::string expectedAdd = "C\n\"test marking a task as done.\" has been added to Taskr!\n\n";
			std::string expectedDone = "C\n\"test marking a task as done.\" has been has been marked done!\n\n";

			confirmationMessage = logic.executeCommand("add test marking a task as done.");
			Assert::AreEqual(expectedAdd, confirmationMessage);
		}

		TEST_METHOD(testDeleteTask) {
			Logic logic;
			std::string confirmationMessage;
			std::string expectedAdd = "C\n\"test deleting a task.\" has been added to Taskr!\n\n";
			std::string expectedDelete = "C\n\"test deleting a task.\" has been deleted from Taskr.\n\n";

			confirmationMessage = logic.executeCommand("add test deleting a task.");
			Assert::AreEqual(expectedAdd, confirmationMessage);
			confirmationMessage = logic.executeCommand("delete 1");
			Assert::AreEqual(expectedDelete, confirmationMessage);
		}

		TEST_METHOD(testEditFloatingTask) {
			Logic logic;
			std::string confirmationMessage;
			std::string expectedAdd = "C\n\"test editing a floating task.\" has been added to Taskr!\n\n";
			std::string expectedEdit = "C\n\"test editing a floating task.\" has been edited to \"this test works.\".\n\n";

			confirmationMessage = logic.executeCommand("add test editing a floating task.");
			Assert::AreEqual(expectedAdd, confirmationMessage);
			confirmationMessage = logic.executeCommand("edit 1 this test works.");
			Assert::AreEqual(expectedEdit, confirmationMessage);
		}

	
		TEST_METHOD(testMarkingDone) {
			Logic logic;
			std::string confirmationMessage;
			std::string expectedDone = "C\n\"mark this task as done.\" has been marked done!\n\n";

			confirmationMessage = logic.executeCommand("add mark this task as done.");
			confirmationMessage = logic.executeCommand("done 1");
			Assert::AreEqual(expectedDone, confirmationMessage);
		}


		TEST_METHOD(testShowHelp)
		{
			Logic logic;
			std::ostringstream confirmationMessage;
			std::string expected = "HELP\n";
			logic.showHelp(confirmationMessage);
			Assert::AreEqual(expected, confirmationMessage.str());
		}

	};
}
