#include "Shader.h"
#include "FileManager.h"
#include "Logger.h"

//For checking if OpenGL has been initialised
#include "Window.h"

namespace GF {
	namespace Graphics {

		int Shader::mCurrentlyBound = 0;

		Shader::Shader(const std::string& resID, const std::string& vertPath, const std::string& fragPath, const std::string& geomPath) :
			Resource(resID)
		{
			if (!Window::mOpenGLInitialised) {
				Utils::Logger::log(Utils::Logger::LogType::ERROR_WARN, "Tried to create Shader '" + resID + "' before OpenGL was initialised.");
				return;
			}
			
			int vertHandle = compileShader(GL_VERTEX_SHADER, Utils::FileManager::fileToString(vertPath));
			mCompiledShaderHandles.push_back(vertHandle);

			int fragHandle = compileShader(GL_FRAGMENT_SHADER, Utils::FileManager::fileToString(fragPath));
			mCompiledShaderHandles.push_back(fragHandle);

			if(geomPath != "") {
				int geomHandle = compileShader(GL_GEOMETRY_SHADER, Utils::FileManager::fileToString(geomPath));
				mCompiledShaderHandles.push_back(geomHandle);
			}

			createProgram();
		}

		void Shader::bind() const { 
			if (mCurrentlyBound == this->mProgramHandle)
				return;
			
			glUseProgram(mProgramHandle);
			mCurrentlyBound = this->mProgramHandle;
		}

		void Shader::unbind() const { 
			glUseProgram(0); 
			mCurrentlyBound = 0; 
		}

		void Shader::addUniform(const std::string& name) {
			if(mUniformLocations.find(name) != mUniformLocations.end())
				return;
			
			bind();
			int location = glGetUniformLocation(mProgramHandle, name.c_str());
			if (location == -1) {
				Utils::Logger::log(Utils::Logger::LogType::ERROR_WARN, "Uniform '" + name + "' does not exist or is not used in Shader '" + getUniqueID() + "'.");
				return;
			}
			
			mUniformLocations.insert({ name, location });
		}

		void Shader::addUniformWithDefault(const std::string& name, float value) {
			addUniform(name);
			setUniform(name, value);
		}

		void Shader::addUniformWithDefault(const std::string& name, glm::vec2 value) {
			addUniform(name);
			setUniform(name, value);
		}

		void Shader::addUniformWithDefault(const std::string& name, glm::vec3 value) {
			addUniform(name);
			setUniform(name, value);
		}

		void Shader::addUniformWithDefault(const std::string& name, glm::vec4 value) {
			addUniform(name);
			setUniform(name, value);
		}

		void Shader::addUniformWithDefault(const std::string& name, glm::mat4 value) {
			addUniform(name);
			setUniform(name, value);
		}

		void Shader::setUniform(const std::string& name, float value) {
			glUniform1f(mUniformLocations[name], value);
		}

		void Shader::setUniform(const std::string& name, glm::vec2 value){
			glUniform2f(mUniformLocations[name], value.x, value.y);
		}

		void Shader::setUniform(const std::string& name, glm::vec3 value) {
			glUniform3f(mUniformLocations[name], value.x, value.y, value.z);
		}

		void Shader::setUniform(const std::string& name, glm::vec4 value) {
			glUniform4f(mUniformLocations[name], value.x, value.y, value.z, value.w);
		}

		void Shader::setUniform(const std::string& name, glm::mat4 value) {
			glUniformMatrix4fv(mUniformLocations[name], 1, GL_FALSE, glm::value_ptr(value));
		}

		int Shader::compileShader(int shaderType, const std::string& source) {
			int shaderHandle = glCreateShader(shaderType);

			const char* charSource = source.c_str();
			glShaderSource(shaderHandle, 1, &charSource, NULL);
			glCompileShader(shaderHandle);

			int compileSuccess;
			char infoLog[512];
			glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);

			if (!compileSuccess) {
				glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
				Utils::Logger::log(Utils::Logger::LogType::ERROR_WARN, "Shader '" + getUniqueID() + "'' compilation failure: " + std::string(infoLog)); 
			}

			return shaderHandle;
		}

		void Shader::createProgram() {
			mProgramHandle = glCreateProgram();

			for (int shaderHandle : mCompiledShaderHandles)
				glAttachShader(mProgramHandle, shaderHandle);

			glLinkProgram(mProgramHandle);

			int linkingSuccess = 0;
			char infoLog[512];
			glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &linkingSuccess);

			if (!linkingSuccess) {
				glGetProgramInfoLog(mProgramHandle, 512, NULL, infoLog);
				Utils::Logger::log(Utils::Logger::LogType::ERROR_WARN, "Shader '" + getUniqueID() + "' linking failure: " + std::string(infoLog));
			}

			for (int shader : mCompiledShaderHandles){
				glDetachShader(mProgramHandle, shader);
				glDeleteShader(shader);
			}
		}

	}
}