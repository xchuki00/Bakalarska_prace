#include "Shader.h"
GLuint LoadShaders(std::string vertex, std::string fragment)
{
	GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string vCode;
	std::string fCode;

	std::ifstream vstream(vertex);
	std::ifstream fstream(fragment);

	if(vstream.is_open())
	{
		std::string line = "";
		while (!vstream.eof()) {

			std::getline(vstream,line);
			vCode += "\n"+ line;
		}

		vstream.close();
		
	}
	
	if (fstream.is_open())
	{
		//read vshader to vshader code
		std::string line = "";
		while (!fstream.eof()) {
			std::getline(fstream, line);
			fCode += "\n" + line;
		}
		fstream.close();
	}

	char const *vPointer = vCode.c_str();
	char const *fPointer = fCode.c_str();
	glShaderSource(vShaderID, 1, &vPointer,NULL);
	glShaderSource(fShaderID, 1, &fPointer,NULL);
	glCompileShader(fShaderID);
	glCompileShader(vShaderID);
	//check shaders
	GLint res = GL_FALSE;
	int logLen;
	int error = 0;
	glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &res);
	glGetShaderiv(vShaderID, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0) {
		std::vector<char> VertexShaderErrorMessage(logLen + 1);
		glGetShaderInfoLog(vShaderID, logLen, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		error = 1;
	}else{
		printf("vertex ok\n");
	}
	glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &res);
	glGetShaderiv(fShaderID, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0) {
		std::vector<char> fShaderErrorMessage(logLen + 1);
		glGetShaderInfoLog(fShaderID, logLen, NULL, &fShaderErrorMessage[0]);
		printf("%s\n", &fShaderErrorMessage[0]);
		error = 1;
	}else{
		printf("fragment ok\n");
	}
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vShaderID);
	glAttachShader(ProgramID, fShaderID);
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &res);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0) {
		std::vector<char> ProgramErrorMessage(logLen + 1);
		glGetProgramInfoLog(ProgramID, logLen, NULL, &ProgramErrorMessage[0]);
		printf("Program: %s\n", &ProgramErrorMessage[0]);
		error = 1;
	}else{
		printf("program ok\n");
	}

	glDetachShader(ProgramID, vShaderID);
	glDetachShader(ProgramID, fShaderID);

	glDeleteShader(vShaderID);
	glDeleteShader(fShaderID);
	if(error==0){
		std::cout << "nacteny shadry " <<vertex<<" a "<<fragment << std::endl;
	}else{
		std::cout << "NEPODARILO se nacist shadry " << vertex << " a " << fragment << std::endl;
	}
	return ProgramID;
}
