#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageTest
{		
	TEST_CLASS(StorageTest)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			Storage storageObject;
			//Assert::AreEqual(true, storageObject.);

		}

		TEST_METHOD(getAllTasksTest) {
			Storage storageObject;
			std::ostringstream oss;
			std::ostringstream confirmationMassage;
			std::string userInput = "test getAllTasks";

		}

	};
}