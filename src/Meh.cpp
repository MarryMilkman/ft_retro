#include "Meh.hpp"

Meh::Meh()
{
}

Meh::Meh(Meh const & dest)
{
	*this = dest;
}

Meh::~Meh()
{
}

Meh		& Meh::operator=(Meh const & dest)
{
	this->_live = dest._live;
	this->_line = dest._line;
	this->_defLock = dest._defLock;
	this->_type = dest._type;
	return (*this);
}

/////////////// GETTER

int		Meh::get_live() const 
{
	return (this->_live);
}

int		Meh::get_act() const 
{
	return (this->_act);
}

int		Meh::get_line() const
{
	return (this->_line);
}

int		Meh::get_defLock() const
{
	return (this->_defLock);
}

int		Meh::get_lock() const
{
	return (this->_lock);
}

int		Meh::get_type() const
{
	return (this->_type);
}

///////////////// SETTER

void	Meh::set_live(int value)
{
	this->_live = value;
}

void	Meh::set_act(int value) 
{
	this->_act = value;
}

void	Meh::set_line(int value)
{
	this->_line = value;
}

void	Meh::set_defLock(int value)
{
	this->_defLock = value;
}

void	Meh::set_lock(int value)
{
	this->_lock = value;
}

void	Meh::set_type(int value)
{
	this->_type = value;
}