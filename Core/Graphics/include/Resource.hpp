#ifndef RESOURCE_H
#define RESOURCE_H
#pragma once

#include <string>

namespace GF {

	class Resource {
	private:
		std::string mUniqueId = "";
			
	public:
		Resource(const std::string& uid) :
			mUniqueId(uid)
		{ }

		virtual ~Resource() = default;

		inline std::string getUniqueID() const { return mUniqueId; }

	};

}

#endif
