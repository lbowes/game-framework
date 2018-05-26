#ifndef	FILEMANAGER_H
#define FILEMANAGER_H
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Framework {
	namespace Utils {

		class FileManager {
		public:
			static std::string fileToString(std::string filePath);
			static void stringToFile(std::string& inputString, std::string filePath);

		};

	}
}

#endif
