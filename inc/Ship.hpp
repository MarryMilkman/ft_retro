#ifndef SHIP_HPP
# define SHIP_HPP
# include <unistd.h>
# include <ncurses.h>

#include "Coord.hpp"
#include "Meh.hpp"

class Ship : public Coord, public Meh {

public:
	Ship( void );
	Ship(WINDOW *win);
	Ship( Ship const & src );
	// Ship (WINDOW * win, int y, int x, char c);
	Ship & operator=( Ship const & rhs ); // TODO:
	~Ship( void );

	void mvUp( void );
	void mvDown( void );
	void mvLeft( void );
	void mvRight( void );
	// void shot( void ); // will create a bullet (rocket)
	int	getMv( void );


// 	int		get_x(void);
// 	int		get_y(void);

// 	void	set_x(int value);
// 	void	set_y(int value);
private:
 	WINDOW * _win;
// 	int _yLoc, _xLoc;
// 	char _char;
};

#endif
