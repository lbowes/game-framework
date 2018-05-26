#include "../Graphics/Shader.h"
#include "Utils/FileManager.h"
#include "Utils/ConsoleLogger.h"

//For checking if OpenGL has been initialised
#include "../Core/Window.h"

namespace Framework {
	namespace Graphics {

		int Shader::mCurrentlyBound = 0;

		Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string resourceID) :
			Resource(resourceID)
		{
			if (!Window::mOpenGLInitialised) {
				Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Tried to create Shader '" + resourceID + "' before OpenGL was initialised.\n\n");
				return;
			}
			
			int vertexShader = compileShader(GL_VERTEX_SHADER, Utils::FileManager::fileToString(vertexShaderPath));
			mCompiledShaders.push_back(vertexShader);

			int fragmentShader = compileShader(GL_FRAGMENT_SHADER, Utils::FileManager::fileToString(fragmentShaderPath));
			mCompiledShaders.push_back(fragmentShader);

			if (!createProgram())
				Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Creation of Shader '" + resourceID + "' failed.\n\n");
		}

		Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath, std::string resourceID) :
			Resource(resourceID)
		{
			if (!Window::mOpenGLInitialised) {
				Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Tried to create Shader '" + resourceID + "' before OpenGL was initialised.\n\n");
				return;
			}
			
			int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderPath);
			mCompiledShaders.push_back(vertexShader);

			int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
			mCompiledShaders.push_back(fragmentShader);

			int geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryShaderPath);
			mCompiledShaders.push_back(geometryShader);

			if (!createProgram())
				Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Creation of Shader '" + resourceID + "' failed.\n\n");
		}

		void Shader::bind() { 
			if (mCurrentlyBound == this->mHandle)
				return;

			glUseProgram(mHandle);
			mCurrentlyBound = this->mHandle;
		}

		void Shader::addUniform(std::string name) {
			bind();
			
			if (!uniformAdded(name)) {
				int location = glGetUniformLocation(mHandle, name.c_str());

				if (location == -1)
					Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Uniform '" + name + "' does not exist/is not used in Shader '" + getUniqueID() + "'.\n\n");
				else
					mUniforms.push_back(Uniform(name, location));
			}
			else
				Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Uniform '" + name + "' has already been added in Shader '" + getUniqueID() + "'.\n\n");
		}

		void Shader::addUniformWithDefault(std::string name, int i) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, i);
		}

		void Shader::addUniformWithDefault(std::string name, int a, int b) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, a, b);
		}

		void Shader::addUniformWithDefault(std::string name, int a, int b, int c) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, a, b, c);
		}

		void Shader::addUniformWithDefault(std::string name, int a, int b, int c, int d) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, a, b, c, d);
		}

		void Shader::addUniformWithDefault(std::string name, float i) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, i);
		}

		void Shader::addUniformWithDefault(std::string name, glm::vec2 vec) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, vec);
		}

		void Shader::addUniformWithDefault(std::string name, glm::vec3 vec) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, vec);
		}

		void Shader::addUniformWithDefault(std::string name, glm::vec4 vec) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, vec);
		}

		void Shader::addUniformWithDefault(std::string name, glm::mat4 matrix) {
			addUniform(name);
			setUniform(mUniforms.size() - 1, matrix);
		}

		void Shader::setUniform(int index, int i) {
			glUniform1i(mUniforms[index].mLocation/*mUniformLocations[index]*/, i);
		}

		void Shader::setUniform(int index, int a, int b) {
			glUniform2i(mUniforms[index].mLocation/*mUniformLocations[index]*/, a, b);
		}

		void Shader::setUniform(int index, int a, int b, int c) {
			glUniform3i(mUniforms[index].mLocation/*mUniformLocations[index]*/, a, b, c);
		}

		void Shader::setUniform(int index, int a, int b, int c, int d) {
			glUniform4i(mUniforms[index].mLocation/*mUniformLocations[index]*/, a, b, c, d);
		}

		void Shader::setUniform(int index, float i) {
			glUniform1f(mUniforms[index].mLocation/*mUniformLocations[index]*/, i);
		}

		void Shader::setUniform(int index, glm::vec2 vec){
			glUniform2f(mUniforms[index].mLocation/*mUniformLocations[index]*/, vec.x, vec.y);
		}

		void Shader::setUniform(int index, glm::vec3 vec) {
			glUniform3f(mUniforms[index].mLocation/*mUniformLocations[index]*/, vec.x, vec.y, vec.z);
		}

		void Shader::setUniform(int index, glm::vec4 vec) {
			glUniform4f(mUniforms[index].mLocation/*mUniformLocations[index]*/, vec.x, vec.y, vec.z, vec.w);
		}

		void Shader::setUniform(int index, glm::mat4 matrix) {
			glUniformMatrix4fv(mUniforms[index].mLocation/*mUniformLocations[index]*/, 1, GL_FALSE, glm::value_ptr(matrix));
		}

		int Shader::compileShader(int shaderType, std::string source) {
			int shaderHandle = glCreateShader(shaderType);

			const char* charSource = source.c_str();
			glShaderSource(shaderHandle, 1, &charSource, NULL);
			glCompileShader(shaderHandle);

			int success;
			char infoLog[512];
			glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
				Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Shader compilation failure: " + std::string(infoLog) + "\n");
			}

			return shaderHandle;
		}

		bool Shader::createProgram() {
			mHandle = glCreateProgram();

			for (int i : mCompiledShaders)
				glAttachShader(mHandle, i);

			glLinkProgram(mHandle);

			//Error checking
			int success = 0;
			char infoLog[512];
			glGetProgramiv(mHandle, GL_LINK_STATUS, &success);

			if (!success) {
				glGetProgramInfoLog(mHandle, 512, NULL, infoLog);
				Utils::ConsoleLogger::log(Utils::ConsoleLogger::LogType::ERROR_WARN, "Shader linking failure: " + std::string(infoLog) + "\n");
				return false;
			}

			//Deleting shaders once they've been linked into the program object
			for (int& i : mCompiledShaders)
				glDeleteShader(i);

			return true;
		}

		bool Shader::uniformAdded(std::string name) {
			for (Uniform& u : mUniforms) {
				if (u.mName == name) 
					return true;
			}
			return false;
		}

	}
}