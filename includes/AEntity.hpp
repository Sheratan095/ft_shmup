#include "ft_shmup.hpp"

#ifndef AENTITY_HPP
#define AENTITY_HPP

// Forward declaration to avoid circular dependency
class	Bullet;

class AEntity
{
	protected:
		int		_x;
		int		_sx = 0;
		int		_y;
		int		_sy = 0;
		char	_symbol;
		int		_health = -1;
		int		_colorPair = 0;

	public:
		AEntity(int x, int y, int sx, int sy, char symbol, int health = -1, int colorPair = 0)
			: _x(x), _sx(sx), _y(y), _sy(sy), _symbol(symbol), _health(health), _colorPair(colorPair)
		{}

		virtual ~AEntity() {}

		int		getX() const { return (_x); }
		int		getY() const { return (_y); }
		int		getSx() const { return (_sx); }
		int		getSy() const { return (_sy); }
		char	getSymbol() const { return (_symbol); }

		int		getHealth() const { return (_health); }
		void	setHealth(int health) { _health = health; }

		void	takeDamage(int damage) { _health -= damage; if (_health < 0) _health = 0; }

		bool	isAlive() const { return (_health > 0); }

		void	render(WINDOW* win) const
		{
			wattron(win, COLOR_PAIR(_colorPair));
			mvwaddch(win, getY(), getX(), getSymbol());
			wattroff(win, A_NORMAL);
		}


		virtual Bullet*	shoot() const { return nullptr; }

		virtual bool	move(int dx, int dy) { _x += dx; _y += dy; return true; };
};

#endif