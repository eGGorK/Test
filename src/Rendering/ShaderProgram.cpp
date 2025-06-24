#include "ShaderProgram.h"
#include <iostream>
namespace Render {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vertexshaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexshaderID)) {
			std::cerr << "VERTEX SHADER complite-time error" << std::endl;
			return;
		}
		GLuint fragmentshaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentshaderID)) {
			std::cerr << "FRAGMENT SHADER complite-time error" << std::endl;
			glDeleteShader(vertexshaderID);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexshaderID);
		glAttachShader(m_ID, fragmentshaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infolog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER:Link-time error:\n" << infolog << std::endl;
		}
		else {
			m_isCompiled = true;
		}

		glDeleteShader(vertexshaderID);
		glDeleteShader(fragmentshaderID);
	}

	bool ShaderProgram::createShader(const std::string& source,GLenum shaderType, GLuint& ShaderID) {
		ShaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(ShaderID,1,&code, nullptr);
		glCompileShader(ShaderID);

		GLint success;
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infolog[1024];
			glGetShaderInfoLog(ShaderID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER:Complite-time error:\n" << infolog << std::endl;
			return  false;
		}
		return true;
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_ID); 
	}
	void ShaderProgram::use() const{
		glUseProgram(m_ID);
	}
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderprogram) noexcept {
		glDeleteProgram(m_ID);
		m_ID = shaderprogram.m_ID;
		m_isCompiled = shaderprogram.m_isCompiled;

		shaderprogram.m_ID = 0;
		shaderprogram.m_isCompiled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderprogram)noexcept {
		m_ID = shaderprogram.m_ID;
		m_isCompiled = shaderprogram.m_isCompiled;

		shaderprogram.m_ID = 0;
		shaderprogram.m_isCompiled = false;
	}

}