#ifndef SHADER_H
#define SHADER_H
#pragma once

#include <GLEW\glew.h>
#include <vector>
#include <glm\glm\mat4x4.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

#include "Core/Resource.hpp"

namespace Framework {
	namespace Graphics {

		struct Uniform {
			std::string mName = "";
			int mLocation = 0;

			Uniform(std::string name, int location) :
				mName(name),
				mLocation(location)
			{ }

		};

		class Shader : public Resource {
		private:
			static int mCurrentlyBound;
			
			std::vector<int> mCompiledShaders;
			std::vector<Uniform> mUniforms;

			int mHandle = 0;

		public:
			Shader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string resourceID);
			Shader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath, std::string resourceID);
			~Shader() = default;

			void bind();
			void unbind() const { glUseProgram(0); mCurrentlyBound = 0; }
			void addUniform(std::string name);

			void addUniformWithDefault(std::string name, int i);
			void addUniformWithDefault(std::string name, int a, int b);
			void addUniformWithDefault(std::string name, int a, int b, int c);
			void addUniformWithDefault(std::string name, int a, int b, int c, int d);
			void addUniformWithDefault(std::string name, float i);
			void addUniformWithDefault(std::string name, glm::vec2 vec);
			void addUniformWithDefault(std::string name, glm::vec3 vec);
			void addUniformWithDefault(std::string name, glm::vec4 vec);
			void addUniformWithDefault(std::string name, glm::mat4 matrix);

			void setUniform(int index, int i);
			void setUniform(int index, int a, int b);
			void setUniform(int index, int a, int b, int c);
			void setUniform(int index, int a, int b, int c, int d);
			void setUniform(int index, float i);
			void setUniform(int index, glm::vec2 vec);
			void setUniform(int index, glm::vec3 vec);
			void setUniform(int index, glm::vec4 vec);
			void setUniform(int index, glm::mat4 matrix);

			inline int getHandle() const { return mHandle; }

		private:
			int compileShader(int shaderType, std::string source);
			bool createProgram();
			bool uniformAdded(std::string name);

		};

	}
}

#endif
