#ifndef DOGLE_HPP
#define DOGLE_HPP

# include <iostream>
# include <sstream>
# include <fstream>
# include <ctime>
# include <list>
# include <vector>
# include <algorithm>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <SOIL2.h>
# include <fcntl.h>
# include <string.h>
# include <utility>
# include <vector>

# include "ogldev_math_3d.h"
# include "ogldev_util.h"
# include "glm/glm.hpp"
# include "glm/gtc/matrix_transform.hpp"
# include "glm/gtc/type_ptr.hpp"
# include "Error.hpp" 

# define C_YELLOW  "\x1B[33m"
# define C_GREEN  "\x1B[32m"
# define C_DEFAULT "\x1B[0m"
# define DEBUG 0
# define PRINT_DEBUG(str) if (DEBUG == 1) { std::cout << str << std::endl; }
# define SEPARATOR '|'
# define SEPARATOR_F ','

	typedef enum	state
	{
		STATE_START,
		STATE_PHYSICS,
		STATE_INPUTS,
		STATE_GAMELOGIC,
		STATE_RENDER,
		STATE_GUI,
		STATE_PAUSE,
		STATE_DESTROY,
		STATE_STOP,
		STATE_EXIT,
		STATE_NBR
	}				e_state;

#endif
