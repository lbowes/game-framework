#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

namespace Framework {
	namespace Utils {

		class ConsoleLogger {
		public:
			enum class LogType { INFO, WARNING, ERROR_WARN, ERROR_HALT };

		private:
			static std::ofstream mErrorLogFile;
			static HANDLE mConsoleWindowHandle;
			static CONSOLE_FONT_INFOEX mFontInfo;
			static bool mLogToErrorFile;

		public:
			static void open();
			static void open(std::string errorLogFilePath);
			static void log(LogType type, std::string message);

		private:
			static void init();

		};
	}

}

#endif
