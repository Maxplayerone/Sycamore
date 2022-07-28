#include "Logger.h"

Logger Logger::m_instance;

void Logger::Init() {
	spdlog::set_pattern("%^[%T] [ At line: %#, file %s]%$ %v");
	console = spdlog::stdout_color_mt("Main console");
	spdlog::set_default_logger(console);

	SPDLOG_INFO("Logger initialized");
}