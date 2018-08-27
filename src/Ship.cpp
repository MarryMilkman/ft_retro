#include "Ship.hpp"
#include <iostream>

#include "Game.hpp"

Ship::Ship( void ) {
	this->_sym = '>';
	this->_x = X_MIN + 3;
	this->_y = WIN_Y_SIZE / 2;
	this->_line = 0;
	this->_live = 3;
	this->_defLock = 0;
	this->_lock = 0;
	this->_act = 0;
}

 Ship::Ship( WINDOW * win) : _win(win){
 	this->_sym = '>';
	this->_x = X_MIN + 3;
	this->_y = WIN_Y_SIZE / 2;
	this->_line = 0;
	this->_live = 3;
	this->_defLock = 0;
	this->_lock = 0;
	this->_act = 0;
 	return ;
}

Ship::Ship( Ship const & src ) {
	*this = src;
	return ;
}

Ship & Ship::operator=( Ship const & dest ) {
	this->_x = dest._x;
	this->_y = dest._y;
	this->_live = dest._live;
	this->_lock = dest._lock;
	this->_defLock = dest._live;
	this->_lock = dest._lock;
	return (*this);
	// TODO: add more copying of fields from the partent class, if needed
}

Ship::~Ship( void ) {
	return ;
}


void Ship::mvUp( void ) {
	if (this->_y > Y_MIN) {
		(this->_y)--;
	}
}

void Ship::mvDown( void ) {
	if (this->_y < Y_MAX - 1) {
		(this->_y)++;
	}
}

void Ship::mvLeft( void ) {
	if (this->_x > X_MIN) {
		(this->_x)--;
	}
}

void Ship::mvRight( void ) {
	if (this->_x < X_MAX - 1) {
		(this->_x)++;
	}
}

int Ship::getMv( void ) {
	int input = wgetch(this->_win);
	switch (input) {
		case KEY_UP:
			mvUp();
			break;
		case KEY_DOWN:
			mvDown();
			break;
		case KEY_LEFT:
			mvLeft();
			break;
		case KEY_RIGHT:
			mvRight();
			break;
		default:
			break;
	}
	return (input);
}


