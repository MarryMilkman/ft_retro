#include "Elem.hpp"

#include "Game.hpp"

Elem::Elem()
{	
	int	z;

	this->_type = 1;
	this->_sym = 'X';
	z = (this->_type == 1 ? 4 : 0);
	this->_x = X_MAX - 1;
	this->_y = (unsigned int)rand() % (Y_MAX - 1);
	this->_partner = 0;
	this->_line = -1;
	this->_live = 1;
	this->_defLock = z;
	this->_lock = this->_defLock;
	this->next = 0;
	this->_act = 1;
}

Elem::Elem(int x, int y, int type, int line)
{
	int	z;

	this->_type = type;
	this->_sym = '-';
	z = type == 1 ? 4 : 0;
	this->_x = x;
	this->_y = y;
	this->_partner = 0;
	this->_line = line;
	this->_live = 1;
	this->_defLock = z;
	this->_lock = this->_defLock;
	this->next = 0;
	this->_act = 1;
}

Elem::Elem(Elem const & dest)
{
	*this = dest;
}

Elem::~Elem()
{
}

int		Elem::checkBullet()
{
	if (!(rand() % 100) && this->_type == 1)
		return (-1);
	return (0);
}

Elem	& Elem::operator=(Elem const &dest)
{
	this->_x = dest._x;
	this->_y = dest._y;
	this->_partner = dest._partner;
	this->_live = dest._live;
	this->next = dest.next;
	this->_lock = dest._lock;
	return (*this);
}