#include "Coord.hpp"

Coord::Coord(void)
{
}

Coord::Coord(Coord const & dest)
{
	*this = dest;
}

Coord::~Coord()
{
}

Coord		& Coord::operator=(Coord const & dest)
{
	this->_x = dest.get_x();
	this->_y = dest.get_y();
	this->_sym = dest.get_sym();
	return (*this);
}

//////////////// GETTER

int		Coord::get_x() const 
{
	return (this->_x);
}

int		Coord::get_y() const
{
	return (this->_y);
}

char	Coord::get_sym() const
{
	return (this->_sym);
}

///////////////// SETTER

void	Coord::set_x(int value)
{
	this->_x = value;
}

void	Coord::set_y(int value)
{
	this->_y = value;
}

void	Coord::set_sym(int value)
{
	this->_sym = value;
}