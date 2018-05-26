#include "FileManager.h"
#include "ConsoleLogger.h"

namespace Framework {
	namespace Utils {

		std::string FileManager::fileToString(std::string filePath) {
			std::ifstream inFile(filePath);
			if (!inFile) {
				ConsoleLogger::log(ConsoleLogger::LogType::ERROR_WARN, "File '" + filePath + "' could not be opened.");
				return 0;
			}
			std::stringstream sStr;
			sStr << inFile.rdbuf();

			return sStr.str();
		}

		void FileManager::stringToFile(std::string& inputString, std::string filePath) {
			std::ofstream outFile(filePath);
			if (!outFile)
				ConsoleLogger::log(ConsoleLogger::LogType::ERROR_WARN, "File '" + filePath + "' could not be opened.");
			else
				outFile << inputString;
		}

	}
}