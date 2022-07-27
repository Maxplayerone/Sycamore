#include"Logger.h"

int main() {
	Logger::Get().Init();
	LOGGER_INFO("Starting the program");

	return 0;
}