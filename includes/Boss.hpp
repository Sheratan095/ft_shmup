#include "ft_shmup.hpp"

#ifndef BOSS_HPP
#define BOSS_HPP

class Boss : public AEntity
{
	public:
		// Main ctor: specify position, symbol and health
		Boss(int x, int y, int sx, int sy, char symbol, int health) : AEntity(x, y, sx, sy, symbol, health)
		{}

		~Boss()
		{}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		void	takeDamage(int d) { _health -= d; if (_health < 0) _health = 0; }
		bool	isAlive() const { return _health > 0; }

		Bullet*	shoot() const { return (new Bullet(_x + 1, _y)); }
};

#endif