#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <sstream>
#include <fstream>
#include <iostream>

namespace SemperGL
{
	Shader::Shader(const ShaderSource &source)
	{
		m_ShaderID = CreateShader(source.vertexSource, source.fragmentSource);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string &name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1f(const std::string &name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1d(const std::string &name, double value)
	{
		glUniform1d(GetUniformLocation(name), value);
	}

	void Shader::SetUniform2i(const std::string &name, int v1, int v2)
	{
		glUniform2i(GetUniformLocation(name), v1, v2);
	}

	void Shader::SetUniform2f(const std::string &name, float v1, float v2)
	{
		glUniform2f(GetUniformLocation(name), v1, v2);
	}

	void Shader::SetUniform2d(const std::string &name, double v1, double v2)
	{
		glUniform2d(GetUniformLocation(name), v1, v2);
	}

	void Shader::SetUniform3f(const std::string &name, float v1, float v2, float v3)
	{
		glUniform3f(GetUniformLocation(name), v1, v2, v3);
	}

	void Shader::SetUniform4i(const std::string &name, int v0, int v1, int v2, int v3)
	{
		glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniform4d(const std::string &name, double v0, double v1, double v2, double v3)
	{
		glUniform4d(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMat2f(const std::string &name, const glm::mat2 &matrix)
	{
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	void Shader::SetUniformMat3f(const std::string &name, const glm::mat3 &matrix)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	Shader *Shader::Create(const ShaderSource &source)
	{
		return new Shader(source);
	}

	ShaderSource Shader::LoadFromGLSLFile(std::string filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int) type] << line << "\n";
			}
		}
		return { ss[(int) ShaderType::VERTEX].str(), ss[(int) ShaderType::FRAGMENT].str() };
	}

	ShaderSource Shader::LoadFromGLSLFiles(std::string vertexPath, std::string fragmentPath)
	{
		std::ifstream vertexStream(vertexPath);
		std::ifstream fragmentStream(fragmentPath);

		std::string vertexSource((std::istreambuf_iterator<char>(vertexStream)),
			(std::istreambuf_iterator<char>()));

		std::string fragmentSource((std::istreambuf_iterator<char>(fragmentStream)),
			(std::istreambuf_iterator<char>()));

		std::cout << "{Vertex Source}:" << std::endl << vertexSource << std::endl;
		std::cout << "{Fragment Source}:" << std::endl << fragmentSource << std::endl;

		return { vertexSource, fragmentSource };
	}

	uint32_t Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
	{
		GLuint program = glCreateProgram();
		GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string &source)
	{
		GLuint id = glCreateShader(type);
		const GLchar *src = source.c_str();

		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		GLint result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char *message = (char *) _alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile" <<  (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "Shader!" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}
		return id;
	}

	int Shader::GetUniformLocation(const std::string &name) const
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_ShaderID, name.c_str());
		if (location == -1)
			std::cout << "Uniform %s"  << name << "doesn't exist!" << std::endl;

		m_UniformLocationCache[name] = location;
		return location;
	}
}
