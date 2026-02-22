#include "ft_shmup.hpp"

#ifndef AENEMY_HPP
#define AENEMY_HPP

class AEnemy : public AEntity
{
	public:
		AEnemy();
		AEnemy(int x, int y, int width, int height, char *symbol, int health, int colorPair)
			: AEntity(x, y, width, height, symbol, health, colorPair)
		{}
		virtual ~AEnemy() {}
};

#endif