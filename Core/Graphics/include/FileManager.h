#ifndef	UTILS_FILEMANAGER_H
#define UTILS_FILEMANAGER_H
#pragma once

#include <sstream>
#include <stdexcept>

namespace GF {
	namespace Utils {

		class FileManager {
		public:
			static std::string fileToString(const std::string& path);
			static void stringToFile(const std::string& input, const std::string& path);

		};

	}
}

#endif
