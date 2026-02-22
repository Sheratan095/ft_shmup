#include "ft_shmup.hpp"

#ifndef MINION_HPP
#define MINION_HPP

class Minion : public AEnemy
{
	public:
		// Main ctor: specify position, symbol and health
		Minion(int x, int y, int width, int height)
			: AEnemy(x, y, width, height, "minion", MINION_HEALTH, MINION_COLOR_PAIR)
		{}

		~Minion()
		{}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		Bullet*	shoot() const { return (new Bullet(_x, _y + 1, MINION_BULLET_SYMBOL, MINION_BULLET_COLOR_PAIR)); }
};

#endif