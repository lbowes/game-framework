#ifndef GF_GRAPHICS_SHADER_H
#define GF_GRAPHICS_SHADER_H
#pragma once

#include "Resource.hpp"

#include <GL/glew.h>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

namespace GF {
	namespace Graphics {

		class Shader : public Resource {
		private:
			static int mCurrentlyBound;
			std::vector<int> mCompiledShaderHandles;
			std::unordered_map<std::string, int> mUniformLocations;
			int mProgramHandle = 0;

		public:
			Shader(const std::string& resID, const std::string& vertPath, const std::string& fragPath, const std::string& geomPath = "");
			~Shader() = default;

			void bind() const;
			void unbind() const;
			void addUniform(const std::string& name);

			void addUniformWithDefault(const std::string& name, float value);
			void addUniformWithDefault(const std::string& name, glm::vec2 value);
			void addUniformWithDefault(const std::string& name, glm::vec3 value);
			void addUniformWithDefault(const std::string& name, glm::vec4 value);
			void addUniformWithDefault(const std::string& name, glm::mat4 value);

			void setUniform(const std::string& name, float value);
			void setUniform(const std::string& name, glm::vec2 value);
			void setUniform(const std::string& name, glm::vec3 value);
			void setUniform(const std::string& name, glm::vec4 value);
			void setUniform(const std::string& name, glm::mat4 value);

			int getProgramHandle() const { return mProgramHandle; }

		private:
			int compileShader(int shaderType, const std::string& source);
			void createProgram();

		};

	}
}

#endif
