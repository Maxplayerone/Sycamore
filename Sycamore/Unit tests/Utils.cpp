#include"Utils.h"

namespace SM_Tests {
	int totalTests = 0;
	//the amount of tests in one session
	int totalTestsSession = 0;
	int correctTestsSession = 0;

	void PrintResultForTest(bool testValidation, const std::string& functionName) {
		totalTests++;
		totalTestsSession++;

		if (testValidation) {
			correctTestsSession++;
		}
		else {
			LOGGER_ERROR("----------------------------------------");

			std::stringstream ss;
			ss << totalTests << ". failed " << functionName;
			LOGGER_ERROR(ss.str());

			LOGGER_ERROR("----------------------------------------");
		}
	}

	CheckingSession::CheckingSession() {
		totalTestsSession = 0;
		correctTestsSession = 0;
	}

	CheckingSession::~CheckingSession() {
		LOGGER_INFO("<><><><><><><><><><><><><><><><><><><><><><>");
		std::stringstream ss;
		ss << "Passed " << correctTestsSession << " out of " << totalTestsSession << " tests";
		LOGGER_INFO(ss.str());
		LOGGER_INFO("<><><><><><><><><><><><><><><><><><><><><><>");
		std::cout << std::endl;

		totalTestsSession = 0;
		correctTestsSession = 0;
	}
}