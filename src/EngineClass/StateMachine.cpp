#include "StateMachine.hpp"
#include "Start.hpp"
#include "Physics.hpp"
#include "Inputs.hpp"
#include "GameLogic.hpp"
#include "Render.hpp"
#include "Gui.hpp"
#include "Pause.hpp"
#include "Destroy.hpp"
#include "Stop.hpp"

IState	*StateMachine::_states[] =
{
	new Start,
	new Physics,
	new Inputs,
	new GameLogic,
	new Render,
	new Gui,
	new Pause,
	new Destroy,
	new Stop,
};

// CONSTRUCTOR DESTRUCTOR //

StateMachine::StateMachine(void) :	_currentState(STATE_RENDER)
{
}

StateMachine::~StateMachine(void)
{
}

// OVERLOADS //

StateMachine	&StateMachine::operator=(StateMachine const & rhs)
{
	(void)rhs;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, StateMachine const & rhs)
{
	o << rhs.toString();
	return o;
}

// PUBLIC //

std::string		StateMachine::toString(void) const
{
	std::stringstream ss;
	return ss.str();
}

void			StateMachine::RunApplication(Application & app)
{
	while (_currentState != STATE_EXIT)
		_states[_currentState]->RunState(app, _currentState);
}


// PRIVATE //

// GETTER SETTER //
