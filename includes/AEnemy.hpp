#include "ft_shmup.hpp"

#ifndef AENEMY_HPP
#define AENEMY_HPP

class AEnemy : public AEntity
{
	public:
		AEnemy();
		AEnemy(int x, int y, int sx, int sy, char symbol, int health) : AEntity(x, y, sx, sy, symbol, health)
		{}
		virtual ~AEnemy() = 0;

	Bullet*	shoot() const { return (new Bullet(_x ,_y)); }
};

#endif