#pragma once
#include"spdlog/spdlog.h"
#include"spdlog/sinks/stdout_color_sinks.h"

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
};

#define LOGGER_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOGGER_WARNING(...) SPDLOG_WARN(__VA_ARGS__)
#define LOGGER_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)

