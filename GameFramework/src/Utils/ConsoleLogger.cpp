#include "ConsoleLogger.h"

namespace Framework {
	namespace Utils {
		
		std::ofstream ConsoleLogger::mErrorLogFile;
		HANDLE ConsoleLogger::mConsoleWindowHandle;
		CONSOLE_FONT_INFOEX ConsoleLogger::mFontInfo;
		bool ConsoleLogger::mLogToErrorFile = false;

		void ConsoleLogger::open() {
			init();
		}

		void ConsoleLogger::open(std::string errorLogFilePath) {
			mLogToErrorFile = true;

			mErrorLogFile.open(errorLogFilePath, std::ofstream::trunc);
			if (!mErrorLogFile)
				std::cout << "ErrorLog filepath incorrect!" << std::endl;

			init();
		}

		void ConsoleLogger::log(LogType type, std::string message) {
			switch (type) {
				case LogType::INFO:
					SetConsoleTextAttribute(mConsoleWindowHandle, 160);
					std::cout << "INFO:";

					SetConsoleTextAttribute(mConsoleWindowHandle, 15);
					std::cout << "    " << message;
					break;

				case LogType::WARNING:
					SetConsoleTextAttribute(mConsoleWindowHandle, 224);
					std::cout << "WARNING:";

					SetConsoleTextAttribute(mConsoleWindowHandle, 15);
					std::cout << " " << message;

					if (mLogToErrorFile) mErrorLogFile << message << std::endl;
					break;
				
				case LogType::ERROR_WARN:
					SetConsoleTextAttribute(mConsoleWindowHandle, 192);
					std::cout << "ERROR:";

					SetConsoleTextAttribute(mConsoleWindowHandle, 15);
					std::cout << "   " << message;

					if (mLogToErrorFile) mErrorLogFile << message << std::endl;
					break;

				case LogType::ERROR_HALT:
					SetConsoleTextAttribute(mConsoleWindowHandle, 192);
					std::cout << "ERROR:";

					SetConsoleTextAttribute(mConsoleWindowHandle, 15);
					std::cout << "   " << message;
					std::cin.get();

					if (mLogToErrorFile) mErrorLogFile << message << std::endl;
					break;
			}
		}

		void ConsoleLogger::init() {
			mConsoleWindowHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			mFontInfo.cbSize = sizeof(mFontInfo);
			SetCurrentConsoleFontEx(mConsoleWindowHandle, FALSE, &mFontInfo);
		}

	}
}