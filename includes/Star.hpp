#include "ft_shmup.hpp"

#ifndef STAR_HPP
#define STAR_HPP

class Star : public AEntity
{
	private:
		const char *_symbols[2][3] = {
			{ ".", "*", "+" },
			{ ":", "^", "x" }
		};
		int _speed; 
	public:
		// Main ctor: specify position, symbol and health
		Star(int x, int y, int sx, int sy)
			: AEntity(x, y, sx, sy, ":", PROP_HEALTH, STAR_COLOR_PAIR)
		{
			_speed = 1 + rand() % 3; // Random speed between 1 and 3
			_symbol = _symbols[rand() % 2][3 - _speed]; // Random symbol
		}

		~Star() {}

		int		getSpeed() const { return _speed; }
		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }
		const char* getSymbol() const { return _symbols[rand() % 2][_speed - 1]; }
		


		void	render(WINDOW* win) const
		{
			wattron(win, COLOR_PAIR(_colorPair) | A_DIM);
			mvwprintw(win, getY(), getX(), "%s", getSymbol());
			wattroff(win, COLOR_PAIR(_colorPair) | A_DIM);
		}

};

#endif