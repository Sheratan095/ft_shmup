#include "ft_shmup.hpp"

#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet : public AEntity
{
	public:
		Bullet(int x, int y, char *symbol, int colorPair)
			: AEntity(x, y, 1, 1, symbol, 1, colorPair) {}
		~Bullet() {}
 
		int		getX() const { return _x; }
		int		getY() const { return _y; }
		char	getSymbol() const { return *_symbol; }

		

		virtual bool move(int dx, int dy) override { _x += dx; _y += dy; return true; }
};

#endif