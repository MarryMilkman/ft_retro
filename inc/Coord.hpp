#ifndef COORD_HPP
# define COORD_HPP
# include <iostream>

class Coord
{
public:
	Coord();
	Coord(Coord const & dest);
	~Coord();

	int		get_x() const;
	int		get_y() const;
	char	get_sym() const;

	void	set_x(int value);
	void	set_y(int value);
	void	set_sym(int value);

	Coord		& operator=(Coord const & dest);

protected:
	int		_x;
	int		_y;
	char	_sym;
};

#endif