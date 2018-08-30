#include "Logger.h"

namespace GF {
	namespace Utils {
		
		std::ofstream Logger::mErrorLogFile;
		bool Logger::mLogToErrorFile = false;

		void Logger::open(const std::string& errorLogFilePath) {
			mLogToErrorFile = true;

			mErrorLogFile.open(errorLogFilePath, std::ofstream::trunc);
			if (!mErrorLogFile)
				printf("Error log filepath '%s' incorrect.", errorLogFilePath.c_str());
		}

		void Logger::log(LogType type, const std::string& message) {
			switch (type) {
				case LogType::INFO:
					printf("\e[38;2;0;255;0mGF_INFO:");
					printf("\e[0m    %s\n", message.c_str());
					break;

				case LogType::WARNING:
					printf("\e[38;2;255;255;0mGF_WARNING:");
					printf("\e[0m %s\n", message.c_str());
					break;
				
				case LogType::ERROR_WARN:
					printf("\e[38;2;255;0;0mGF_WARNING:");
					printf("\e[0m %s\n", message.c_str());
					break;

				case LogType::ERROR_HALT:
					printf("\e[38;2;255;0;0mGF_ERROR:");
					printf("\e[0m   %s\n", message.c_str());
					std::cin.get();
					break;
			}

			if (mLogToErrorFile) 
				mErrorLogFile << message << std::endl;
		}

	}
}