#include "Engine.hpp"

// STATIC //

Engine*		Engine::singleton = nullptr;

// CONSTRUCTOR DESTRUCTOR //

Engine::Engine()
{
	if (!singleton)
		singleton = this;
	_setupOpenGL = false;
	_app = nullptr;
	pause = false;

	// TODO from config file ?
	_winW = 0;
	_winH = 0;
	_versionMajor = 4;
	_versionMinor = 1;
	_aliasingSamples = 4;
	// end TODO
}

Engine::~Engine(void)
{
}

// OVERLOADS //

Engine	&Engine::operator=(Engine const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Engine const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Engine::RunApplication(Application* app)
{
	std::cout << "[ENGINE] <RunApplication> : " << app->name << std::endl;

	if (_app != nullptr)
	{
		_StopOpenGL();
		delete _app;
	}
	_app = app;
	if (_setupOpenGL == false)
	{
		_winW = app->winW;
		_winH = app->winH;
		_StartOpenGL();
	}
	app->shaderProgram3D = _CompileShader("3D"); // shader par defaut ?
	app->shaderProgramDebug = _CompileShader("Debug"); // shader par defaut ?
	app->window = _window;
	glfwSetKeyCallback(app->window, Inputs::KeyCallback);
	_SM.RunApplication(*app);
	_StopOpenGL();
}

std::string		Engine::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

void			Engine::Pause()
{
	pause = true;
}

// PRIVATE //

void			Engine::_StartOpenGL(void)
{
	std::cout << std::endl << "[ENGINE] <StartOpenGL>" <<  std::endl;
	if (_setupOpenGL == true)
		return ;

	if (!glfwInit())
		throw DError() << msg("could not start GLFW3");
	// set hints version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _versionMinor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window and GLFW context
	//if ((_window = glfwCreateWindow(_winW, _winH, _app->name.c_str(), nullptr, nullptr)) == nullptr)
	if ((_window = glfwCreateWindow(200, 200, "test", nullptr, nullptr)) == nullptr)
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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0, 0.0, 0.0, 1);
	glfwWindowHint(GLFW_SAMPLES, _aliasingSamples);
	
	// culling mode
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
	// texture setting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	_setupOpenGL = true;
}

void			Engine::_StopOpenGL(void)
{
	std::cout << "[ENGINE] <StopOpenGL>" << std::endl <<  std::endl;
	if (_app != nullptr)
		delete _app;
	if (_setupOpenGL == true)
	{
		_setupOpenGL = false;
		glfwTerminate();
	}
}

const char 		*Engine::_GetShaderCode(std::string filePath)
{
	std::ifstream	file;
	int			size;
	char*		inBuf = nullptr;

	file.open(filePath.c_str(),std::ios_base::binary);
	if (file.is_open())
	{
		file.seekg(0,std::ios::end);
		size = file.tellg();
		file.seekg(0,std::ios::beg);

		inBuf = new char[size + 1];
		inBuf[size] = '\0';
		file.read(inBuf,size);
		file.close();
	}
	else
		throw DError() << msg("GetShaderCode() failed. " + filePath + " not found.") ;
	return const_cast<const char*>(inBuf);
}

GLuint			Engine::_CompileShader(std::string name)
{
	// get shaders code
	std::stringstream 	vertexFilePath; 
	std::stringstream 	fragmentFilePath;

	vertexFilePath << "resources/Shaders/" << name << ".vert";
	fragmentFilePath << "resources/Shaders/" << name << ".frag";
	const char * vertexCode = _GetShaderCode(vertexFilePath.str());
	const char * fragmentCode = _GetShaderCode(fragmentFilePath.str());

	// compile vertex shader code
	GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &(vertexCode), nullptr);
	glCompileShader(vertexId);

	// compile fragment shader code
	GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &(fragmentCode), nullptr);
	glCompileShader(fragmentId);
	
	// create shader program
	GLuint			ShaderProgram;
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexId);
	glAttachShader(ShaderProgram, fragmentId);
	glLinkProgram(ShaderProgram);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
	delete vertexCode;
	delete fragmentCode;
	return (ShaderProgram);
}

// GETTER SETTER //
