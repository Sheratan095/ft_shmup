#include "ft_shmup.hpp"

#ifndef AENEMY_HPP
#define AENEMY_HPP

class AEnemy : public AEntity
{
	public:
		AEnemy();
		AEnemy(int x, int y, int sx, int sy, char symbol, int health) : AEntity(x, y, sx, sy, symbol, health, 0)
		{}
		virtual ~AEnemy() = 0;
};

#endif