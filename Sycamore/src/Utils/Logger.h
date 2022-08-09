#pragma once
#include"spdlog/spdlog.h"
#include"spdlog/sinks/stdout_color_sinks.h"

//helps with putting the variables in the argument of the macros
#include <sstream>

//the class should be only used for initializing
//if you want to log out stuff use the macros

class Logger
{
private:
	static Logger m_instance;
	Logger() {}

	std::shared_ptr<spdlog::logger> console;
public:
	static Logger& Get() {
		return m_instance;
	}

	Logger(const Logger&) = delete;

	void Init();

	/*
	+= operator for strings is already overloaded (thx c++)

	std::string start = "Hello ";
    std::string end = "World";
    start += end;

    std::cout << start << std::endl;
	*/

	friend std::string& operator<<(std::string& source, const std::string& string) {
		return source += string;
	}
};

#define LOGGER_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOGGER_WARNING(...) SPDLOG_WARN(__VA_ARGS__)
#define LOGGER_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)

