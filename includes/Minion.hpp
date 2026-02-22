#include "ft_shmup.hpp"

#ifndef MINION_HPP
#define MINION_HPP

class Minion : public AEnemy
{
	public:
		// Main ctor: specify position, symbol and health
		Minion(int x, int y, int sx, int sy)
			: AEnemy(x, y, sx, sy, MINION_SYMBOL, MINION_HEALTH, MINION_COLOR_PAIR)
		{}

		~Minion()
		{}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		Bullet*	shoot() const { return (new Bullet(_x + 1, _y, MINION_BULLET_COLOR_PAIR)); }
};

#endif