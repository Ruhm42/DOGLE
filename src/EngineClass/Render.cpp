#include "Render.hpp"
#include "Script.hpp"

// CONSTRUCTOR DESTRUCTOR //

Render::Render(void)
{
	
}

Render::~Render(void)
{

}

// OVERLOADS //

std::ostream	&operator<<(std::ostream & o, Render const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

void			Render::RunState(Application & app, e_state & currentState)
{
	PRINT_DEBUG("[MACHINE] <Render>");
	(void)app;
	// GLint variableLocation;

	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glViewport(0, 0, app.winW, app.winH);
	// glUseProgram(app.shaderProgramDebug);

	
	// // TODO


	static bool start = false;

	if (!start)
	{
    	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		printf("START\n");
		Vector3f Vertices[3];
    	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
	
 		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
		start = true;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


       glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
	glfwSwapBuffers(app.window);

	currentState = STATE_RENDER;
}

std::string		Render::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

// PRIVATE //


// GETTER SETTER //
