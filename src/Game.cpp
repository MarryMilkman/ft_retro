#include "Game.hpp"

Game::Game()
{
	this->elem = 0;
	this->_cycl = 0;
	this->_score = 3;
	this->_score_to_live = 50;
}

Game::Game(Game const & dest)
{
	*this = dest;
}

Game::~Game()
{
	Elem	*d_elem;

	while (this->elem)
	{
		d_elem = this->elem;
		this->elem = this->elem->next;
		delete d_elem;
	}
	::exit(0);
}

///////////////////////

void	Game::_do_cycl(void)
{
	Elem	*elem = this->elem;
	int		z = (rand() % 2 == 0 ? 1 : -1);

	while (elem)
	{
		if (!(elem->get_lock()) && elem->get_live() > 0)
		{
			elem->set_lock(elem->get_defLock());
			elem->set_x(elem->get_x() + elem->get_line());
			if (elem->get_type() == 1)
				elem->set_y(elem->get_y() + ((rand() % 8 == 0) ? z : 0));
			Game::_checkCoord(elem);
		}
		else
			elem->set_lock(elem->get_lock() - 1);
		Game::_createBull(elem->checkBullet(),
					elem->get_x() - 1, elem->get_y());
		elem = elem->next;
	}
	if (!(this->_cycl % (6 + rand() % 2)))
		Game::_addElem();
	Game::_check_cycl();
	Game::_reAct();
	this->_cycl++;
}

void	Game::_checkCoord(Elem *ch_elem)
{
	Elem	*elem = this->elem;
	int		loos_live;

	loos_live = 1;
	ch_elem->set_act(0);
	while (elem)
	{
		if (elem != ch_elem && elem->get_x() == ch_elem->get_x()
			&& elem->get_y() == ch_elem->get_y()
			&& elem->get_live() > 0 && (!elem->get_act()
				|| ch_elem->get_line() != elem->get_line()
				|| elem->get_type() == 1))
		{
			if (ch_elem->get_line() == 1 && elem->get_line() == -1
				&& elem->get_type() == 1)
				this->_score += 20;
			if (ch_elem->get_line() == 1 && elem->get_line() == -1
				&& elem->get_type() == 2)
				this->_score += 5;
			ch_elem->set_live(ch_elem->get_live() - 1);
			elem->set_live(elem->get_live() - 1);
		}
		if (elem->get_x() == this->ship->get_x()
			&& elem->get_y() == this->ship->get_y()
			&& elem->get_live() > 0)
		{
			if (elem->get_type() == 2 && loos_live == 1)
				this->_score += 5;
			if (elem->get_type() == 1 && loos_live == 2)
				this->_score += 10;
			this->ship->set_live(this->ship->get_live() - loos_live);
			elem->set_live(elem->get_live() - 1);
		}
		if ((elem->get_x() > WIN_X_SIZE - 2 || elem->get_y() > WIN_Y_SIZE - 2
			|| elem->get_x() < WIN_X_MIN + 2 || elem->get_y() < WIN_Y_MIN + 1)
			&& elem->get_live() > 0)
			elem->set_live(elem->get_live() - 5);
		elem = elem->next;
	}
}

void	Game::_reAct(void)
{
	Elem	*elem = this->elem;

	while (elem)
	{
		elem->set_act(1);
		elem = elem->next;
	}
}

void	Game::_check_cycl(void)
{
	if (this->ship->get_live() <= 0)
		this->_gameOver();
	Elem	*elem = this->elem;
	Elem	*s_elem = 0;
	Elem	*d_elem = 0;

	while (elem)
	{
		if (elem->get_live() <= 0)
		{
			d_elem = elem;
			if (s_elem)
				s_elem->next = elem->next;
			else
				this->elem = elem->next;
			elem = elem->next;
			delete d_elem;
			d_elem = 0;
			continue ;
		}
		s_elem = elem;
		elem = elem->next;
	}
	s_elem = 0;
	elem = 0;
}

void	Game::_display()
{
	Elem	*elem = this->elem;
	int		c = 3;

	wattron(win, COLOR_PAIR(c));
	mvwaddch(this->win, this->ship->get_y(), this->ship->get_x(),
		this->ship->get_sym());
	wattroff(win, COLOR_PAIR(c));
	while (elem)
	{
		if (elem->get_type() == 2 && elem->get_line() == -1)
			c = 6;
		if (elem->get_type() == 2 && elem->get_line() == 1)
			c = 2;
		if (elem->get_type() == 1)
			c = 1;
		wattron(win, COLOR_PAIR(c));
		mvwaddch(this->win, elem->get_y(), elem->get_x(),
			elem->get_sym());
		elem = elem->next;
		wattroff(win, COLOR_PAIR(c));
	}
}








/////////////////////

void	Game::hendlGame()
{
	int sec = 0;
	time_t start = time(0);
	char	t;

	initscr();
	cbreak();
	curs_set(0);
	curs_set(0);
	noecho();
	this->win = newwin(WIN_Y_SIZE, WIN_X_SIZE, 2, 0);
	this->header = newwin(3, WIN_X_SIZE, 0, 0);
	this->ship = new Ship(this->win);
	this->_start_color();
	wrefresh(this->win);
	wrefresh(this->header);
	keypad(this->win, true);
	srand(time(NULL));
	nodelay(this->win, true);
	while (true)
	{
		sec = difftime( time(0), start);
		werase(this->win);
		this->_do_cycl();
		this->_display_header(sec);
		// mvwprintw(this->header, 1, 1, 
		// 	"Score: %4d || Live: %d || Time from start: %0.2d:%0.2d", 
		// 	this->_score, this->ship->get_live(), sec / 60, sec % 40);
		box(this->win, 0, 0);
		t = this->ship->getMv();
		this->_find_target(t, sec, start);
		this->_display();
		wrefresh(win);
		wrefresh(header);
		usleep(40000 - (sec * 300 > 30000 ? 30000 : sec * 300));
		if (this->_score > this->_score_to_live
			&& (this->_score_to_live += this->_score))
			this->ship->set_live(this->ship->get_live() + 1);
	}
}

//////////////////////


void	Game::_find_target(char const t, int sec, time_t start)
{
	int		n;

	n = 0;
	if (t == 'p')
		while ((n = wgetch(this->win)) != 'p')
		{
			if (n == 'q')
				Game::_gameOver();
			sec = difftime( time(0), start);
			this->_display_header(sec);
			// mvwprintw(this->header, 1, 1, 
			// 	"Score: %4d || Live: %d || Time from start: %0.2d:%0.2d", 
			// 	this->_score, this->ship->get_live(), sec / 60, sec % 60);
			box(this->win, 0, 0);
			wrefresh(header);
			this->_display();
		}
	if (t == 'c')
		while ((n = this->ship->getMv()) != 'c')
		{
			if (n == 'q')
				Game::_gameOver();
			sec = difftime( time(0), start);
	//		werase(this->win);
			this->_display_header(sec);
			// mvwprintw(this->header, 1, 1, 
			// 	"Score: %4d || Live: %d || Time from start: %0.2d:%0.2d", 
			// 	this->_score, this->ship->get_live(), sec / 60, sec % 60);
			box(this->win, 0, 0);
			wrefresh(header);
			this->_display();
		}
	if (t == 'q')
		this->_gameOver();
	if (t == 'h')
		this->ship->set_live(this->ship->get_live() + 1);
	if (t == ' ')
	{
		if (this->_score > 0)
		{
			this->_score--;
			Game::_createBull(1,
					this->ship->get_x() + 1, this->ship->get_y());
		}
	}
}

void	Game::_display_header(int sec)
{
	mvwprintw(this->header, 1, 1, 
		"Score: %4d || Live: %d || %s%d || Time from start: %0.2d:%0.2d", 
		this->_score, this->ship->get_live(),
		"Score to Live: ", this->_score_to_live,
		sec / 60, sec % 60);
}

void	Game::_start_color()
{
	start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
}



void	Game::_addElem()
{
	Elem	*new_elem = new Elem();

	new_elem->next = this->elem;
	this->elem = new_elem;
}

void	Game::_createBull(int line, int x, int y)
{
	if (line == 0)
		return ;

	Elem	*elem = new Elem(x, y, 2, line);
	elem->next = this->elem;
	this->elem = elem;
}

void	Game::_gameOver(void)
{
	endwin();

	std::cout << "GAME OVER\nScore: " << this->_score << std::endl;
	Game::~Game();

	::exit(0);
}

///////////////////////

Game	& Game::operator=(Game const & dest)
{
	this->elem = dest.elem;
	this->ship = dest.ship;
	this->_cycl = dest._cycl;
	this->_score = dest._score;
	return (*this);
}

////////////////////////

int		Game::get_cycl() const
{
	return (this->_cycl);
}

void	Game::set_cycl(int value)
{
	this->_cycl = value;
}