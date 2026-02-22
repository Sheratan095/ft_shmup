#include "ft_shmup.hpp"

#ifndef AENTITY_HPP
#define AENTITY_HPP

// Forward declaration to avoid circular dependency
class	Bullet;

class AEntity
{
	protected:
		int		_x;
		int		_y;
		char	*_symbol;
		int		_health = -1;
		int		_colorPair = 0;
		int		_width = 1;
		int		_height = 1;

	public:
		AEntity(int x, int y, int width, int height, char *symbol, int health = -1, int colorPair = 0)
			: _x(x), _y(y),  _width(width), _height(height), _symbol(symbol), _health(health), _colorPair(colorPair)
		{}

		virtual ~AEntity() {}

		int		getX() const { return (_x); }
		int		getY() const { return (_y); }
		int		getSpriteW() const { return (_width); }
		int		getSpriteH() const { return (_height); }
		char	*getSymbol() const { return _symbol; }

		int		getHealth() const { return (_health); }
		void	setHealth(int health) { _health = health; }

		bool	takeDamage(int damage) { _health -= damage; if (_health < 0) _health = 0; return (isAlive()); }

		int		getRight() const { return _x + _width - 1; }
		int		getBottom() const { return _y + _height - 1; }

		bool	checkCollision(const AEntity& other) const
		{
			return !(_x > other.getRight() || getRight() < other.getX() ||
					 _y > other.getBottom() || getBottom() < other.getY());
		}
		bool	isAlive() const { return (_health > 0); }

		void	render(WINDOW* win) const
		{
			wattron(win, COLOR_PAIR(_colorPair));
			mvwprintw(win, getY(), getX(), "%s", getSymbol());
			wattroff(win, A_NORMAL);
		}


		virtual Bullet*	shoot() const { return nullptr; }

		virtual bool	move(int dx, int dy) { _x += dx; _y += dy; return true; };
};

#endif