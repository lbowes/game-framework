#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP
#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace GF {
	namespace Utils {

		static std::vector<std::string> splitString(const std::string& str, char delimiter) {
			using namespace std;
			
			vector<string> result;
			string item;
			stringstream stream(str);

			while (getline(stream, item, delimiter))
				result.push_back(item);

			return result;
		}

	}
}

#endif
