#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{		
	TEST_CLASS(LogicTest)
	{
	public:
		
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