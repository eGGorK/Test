#pragma once
#include <string>
#include <glad/glad.h>

namespace Render {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete; 
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderprogram) noexcept;
		ShaderProgram(ShaderProgram&& shaderprogram) noexcept;

		~ShaderProgram();
		
		bool isComplided() { return m_isCompiled;}

		void use() const;

	private:
		bool createShader(const std::string& source, GLenum shaderType, GLuint& ShaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;


	};
}