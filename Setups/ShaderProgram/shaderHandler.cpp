#include "shaderHandler.h"

std::string getFileRaw(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

ShaderHandler::ShaderHandler(const char* vertexFile, const char* fragmentFile) {
	std::string vertexRaw = getFileRaw(vertexFile);
	std::string fragmentRaw = getFileRaw(fragmentFile);

	const char* vertexCode = vertexRaw.c_str();
	const char* fragmentCode = fragmentRaw.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderHandler::activate(void) {
	glUseProgram(ID);
}

void ShaderHandler::deactive(void) {
	glDeleteProgram(ID);
}