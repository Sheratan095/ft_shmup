#include "ft_shmup.hpp"

#ifndef BOSS_HPP
#define BOSS_HPP

class Boss : public AEnemy
{
	public:
		// Main ctor: specify position, symbol and health
		Boss(int x, int y, int width, int height)
			: AEnemy(x, y, width, height, "boss", BOSS_HEALTH, BOSS_COLOR_PAIR)
		{}

		~Boss()
		{}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		Bullet*	shoot() const { return (new Bullet(_x, _y + 1, BOSS_BULLET_COLOR_PAIR)); }
};

#endif