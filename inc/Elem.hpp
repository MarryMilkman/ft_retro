#ifndef ELEM_HPP
# define ELEM_HPP

# include "Meh.hpp"
# include "Coord.hpp"


class Elem : public Coord, public Meh
{
public:
	Elem();
	Elem(int x, int y, int type, int line);
	Elem(Elem const & dest);
	~Elem();
	
	Elem	& operator=(Elem const & dest);
	int		checkBullet();

	Elem		*next;

private:
	Elem	*_partner;
};

#endif