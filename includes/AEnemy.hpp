#include "ft_shmup.hpp"

#ifndef AENEMY_HPP
#define AENEMY_HPP

class AEnemy : public AEntity
{
	public:
		AEnemy();
		virtual ~AEnemy() = 0;

	Bullet*	shoot() const { return (new Bullet(_x - 1, _y)); }
};

#endif