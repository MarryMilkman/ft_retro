#ifndef MEH_HPP
# define MEH_HPP
# include <iostream>

class Meh
{
public:
	Meh();
	Meh(Meh const & dest);
	~Meh();
	
	Meh		& operator=(Meh const & dest);


	int		get_live() const ;
	int		get_partner() const;
	int		get_line() const;
	int		get_defLock() const;
	int		get_lock() const;
	int		get_type() const;
	int		get_act() const; 
	
	void	set_act(int value);
	void	set_live(int value);
	void	set_partner(int value);
	void	set_line(int value);
	void	set_defLock(int value);
	void	set_lock(int value);
	void	set_type(int value);

protected:
	int			_defLock;
	int			_lock;
	int			_type;
	int			_live;
	int			_line;
	int			_act;
};

#endif