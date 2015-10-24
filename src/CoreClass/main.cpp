#include "DOGLE.hpp"
#include "Engine.hpp"
#include "Builder.hpp"
#include "ogldev_pipeline.h"


GLuint VBO;
GLuint VAO;
GLuint IBO;
GLuint gWorldLocation;
PersProjInfo gPersProjInfo;



void CreateVertexBuffer()
{
    Vector3f Vertices[4];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.5773f);
    Vertices[1] = Vector3f(0.0f, -1.0f, -1.15475f);
    Vertices[2] = Vector3f(1.0f, -1.0f, 0.5773f);
    Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);





 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);


}

static void CreateIndexBuffer()
{
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}








const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

void RenderSceneCB(GLFWwindow *_window)
{
    glClear(GL_COLOR_BUFFER_BIT);


    static float Scale = 0.0f;

    Scale += 0.01f;

    Pipeline p;
    p.Rotate(0.0f, Scale, 0.0f);
    p.WorldPos(0.0f, 0.0f, 5.0f);
    p.SetPerspectiveProj(gPersProjInfo);

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.GetWPTrans());



    
   	glBindVertexArray (VAO);



    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(_window);

}


/*
void CreateVertexBuffer()
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer (VBO, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}*/

void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

bool ReadFile(const char* pFileName, string& outFile)
{
    ifstream f(pFileName);
    
    bool ret = false;
    
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        
        f.close();
        
        ret = true;
    }
   
    
    return ret;
}

void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    
    string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
	}

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
    }

    glUseProgram(ShaderProgram);
        gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
    assert(gWorldLocation != 0xFFFFFFFF);
}

int main()
{		GLFWwindow		*_window;

	if (!glfwInit())
		throw DError() << msg("could not start GLFW3");
	// set hints version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window and GLFW context
	//if ((_window = glfwCreateWindow(_winW, _winH, _app->name.c_str(), nullptr, nullptr)) == nullptr)
	if ((_window = glfwCreateWindow(600, 600, "test", nullptr, nullptr)) == nullptr)
	{
		glfwTerminate();
		throw DError() << msg("glfw could not open window");
	}
	
	glfwMakeContextCurrent(_window);
	
	glewExperimental = GL_TRUE;
	glewInit();
	
	std::cout << "Renderer: " <<  (char*)glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version supported " <<  (char*)glGetString(GL_VERSION) << std::endl;

	// renderer attibuts
	
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glfwWindowHint(GLFW_SAMPLES, 4);
	





    CreateVertexBuffer();
    CreateIndexBuffer();

    CompileShaders();
        gPersProjInfo.FOV = 30.0f;
    gPersProjInfo.Height = 600;
    gPersProjInfo.Width = 600;
    gPersProjInfo.zNear = 1.0f;
    gPersProjInfo.zFar = 100.0f;
    while (1)
    	RenderSceneCB(_window);
 	glfwTerminate();
    return 0;
}


