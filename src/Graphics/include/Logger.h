#ifndef GF_UTILS_LOGGER_H
#define GF_UTILS_LOGGER_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>

namespace GF {
	namespace Utils {

		class Logger {
		public:
			enum class LogType { INFO, WARNING, ERROR_WARN, ERROR_HALT };

		private:
			static std::ofstream mErrorLogFile;
			static bool mLogToErrorFile;

		public:
			static void open(const std::string& errorLogFilePath);
			static void log(LogType type, const std::string& message);

		private:
			static void init();

		};

	}
}

#endif
