#pragma once
#include"../src/Utils/Logger.h"

#include"../Physics/Rigidbody/IntersectionDetection.h"
#include"../Physics/Primitives/Primitives.h"

#include"../Math/SM_math.h"

#include"../src/Rendering/DebugDraw.h"

#define ASSERT(x) if(!(x)) __debugbreak();

namespace SM_Tests {

	//function that only unit tests functions that return boolean
	void PrintTestResult(bool testValidation, const std::string& functionName);

	class CheckingSession {
	public:
		CheckingSession();
		~CheckingSession();
	};

#define HEADER(...) LOGGER_WARNING(__VA_ARGS__); \
	SM_Tests::CheckingSession session = SM_Tests::CheckingSession()

#define CHECK(FUNCTION);  \
	PrintTestResult(FUNCTION(), #FUNCTION)
}
