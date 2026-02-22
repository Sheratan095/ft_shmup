#include "ft_shmup.hpp"

#ifndef ASTEROID_HPP
#define ASTEROID_HPP

class Asteroid : public AEntity
{
	public:
		// Main ctor: specify position, symbol and health
		Asteroid(int x, int y, int sx, int sy) : AEntity(x, y, sx, sy, ASTEROID_SYMBOL, ASTEROID_HEALTH)
		{}

		~Asteroid() {}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		void	takeDamage(int d) { _health -= d; if (_health < 0) _health = 0; }
		bool	isAlive() const { return _health > 0; }

		Bullet*	shoot() const { return (new Bullet(_x + 1, _y)); }
};

#endif