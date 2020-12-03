#pragma once
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace SemperGL
{
	struct ShaderSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	class Shader
	{
	public:
		Shader(const ShaderSource &source);
		~Shader();

		void Bind() const;
		void UnBind() const;
		inline uint32_t GetID() const { return m_ShaderID; }

		void SetUniform1i(const std::string &name, int value);
		void SetUniform1f(const std::string &name, float value);
		void SetUniform1d(const std::string &name, double value);

		void SetUniform2i(const std::string &name, int v1, int v2);
		void SetUniform2f(const std::string &name, float v1, float v2);
		void SetUniform2d(const std::string &name, double v1, double v2);

		void SetUniform3f(const std::string &name, float v1, float v2, float v3);

		void SetUniform4i(const std::string &name, int v0, int v1, int v2, int v3);
		void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
		void SetUniform4d(const std::string &name, double v0, double v1, double v2, double v3);

		void SetUniformMat2f(const std::string &name, const glm::mat2 &matrix);
		void SetUniformMat3f(const std::string &name, const glm::mat3 &matrix);
		void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

		static Shader *Create(const ShaderSource &source);
		static ShaderSource LoadFromGLSLFile(std::string filepath);
		static ShaderSource LoadFromGLSLFiles(std::string vertexPath, std::string fragmentPath);

	private:
		uint32_t CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
		uint32_t CompileShader(uint32_t type, const std::string &source);
		int GetUniformLocation(const std::string &name) const;

	private:
		uint32_t m_ShaderID;
		mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}