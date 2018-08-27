#ifndef GAME_HPP
# define GAME_HPP
# include <iostream>
# include <unistd.h>
# include <ncurses.h>
# define WIN_X_MIN 0
# define WIN_Y_MIN 0
# define WIN_X_SIZE 170
# define WIN_Y_SIZE 30
// WIN_MIN - 1
# define X_MIN 1
# define Y_MIN 1
// WIN_SIZE - 1
# define X_MAX 169
# define Y_MAX 29

# include "Ship.hpp"
# include "Elem.hpp"



class Game
{

public:
	Game();
	Game(Game const & dest);
	~Game();

	Elem	*elem;
	Ship	*ship;

	WINDOW	*win;
	WINDOW	*header;

	void	hendlGame();

	Game	& operator=(Game const & dest);
	int		get_cycl() const;
	void	set_cycl(int value);

private:
	void			_display_header(int sec);
	void			_find_target(char const t, int sec, time_t start);
	void			_start_color(void);
	void			_reAct(void);
	void			_display();
	void			_gameOver();
	void			_createBull(int line, int x, int y);
	void			_addElem();
	void			_do_cycl();
	void			_check_cycl();
	void			_checkCoord(Elem *ch_elem);
	unsigned int	_score_to_live;
	unsigned int	_cycl;
	unsigned int	_score;

};

#endif