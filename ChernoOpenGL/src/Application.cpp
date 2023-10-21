
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath) {
	std::ifstream stream(filePath);

	enum class ShaderType {
		NONE =-1, VERTEX =0, FRAGMENT =1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("# shader") != std::string::npos) {
			
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(),ss[1].str() };
}


static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	// OpenGL wants an raw string (array of chars) instead of C++ string
	const char* src = source.c_str();
	
	// type of shader, how many source codes, address of the pointer that contains shader code, until reaching nullptr (end of source code)
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// i for integer result and v for vector(array) result which makes it a pointer
	int res;
	glGetShaderiv(id,GL_COMPILE_STATUS,&res);
	if (res == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		// Alloca is a C function that lets us allocate to stack dynamically 
		char* message =(char*) alloca(length*sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type ==GL_VERTEX_SHADER ? "vertex" : "fragmet") << " shader!" << std::endl;
		std::cout << message << std::endl;

		// Delete Failed shader and return
		glDeleteShader(id);
		return 0;
	}


	return id;

}

 //vertexShader and fragmentShader are the actual source code for these shaders as string
 //Better method would have been reading them in from a file  
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program  = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Link shaders into created program
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	// We can delete the intermidiate shaders since they are linked to the program
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

static unsigned int* CreateBuffer(int n) {
	// Generate n buffer and gives us id for the buffer (as buffer is an out variable)
	unsigned int* buffer = new unsigned int[n];
	glGenBuffers(n, buffer);

	return buffer;

}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//  Pass glad the function to load the address of the OpenGL function pointers which is OS-specific.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Positions of vertexes
	float position[] = {
		-0.5f,-0.5f, //0
		 0.5f,-0.5f, //1
		 0.5f, 0.5f, //2
		-0.5f, 0.5f, //3
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0,
	};

	unsigned int arrayBuffer = *CreateBuffer(1);

	// Bind arrayBuffer as main ArrayBuffer and 
	// Define Layout (4 vertex 2 floats in bytes, copy the values from position array, data won't change(STATIC) read for drawing (DRAW)
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), position, GL_STATIC_DRAW);

	// Enable and Define the vertexAttributes Layout inside the buffer (Starting from array index 0, 2 Floats,don't normalize, 2 floats bytes per vertex, 0th attribute)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int indexBuffer = *CreateBuffer(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");



	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);


	/* Game Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw Elements from indices
		glDrawElements(GL_TRIANGLES,  6, GL_UNSIGNED_INT,nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}