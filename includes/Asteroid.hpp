#include "ft_shmup.hpp"

#ifndef ASTEROID_HPP
#define ASTEROID_HPP

class Asteroid : public AEntity
{
	public:
		// Main ctor: specify position, symbol and health
		Asteroid(int x, int y, int width, int height)
			: AEntity(x, y, width, height, "asteroid", ASTEROID_HEALTH, ASTEROID_COLOR_PAIR)
		{}

		~Asteroid() {}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

};

#endif