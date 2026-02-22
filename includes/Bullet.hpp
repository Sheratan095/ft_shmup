#include "ft_shmup.hpp"

#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet : public AEntity
{
	public:
		Bullet(int x, int y) : AEntity(x, y, 0, 0, BULLET_SYMBOL, 1) {}
		~Bullet() {}
 
		int		getX() const { return _x; }
		int		getY() const { return _y; }
		char	getSymbol() const { return _symbol; }

		virtual bool move(int dx, int dy) override { _x += dx; _y += dy; return true; }
};

#endif