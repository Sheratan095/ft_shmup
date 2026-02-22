#include "ft_shmup.hpp"

#ifndef STAR_HPP
#define STAR_HPP

class Star : public AEntity
{
	public:
		// Main ctor: specify position, symbol and health
		Star(int x, int y, int sx, int sy)
			: AEntity(x, y, sx, sy, STAR_SYMBOL, PROP_HEALTH, STAR_COLOR_PAIR)
		{}

		~Star() {}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

};

#endif