#include "FileManager.h"
#include "Logger.h"

namespace GF {
	namespace Utils {

		std::string FileManager::fileToString(const std::string& path) {
			std::ifstream inFile(path);
			if (!inFile) {
				Logger::log(Logger::LogType::ERROR_WARN, "File '" + path + "' could not be opened.");
				return "";
			}
			std::stringstream sStr;
			sStr << inFile.rdbuf();

			return sStr.str();
		}

		void FileManager::stringToFile(const std::string& input, const std::string& path) {
			std::ofstream outFile(path);
			if (!outFile)
				Logger::log(Logger::LogType::ERROR_WARN, "File '" + path + "' could not be opened.");
			else
				outFile << input;
		}

	}
}